#ifndef COMPONENT_DATA_SHEET___H_H__
#define COMPONENT_DATA_SHEET___H_H__

class ComponentDataSheet
{
public:
  std::string name;
  bool has_data_sheet = false;
  std::vector<Table *> table_list;
  std::vector<Page *> pkg_list;

public:
  ComponentDataSheet(const std::string &s)
    : name(s)
  {
  }

  void add_package(Page *p)
  {
    pkg_list.push_back(p);
  }
    
  Table *find_table(const std::string &name)
  {
    for (auto t : table_list)
      {
	if (t->name == name)
	  {
	    return t;
	  }
      }
    return NULL;
  }
};


ComponentDataSheet *get_datasheet_info(const std::string &name);


#endif
