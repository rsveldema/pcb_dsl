#ifndef TABLE_H___
#define TABLE_H___

#include <vector>
#include "utils.h"

class Text
{
public:
  const int x, y, width, height;
  std::string string;
  
public:
  Text(int _x, int _y, int _width, int _height,
       const std::string &_string)
    : x(_x), y(_y), width(_width), height(_height),
      string(normalize_text(_string))
  {
  }
  
  bool isIllegalPinName() const;
  
  bool isBelow(const Text *elt) const
  {
    return y > elt->y;
  }

  const std::string &str() const { return string; }
  
  bool contains(const std::string &s) const
  {
    return string.find(s) != std::string::npos;
  }  
};


class Row
{
 public:
  const int y;
  std::vector<Text *> cols;
  
 public:
  Row(int _y)
    : y(_y)
    {
    }

  void dump()
  {
    fprintf(stderr, "%d: ", y);
    for (auto t : cols)
      {
	fprintf(stderr, "%s, ", t->str().c_str());
      }
    fprintf(stderr, "\n");
  }

  void add(Text *p)
  {
    cols.push_back(p);
  }
  
  bool hasKey(const std::string &s) const
  {
    if (cols.size() == 0)
      {
	return false;
      }    
    return cols[0]->str() == s;
  }

  Text* get(unsigned ix) const { return cols[ix]; }
};

class Table
{  
 public:
  std::vector<Row *> rows;
  std::string name;

 public:
  Table(const std::string &n)
    : name(n)
    {
    }

  void dump()
  {
    for (auto r : rows)
      {
	r->dump();
      }
  }

  void cleanup()
  {
    std::vector<Row *> cleaned;    
    for (auto r : rows)
      {
	if (r->cols.size() > 1)
	  {
	    cleaned.push_back(r);
	  }
      }
    rows = cleaned;
  }
  
  void add(Text *p)
  {
    auto row = find_row(p);
    row->add(p);
  }

  Row *find_row(Text *p)
  {
    for (auto r : rows)
      {
	if (r->y == p->y)
	  {
	    return r;
	  }
      }
    
    auto newrow = new Row(p->y);
    rows.push_back(newrow);
    return newrow;
  }
  
  Row *find_row_by_key(const std::string &key)
  {
    for (auto r : rows)
      {
	if (r->hasKey(key))
	  {
	    return r;
	  }
      }
    return NULL;
  }
};



class Page
{
 private:
  std::vector<Text*> texts;
  int width;
  int height;

 public:
  std::string name;
  
 public:
  Page(int _width, int _height)
    : width(_width), height(_height)
    {
    }

  Page *extractPinTexts();

  bool isDualCol()
  {
    return true;
  }
  
  unsigned getColumn(Text *t)
  {
    if (isDualCol())
      {
	if (t->x < (width / 2))
	  {
	    return 0;
	  }
	return 1;
      }
    return 0;
  }
  
  Page *extract_section(const std::string &title);

  bool contains(const std::string &str)
  {
    return find(str) != NULL;
  }
  
  Text *find(const std::string &title)
  {
    for (Text *t : texts)
      {
	if (t->contains(title))
	  {
	    return t;
	  }
      }
    return NULL;
  }

  void add(Text *t)
  {
    texts.push_back(t);
  }

  Table *extractTable()
  {
    auto table = new Table("");
    for (auto p : texts)
      {
	table->add(p);
      }
    return table;
  }

  void dump()
  {
    for (auto t : texts)
      {
	fprintf(stderr, "(%d,%d): %s\n", t->x, t->y, t->string.c_str());
      }
  }
};


void parse_xml(const char *xml,
	       std::vector<Page *> &pages);

#endif
