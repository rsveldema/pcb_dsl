from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from bs4 import BeautifulSoup
from antlr4 import *
import os
import sys
import svgwrite
from phys import Outline,Point,Dimension

__uniq=0


class Model:
    def __init__(self):
        self.constants={}
        self.components = []

    def find_component(self, name):
        for c in self.components:
            if c.name == name:
                return c
        print("ERROR: failed to find: " + name)
        failed_to_find_component()

    def writeSVG(self, filename):
        dwg = svgwrite.Drawing(filename, profile='tiny')
        #dwg.add(dwg.text('Test', insert=(10, 10.2), fill='red'))
        
        for c in self.components:
            c.writeSVG(dwg)

        dwg.save()        

    def writeDot(self, filename):
        fp = open(filename, "w")
        fp.write("graph model {\n")
        fp.write("\tgraph [fontsize=10 fontname=\"Verdana\" compound=true];\n");
        for c in self.components:
            c.writeDotFile(fp)
        fp.write("}");
        fp.close()

 
def normalize(s):
    s = s.replace('-', '_')
    s = s.replace(' ', '_')
    return s

def valid_pin_name(name):
    if name == "Name":
        return False
    return True

def get_unique_id():
    global __uniq
    __uniq +=1 
    return __uniq


class Pin:
    def __init__(self, comp, name):
        self.mode = None
        self.outline = Outline(self)
        self.name = name
        self.component = comp
        self.connections = []
        self.description = ""
        self.id = get_unique_id()

    def writeSVG(self, dwg):
        self.outline.writeSVG(dwg)
        
    def add_connection(self, to_pin):
        self.connections.append(to_pin)

    def setDescription(self, descr):
        self.description = descr
        
    def getDotID(self):
        return self.component.getDotID() +  "___PIN_" + str(self.id)

    def writeDotFile(self, fp):
        k = self.getDotID()
        fp.write(k + "[label=\""+self.name+"\"];\n")
        for c in self.connections:
            fp.write(k + " -- " + c.getDotID() + ";\n")

            
class Component:
    def __init__(self, model, name):
        self.model = model
        self.width = None
        self.height = None
        self.layers = None
        self.outline = Outline(self)
        self.id = get_unique_id()
        self.name = name
        self.pkg_list = []
        self.table_list = []
        self.pins = []

    def add_pin(self, name):
        pin = Pin(self, name)
        self.pins.append(pin)
        return pin

    def get_pin_by_name(self, name):
        for p in self.pins:
            #print("PIN COMPARE: " + p.name + " VS " + name)
            if p.name == name:
                return p

        print("failed to find pin " + name + " in component " + self.name)
        not_found()

        
    def get_pin_by_suffixes(self, suffixes, context, odd):
        if len(suffixes) == 0:
            if len(self.pins) == 1:
                return self.pins[0]
            if len(self.pins) > 2:
                print("don't know which pin to address, please make it explicit: " + str(self.name))
                error()
            return self.pins[odd]
        else:
            s0 = suffixes[0]
            name = str(s0.ID())
            if s0.index() == None:
                return self.get_pin_by_name(name)
            else:
                return self.get_pin_by_name(context.indexed_pin_name(name, s0.index()))
    
    def getDotID(self):
        return "ID" + str(self.id)

    def writeSVG(self, dwg):        
        self.outline.writeSVG(dwg)
        for p in self.pins:
            p.writeSVG(dwg)
        
    def writeDotFile(self, fp):
        k = self.getDotID()

        fp.write("subgraph cluster_" + k + " {\n")
        fp.write("\tcolor=red;\n")
        fp.write("\tnode [style=filled];\n");
        
        fp.write("\t" + k + "[label=\"" + self.name + "\"];\n")
        for p in self.pins:
            p.writeDotFile(fp)
            fp.write(k + " -- " + p.getDotID() + ";\n")
        fp.write("}\n")
        
    def add_package(self, pkg):
        self.pkg_list.append(pkg)
        for e in pkg.texts:
            #print("PINNNNNN: " + e.string)
            #self.add_pin()
            pass

    def add_table(self, table):
        self.table_list.append(table)
        if table.name == 'pins':
            for row in table.rows:
                name = normalize(row.get(0).string)
                if valid_pin_name(name):
                    pin = self.add_pin(name)
                    pin.setDescription(row.get(1).string)

    def find_table(self, name):
        for t in self.table_list:
            print(t.name + " vs " + name)
            if t.name == str(name):
                return t
        return None

    """
    access_suffix: ('.' ID index?)
    ;	   
    """
    def constant_fold(self, access_suffixes):
        name0 = str(access_suffixes[0].ID())
        name1 = str(access_suffixes[1].ID())
        
        #print("constant fold in component " + str(names) + ", list = " + str(self.table_list))
        table = self.find_table(name0)
        row = table.find_row_by_key(name1)
        value = int(row.get(1).string)
        print("PDF TABLE LOOKUP["+name0+"."+name1+"] = " + str(value))
        return value



