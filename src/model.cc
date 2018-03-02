#include "create_model.h"
#include <boost/algorithm/string/replace.hpp>


unsigned get_unique_id()
{
  static unsigned id;
  return id++;
}

std::string normalize(const std::string &str)
{
  std::string s(str);
  boost::replace_all(s, "-", "_");
  boost::replace_all(s, " ", "_");
  return s;
}


bool valid_pin_name(const std::string &name)
{
  if (name == "Name") {
    return false;
  }
  return true;
}
    

Pin *Component::get_pin_by_suffixes(const std::vector<dslParser::Access_suffixContext*> &suffixes,
				    ModelContext &context, bool odd)
{
  if (suffixes.size() == 0) {
    if (this->pins.size() == 1) {
      return this->pins[0];
    }
    
    if (this->pins.size() > 2) {
      printf("don't know which pin to address, please make it explicit: %s\n", this->name.c_str());
      abort();
    }
    
    return this->pins[odd];

  } else {
    auto s0 = suffixes[0];
    auto name = s0->ID()->getText();
    if (s0->index() == 0)
      return this->get_pin_by_name(name);
    else
      return this->get_pin_by_name(context.indexed_pin_name(name, s0->index()));
  }
}
