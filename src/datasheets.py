from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from bs4 import BeautifulSoup
from antlr4 import *
import os
import sys

def unimplemented(msg):
    print("UNIMPLEMENTED: " + msg)
    sys.exit(1)

def error(msg):
    print("ERROR: " + msg)
    assert False

def normalize(string):
    string = string.replace('–', '-')
    return string

pin_forbidden = ["CAUTION"]

class Text:
    def __init__(self, x, y, string, width, height):
        self.x = x;
        self.y = y;
        self.string = string
        self.width = width
        self.height = height

    def contains(self, s):
        return self.string.find(s) >= 0

    def isBelow(self, elt):
        return self.y > elt.y

    def isIllegalPinName(self):
        if self.string[0] == '-' or self.string[0] == '–':
            return True
        
        for f in pin_forbidden:
            if self.string.find(f) >= 0:
                return True
            
        if self.string.find(' ') >= 0:
            return True
        if self.string[0] == '_':
            return True
        if self.string[0] == '(':
            return True
        if len(self.string) > 16:
            return True
        return False
    
    def dump(self):
        print(self.string)


class Row:
    def __init__(self, y):
        self.cols = []
        self.y = y;

    def add(self,p):
        self.cols.append(p)

    def has_key(self, name):
        if len(self.cols) > 0:
            #print(self.cols[0].string + "  ================ " + name)
            if self.cols[0].string == name:
                return True
        return False

    def get(self, ix):
        return self.cols[ix]

        
class Table:
    def __init__(self):
        self.rows = []

    def add(self, p):
        row = self.find_row(p)
        row.add(p)

    def find_row(self, p):
        for r in self.rows:
            if r.y == p.y:
                return r
        newrow = Row(p.y)
        self.rows.append(newrow)
        return newrow


    def find_row_by_key(self, name):
        for r in self.rows:
            if r.has_key(name):
                return r
        return None
        
class Page:
    def __init__(self, width, height):
        self.texts = []
        self.width = width
        self.height = height

    def isDualCol(self):
        return True
        
    def add(self, t):        
        self.texts.append(t)
    
    def find(self, s):
        for t in self.texts:
            if t.contains(s):
                return t
        return None

    def contains(self, s):
        elt = self.find(s)
        return elt != None

    
    def getColumn(self, t):
        if self.isDualCol():
            if t.x < (self.width / 2):
                return 0
            return 1
        return 0
        
    def extract_section(self, s):
        elt = self.find(s)
        newPage = Page(self.width, self.height)
        myCol = self.getColumn(elt)
        for p in self.texts:
            if p.isBelow(elt):
                otherCol = self.getColumn(p)
                if otherCol == myCol:
                    newPage.add(p)
        return newPage

    def extractTable(self):
        table = Table();
        for p in self.texts:
            table.add(p)
        return table

    def extractPinTexts(self):
        newPage = Page(self.width, self.height)
        for p in self.texts:
            if not p.isIllegalPinName():
                newPage.add(p)
        return newPage

    def dump(self, msg):
        print("----- PAGE[" + msg + "]--------");
        for p in self.texts:
            p.dump()
        

        
def createPageArray(soup):
    pages = []
    for page in soup.find_all("page"):
        print("examining page " + page['number'])
        page_width = int(page['width'])
        page_height = int(page['height'])
        
        current = Page(page_width, page_height)
        pages.append(current)
        for t in page.find_all("text"):
            string = t.string
            if string != None:
                string = normalize(string)
                x = int(t['left'])
                y = int(t['top'])
                width = int(t['width'])
                height = int(t['height'])
                #print("saw: " + string)
                current.add(Text(x, y, string, width, height))

    return pages


def find_page(pages, title):
    for p in pages:
        if p.contains(title):
            return p
    error("failed to find page holding " + title)
            

def extract_package(pkg_name, pages, title, outputName):
    p = find_page(pages, title)
    p = p.extract_section(title)
    p = p.extractPinTexts()
    p.dump("extracted subsection")
    p.name = pkg_name
    return p
    

    
def extract_table(tableName, pages, title, outputName):
    p = find_page(pages, title)
    p = p.extract_section(title)
    table = p.extractTable()
    table.name = tableName
    return table
    
def destringify(s):
    print("string ----- " + s)
    assert s[0] == '"'
    assert s[len(s)-1] == '"'
    return s[1:len(s)-1]

def extract_tables(comp, pages, ds_prop_list):
    for p in ds_prop_list:
        extractor = p.extractor
        if extractor != None:
            title            = destringify(p.title.text)
            table            = str(p.table.text)
            createdTableName = str(p.table.text)
            if extractor.text == "package":
                comp.add_package(extract_package(table, pages, title, createdTableName))
            elif extractor.text == "table":
                comp.add_table(extract_table(table, pages, title, createdTableName))
            else:
                unimplemented("extractor: " + extractor.text)


def getFileName(pl):
    for p in pl:
        if p.filename != None:
            return p.filename.text
    return None



#def enterComponent_property(self, ctxt):
#if len(ctxt.datasheet_prop()) > 0:


def process_datasheet_prop(comp, prop):
    filename = getFileName(prop) #ctxt.datasheet_prop())
    if filename == None:
        return;
    
    print("reading component prop: " + str(filename))
    os.system("pdftohtml -xml " + filename + " out.xml")
    fp = open("out.xml")
    soup = BeautifulSoup(fp, "xml")
    pages = createPageArray(soup)
    fp.close()
    
    extract_tables(comp, pages, prop)
    
