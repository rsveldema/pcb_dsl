from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from bs4 import BeautifulSoup
from antlr4 import *
import os
import sys
import svgwrite
from datasheets import process_datasheet_prop
from svgwrite import cm, mm  


__uniq=0
COMPONENT_INDEX_STRING=""


#svgwrite.rgb(10, 10, 16, '%')

def draw_wireframe_rect(dwg, x,y, ex, ey):
    dwg.add(dwg.line( (x, y),  (x, ey), stroke='green'))
    dwg.add(dwg.line( (x, y),  (ex, y), stroke='green'))
    dwg.add(dwg.line((ex, y), (ex, ey), stroke='green'))
    dwg.add(dwg.line((x, ey), (ex, ey), stroke='green'))


def draw_rect(dwg, from_pos, to_pos):
    draw_wireframe_rect(dwg,
               from_pos.x.svg(), from_pos.y.svg(),
               to_pos.x.svg(), to_pos.y.svg())

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

model = Model()
        
def isOdd(k):
    return k % 2 == 1

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
        self.name = name
        self.component = comp
        self.connections = []
        self.description = ""
        self.id = get_unique_id()
        self.location_from = self.location_to = None

    def writeSVG(self, dwg):
        pass
        
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
    def __init__(self, name):
        self.width = None
        self.height = None
        self.layers = None
        self.location_from = None
        self.location_to = None
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
        if self.location_from != None and self.location_to != None:
            draw_rect(dwg, self.location_from, self.location_to)
            for p in self.pins:
                p.writeSVG(dwg)
        elif self.location_from != None:
            draw_rect(dwg, self.location_from, self.location_to)
        
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




"""
access: ID index? access_suffix*
    ;

access_suffix: ('.' ID index?)
    ;	   
"""
def constant_fold_access(access):
    name  = str(access.ID())
    if len(access.access_suffix()) == 0:
        if access.index() == None:
            return model.constants[name]
        
    comp = model.find_component(name)
    if comp != None:
        return comp.constant_fold(access.access_suffix())
    unimpl()

class Dimension:
    def __init__(self, d, unit):
        if hasattr(d, "text"):
            self.value = float(d.text);
        else:
            self.value = d;

        if hasattr(unit, "name"):
            self.unit  = str(unit.name.text)
        else:
            self.unit = unit

    def svg(self):
        if self.unit == "mm":
            return self.value * mm
        if self.unit == "cm":
            return self.value * cm
        print("unknown unit for svg: " + self.unit)
        error()

class Point:
    def __init__(self, x, y):
        self.x = x;
        self.y = y

def constant_fold_primary(p):
    if p.expr() != None:
        return constant_fold_expr(p.expr())
    if p.access() != None:
        return constant_fold_access(p.access())
    if p.unit != None:
        return Dimension(p.n, p.unit())
    print("unrecognized primary expr: " + str(p))
    unimpl()

def constant_fold_expr(expr):
    p = expr.primary()
    if len(p) == 1:
        return constant_fold_primary(p[0])
    else:
        unimpl()


class ModelVar:
    def __init__(self, name, value):
        self.name = name
        self.value = value


class ModelContext:
    def __init__(self):
        self.vars = []

    def add(self, var):
        self.vars.append(var)

    def indexed_comp_name(self, name, index):
        for v in self.vars:
            if v.name == str(index.ID()):
                return name + COMPONENT_INDEX_STRING + str(v.value)            
        not_found()

    def indexed_pin_name(self, name, index):
        for v in self.vars:
            #print("EXAMINE " + v.name + " vs " + str(index.ID()))
            if v.name == str(index.ID()):
                return name + "" + str(v.value)
        print("ERRROR: failed to find " + str(index.ID()))
        not_found()

# access: ID index? access_suffix*
# 
# comp.P
# comp.P[x]
# comp[x].P
def access_to_component_pin(access, context, odd):
    name = str(access.ID())
    if access.index() != None:
        name = context.indexed_comp_name(name, access.index())

    comp = model.find_component(name)
    return comp.get_pin_by_suffixes(access.access_suffix(), context, odd)


def process_location(comp, loc_prop_list):
    for loc in loc_prop_list:
        x = constant_fold_expr(loc.expr()[0])
        y = constant_fold_expr(loc.expr()[1])
        if loc.from_tok != None:
            comp.location_from = Point(x,y)
        else:
            comp.location_to = Point(x,y)

def process_dimensions(comp, dim_prop_list):
    for dim in dim_prop_list:
        if dim.width != None:
            comp.width = constant_fold_expr(dim.width)
        if dim.height != None:
            comp.height = constant_fold_expr(dim.height)
        if dim.layers != None:
            comp.layers = constant_fold_expr(dim.layers)
    if comp.name == "board":
        print("BOArD SIZE = " + str(comp.width) + " , " + str(comp.height))
        comp.location_from = Point(Dimension(0, "cm"), Dimension(0, "cm"))
        comp.location_to   = Point(comp.width, comp.height)
            
class ModelListener(dslListener):
    def __init__(self):
        pass

    def enterConstant(self, ctxt):
        #constant: 'const' ID '=' expr ';';
        name = str(ctxt.ID())
        expr = ctxt.expr()
        print("resolve constant: " + name)
        model.constants[name] = constant_fold_expr(expr)

    def add_pins(self, comp, props):
        for p in props:
            if p.pin_name() != None:
                for pin_name in p.pin_name().ID():
                    pin = comp.add_pin(str(pin_name))
                    for k in p.pin_prop():
                        pass


    def add_connections(self, mctxt, ctxt):
        for conn in ctxt.connection():
            for k in range(0, len(conn.access())-1):
                from_access = conn.access()[k]
                to_access   = conn.access()[k + 1]
                from_pin   = access_to_component_pin(from_access, mctxt, True)
                to_pin     = access_to_component_pin(to_access, mctxt, False)
                from_pin.add_connection(to_pin)            

    def enterNetwork(self, ctxt):
        names = ctxt.object_name().ID()        
        if len(names) == 1:            
            mctxt = ModelContext()
            self.add_connections(mctxt, ctxt)
        else:
            limit = str(names[2])
            count = model.constants[limit]
            for i in range(0, count):
                var = ModelVar(str(names[1]), i)
                mctxt = ModelContext()
                mctxt.add(var)
                self.add_connections(mctxt, ctxt)

    
    def enterComponent(self, ctxt):
        names = ctxt.object_name().ID()

        #print("EXAMINE COMPONENT: " + str(names))
        if len(names) == 1:
            comp = Component(str(names[0]))
            self.add_pins(comp, ctxt.component_property())
            model.components.append(comp)

            if ctxt.component_property() != None:
                for p in ctxt.component_property():
                    process_dimensions(comp, p.dim_prop())
                    process_location(comp, p.location_prop())
                    process_datasheet_prop(comp, p.datasheet_prop())
        else:
            limit = str(names[2])
            count = model.constants[limit]
            for i in range(0, count):
                comp = Component(str(names[0]) + COMPONENT_INDEX_STRING + str(i))
                self.add_pins(comp, ctxt.component_property())
                model.components.append(comp)

                if ctxt.component_property() != None:
                    for p in ctxt.component_property():
                        process_dimensions(comp, p.dim_prop())
                
            
def read_model(tree):
    ds = ModelListener()
    walker = ParseTreeWalker()
    walker.walk(ds, tree)

    model.writeDot("model.dot")
    model.writeSVG("model.svg")
    return model
