#ifndef TABLE_H___
#define TABLE_H___

#include <vector>

class Text
{
 public:
  const int x, y, width, height;
  std::string string;

 public:
  Text(int _x, int _y, int _width, int _height,
       const std::string &_string)
    : x(_x), y(_y), width(_width), height(_height),
    string(_string)
    {
    }

  const std::string &str() const { return string; }
  
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
 private:
  std::vector<Row *> rows;
  
 public:
  const std::string name;

  Table(const std::string &n)
    : name(n)
    {
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
  Page(int _width, int _height)
    : width(_width), height(_height)
    {
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
};

void parse_xml(const char *xml);

#endif
