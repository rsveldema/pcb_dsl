#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
//#include <boost/foreach.hpp>

#include "create_model.hpp"


using boost::property_tree::ptree;

static
bool valid_pin_name(const std::string &name)
{
  if (name == "Name") {
    return false;
  }
  return true;
}
    

void Component::add_table(Model *m, Table *table)
{
  info->table_list.push_back(table);
  if (table->name == "pins")
    {
      for (auto row : table->rows)
	{
	  auto name = normalize_ident(row->get(0)->string);
	  if (valid_pin_name(name))
	    {
	      auto info = new PinInfo(name);
	      auto pin = add_pin(m, info);
	      pin->setDescription(row->get(1)->string);
	    }
	}
    }
}


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
  fprintf(stderr, "ERROR: failed to find page holding %s in PDF\n", title.c_str());
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
  if (pt.size() > 1)    
    {
      std::string ret;
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
		  auto sec = it.second;
		  int x = sec.get<int>("<xmlattr>.left");
		  int y = sec.get<int>("<xmlattr>.top");
		  int w = sec.get<int>("<xmlattr>.width");
		  int h = sec.get<int>("<xmlattr>.height");
		  std::string str = get_content(sec);

		  //printf("looking2 at %s\n", str.c_str());
		  
		  Text *t = new Text(x, y, w, h, str);
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
      comp->info->component_type = "RS-28";
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
  //p->dump();
  auto table = p->extractTable();
  table->name = tableName;
  return table;
}
    

static
void extract_tables(Model *model,
		    Component *comp,
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
	    comp->info->add_package(pkg);
	  } else if (extractor->getText() == "outline") {
	    extract_outline(comp, pages, title);
	  } else if (extractor->getText() == "table") {
	    auto tab = extract_table(table, pages, title, createdTableName);
	    tab->cleanup();
	    comp->add_table(model, tab);
	  } else {
	    abort();
	  }
	}
    }
}

void process_datasheet_prop(Model *model,
			    Component *comp,
			    const std::vector<dslParser::Datasheet_propContext *> &prop)
{
  auto filename = getFileName(prop);
  if (filename == "")
    return;
    
  printf("reading component prop: %s\n", filename.c_str());
  char cmd[64];
  sprintf(cmd, "pdftohtml -xml %s out.xml",  filename.c_str());
  int ret = system(cmd);
  assert(ret == 0);

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
    
  extract_tables(model, comp, pages, prop);
}
