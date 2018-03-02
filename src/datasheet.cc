#include "create_model.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;

std::string getFileName(const std::vector<dslParser::Datasheet_propContext *> &pl)
{
  for (auto p : pl)
    {
      if (p->filename)
	{
	  return p->filename->getText();
	}
    }
  return "";
}


std::string get_content(ptree &pt)
{
  std::string ret;
  if (pt.size())
    {
      for (auto it : pt)
	{
	  auto name = it.first;
	  if (name != "<xmlattr>")
	    {
	      if (ret == "")
		{
		  ret += get_content(it.second);
		}
	      else
		{
		  ret += " " + get_content(it.second);
		}	       
	    }
	}      
      return ret;
    }
  else
    {
      return pt.data();
    }
}

void createPageArray(ptree &pt,
		     std::vector<Page *> &pages)
{
  for (auto page_it : pt.get_child("pdf2xml"))
    {
      auto name = page_it.first;
      if (name == "page")
	{
	  auto pt = page_it.second;
	  
	  int width = pt.get<int>("<xmlattr>.width");
	  int height = pt.get<int>("<xmlattr>.height");
	  int num = pt.get<int>("<xmlattr>.number");
	  
	  //printf("WxH, %d = %d, %d\n", width, height, num);
	  
	  Page *p = new Page(width, height);
	  pages.push_back(p);
	  
	  //printf("looking1 at %s\n", name.c_str());
	  
	  for (auto it : pt)
	    {
	      auto name = it.first;
	      if (name == "text")
		{	  
		  int x = pt.get<int>("<xmlattr>.left");
		  int y = pt.get<int>("<xmlattr>.top");
		  int w = pt.get<int>("<xmlattr>.width");
		  int h = pt.get<int>("<xmlattr>.height");
		  std::string str = get_content(it.second);

		  //printf("looking2 at %s\n", str.c_str());
				  
		  Text *t = new Text(x,y,w,h,str);
		  p->add(t);
		}
	    }
	}
    }
}

void parse_xml(const char *xml)
{  
  // Create an empty property tree object

  ptree pt;
  read_xml(xml, pt);
  
  std::vector<Page *> pages;
  createPageArray(pt, pages);
  
  //extract_tables(comp, pages, prop);
}


void process_datasheet_prop(Component *comp,
			    const std::vector<dslParser::Datasheet_propContext *> &prop)
{
  auto filename = getFileName(prop);
  if (filename == "")
    return;
    
  printf("reading component prop: %s\n", filename.c_str());
  char cmd[64];
  sprintf(cmd, "pdftohtml -xml %s out.xml",  filename.c_str());
  system(cmd);

  const char *xml ="out.xml";
  FILE *f = fopen(xml, "rb");
  if (! f)
    {
      xml = "out.xml.xml";
    }
  else
    {
      fclose(f);
    }

  parse_xml(xml);
}
