#include "create_model.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;

Page *find_page(std::vector<Page *> &pages,
		const std::string &title)
{
  for (Page *p : pages)
    {
      if (p->find(title))
	{
	  return p;
	}
    }
  abort();
  return NULL;
}
  
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
	  ///  int num = pt.get<int>("<xmlattr>.number");
	  
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

void parse_xml(const char *xml,
	       std::vector<Page *> &pages)
{  
  // Create an empty property tree object

  ptree pt;
  read_xml(xml, pt);
  
  createPageArray(pt, pages);
}


Page *Page::extract_section(const std::string &s)
{
  auto newPage = new Page(width, height);
  
  auto elt = find(s);
  auto myCol   = getColumn(elt);
  for (auto p : texts)
    {
      if (p->isBelow(elt))
	{
	  auto otherCol = getColumn(p);
	  if (otherCol == myCol)
	    {
	      newPage->add(p);
	    }
	}
    }
  return newPage;
}

std::vector<std::string> pin_forbidden = {"CAUTION"};
  
bool Text::isIllegalPinName() const
{
  if (string[0] == '-') { //|| string[0] == '–') {
    return true;
  }
        
  for (auto f : pin_forbidden) {
    if (string.find(f) != std::string::npos) {
      return true;
    }
  }
  
  if (string.find(' ') != std::string::npos) {
    return true;
  }
  
  if (string[0] == '_') {
    return true;
  }
  
  if (string[0] == '(') {
    return true;
  }
  
  if (string.size() > 16) {
    return true;
  }
  return false;
}

Page * Page::extractPinTexts()
{
  auto newPage = new Page(width, height);
  for (auto p : texts)
    {
      if (! p->isIllegalPinName())
	{
	  newPage->add(p);
	}
    }
  return newPage;
}

Page *extract_package(const std::string &pkg_name,
		      std::vector<Page *> pages,
		      const std::string &title,
		      const std::string &createdTableName)
{
  auto p = find_page(pages, title);
  p = p->extract_section(title);
  p = p->extractPinTexts();
  p->name = pkg_name;
  return p;
}

void extract_outline(Component *comp, 
		     std::vector<Page *> pages,
		     const std::string &title)
{
  auto p = find_page(pages, title);
  if (p->contains("28-Lead Shrink Small Outline Package (SSOP)") || p->contains("(RS-28)"))
    {
      comp->component_type = "RS-28";
      comp->create_outline();
    }
  else
    {
      abort();
    }
}
        
    
Table *extract_table(const std::string &tableName,
		     std::vector<Page *> pages,
		     const std::string &title,
		     const std::string &outputName)
{
  auto p = find_page(pages, title);
  p = p->extract_section(title);
  auto table = p->extractTable();
  table->name = tableName;
  return table;
}
    


void extract_tables(Component *comp,
		    std::vector<Page *> pages,
		    const std::vector<dslParser::Datasheet_propContext *> &ds_prop_list)
{
  for (auto p : ds_prop_list)
    {
      auto extractor = p->extractor;
      if (extractor)
	{
	  auto title            = destringify(p->title->getText());
	  auto table            = p->table->getText();
	  auto createdTableName = p->table->getText();
	  
	  if (extractor->getText() == "package") {
	    auto pkg = extract_package(table, pages, title, createdTableName);
	    comp->add_package(pkg);
	  } else if (extractor->getText() == "outline") {
	    extract_outline(comp, pages, title);
	  } else if (extractor->getText() == "table") {
	    auto tab = extract_table(table, pages, title, createdTableName);
	    tab->cleanup();
	    comp->add_table(tab);
	  } else {
	    abort();
	  }
	}
    }
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
  
  std::vector<Page *> pages;

  parse_xml(xml, pages);
    
  extract_tables(comp, pages, prop);
}