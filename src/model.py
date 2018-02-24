from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from bs4 import BeautifulSoup
from antlr4 import *
import os
import sys
from datasheets import process_datasheet_prop

__uniq=0
constants={}
components = []
board = None

def find_component(name):
    for c in components:
        if c.name == name:
            return c
    print("ERROR: failed to find: " + name)
    failed_to_find_component()

def get_unique_id():
    global __uniq
    __uniq +=1 
    return __uniq
    
class Pin:
    def __init__(self, comp, name):
        self.name = name
        self.component = comp
        self.connections = []
        
    def add_connection(self, to_pin):
        self.connections.append(to_pin)
        
    def getDotID(self):
        return self.component.getDotID() +  "___PIN_" + self.name

    def writeDotFile(self, fp):
        k = self.getDotID()
        fp.write(k + "[label=\""+self.name+"\"];\n")
        for c in self.connections:
            fp.write(k + " -> " + c.getDotID() + ";\n")
    
class Component:
    def __init__(self, name):
        self.id = get_unique_id()
        self.name = name
        self.pkg_list = []
        self.table_list = []
        self.pins = []

    def add_pin(self, name):
        self.pins.append(Pin(self, name))


    def get_pin_by_name(self, name):
        for p in self.pins:
            print("PIN COMPARE: " + p.name + " VS " + name)
            if p.name == name:
                return p

        print("failed to find pin " + name + " in component " + self.name)
        not_found()

        
    def get_pin_by_suffixes(self, suffixes, context):
        s0 = suffixes[0]
        name = str(s0.ID())
        if s0.index() == None:
            return self.get_pin_by_name(name)
        else:
            return self.get_pin_by_name(context.indexed_pin_name(name, s0.index()))
    
    def getDotID(self):
        return "ID" + str(self.id)
        
    def writeDotFile(self, fp):
        k = self.getDotID()
        fp.write(k + "[label=\"" + self.name + "\"];\n")
        for p in self.pins:
            p.writeDotFile(fp)
            fp.write(k + " -> " + p.getDotID() + ";\n")
        
    def add_package(self, pkg):
        self.pkg_list.append(pkg)

    def add_table(self, table):
        self.table_list.append(table)

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



def setBoard(brd):
    board = brd


def getBoard():
    return board

def writeModelDot(filename):
    fp = open(filename, "w")
    fp.write("digraph model {\n")
    for c in components:
        c.writeDotFile(fp)
    fp.write("}");
    fp.close()


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
            return constants[name]
        
    comp = find_component(name)
    if comp != None:
        return comp.constant_fold(access.access_suffix())
    unimpl()

def constant_fold_primary(p):
    if p.expr() != None:
        return constant_fold_expr(p.expr())
    if p.access() != None:
        return constant_fold_access(p.access())
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
                return name + "$" + str(v.value)            
        not_found()

    def indexed_pin_name(self, name, index):
        for v in self.vars:
            print("EXAMINE " + v.name + " vs " + str(index.ID()))
            if v.name == str(index.ID()):
                return name + "" + str(v.value)
        print("ERRROR: failed to find " + str(index.ID()))
        not_found()

# access: ID index? access_suffix*
# 
# comp.P
# comp.P[x]
# comp[x].P
def access_to_component_pin(access, context):
    name = str(access.ID())
    if access.index() == None:
        # comp.P
        # comp.P[x]
        comp = find_component(name)
    else:
        comp = find_component(context.indexed_comp_name(name, access.index()))

    return comp.get_pin_by_suffixes(access.access_suffix(), context)

class ModelListener(dslListener):
    def __init__(self):
        pass

    def enterConstant(self, ctxt):
        #constant: 'const' ID '=' expr ';';
        name = str(ctxt.ID())
        expr = ctxt.expr()
        print("resolve constant: " + name)
        constants[name] = constant_fold_expr(expr)

    def add_pins(self, comp, props):
        for p in props:
            if p.pin_name() != None:
                for pin_name in p.pin_name().ID():
                    pin = comp.add_pin(str(pin_name))
                    for k in p.pin_prop():
                        pass

    def enterConnection(self, ctxt):
        names = ctxt.object_name().ID()        
        if len(names) == 1:
            unimpl()
        else:
            limit = str(names[2])
            count = constants[limit]
            for i in range(0, count):
                var = ModelVar(str(names[1]), i)
                mctxt = ModelContext()
                mctxt.add(var)
                
                from_access = ctxt.access()[0]
                to_access   = ctxt.access()[1]
                from_pin   = access_to_component_pin(from_access, mctxt)
                to_pin     = access_to_component_pin(to_access, mctxt)
                from_pin.add_connection(to_pin)
                

    def enterComponent(self, ctxt):
        names = ctxt.object_name().ID()
        
        if len(names) == 1:
            comp = Component(str(names[0]))
            self.add_pins(comp, ctxt.component_property())
            components.append(comp)

            if ctxt.component_property() != None:
                for p in ctxt.component_property():
                    process_datasheet_prop(comp, p.datasheet_prop())
        else:
            limit = str(names[2])
            count = constants[limit]
            for i in range(0, count):
                comp = Component(str(names[0]) + "$" + str(i))
                self.add_pins(comp, ctxt.component_property())
                components.append(comp)
                
            
def read_model(tree):
    ds = ModelListener()
    walker = ParseTreeWalker()
    walker.walk(ds, tree)

    writeModelDot("model.dot")
    return getBoard()
