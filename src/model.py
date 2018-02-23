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

def findComponent(name):
    for c in components:
        if c.name == name:
            return c
    failed_to_find_component()

def get_unique_id():
    global __uniq
    __uniq +=1 
    return __uniq
    
class Connection:    
    def __init__(self, comp):
        self.component = comp


class Component:
    def __init__(self, name):
        self.id = get_unique_id()
        self.name = name
        self.connections = []

    def addRef(self, comp):
        self.connections.append(Connection(comp))

    def writeDotFile(self, fp):
        fp.write("ID" + str(self.id) + "[label=\"" + self.name + "\"];\n")

    def constant_fold(self, names):
        return 10
        

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


def constant_fold_access(access):
    names = access.ID()
    indices = access.index()
    name = str(names[0])
    if len(names) == 1 and len(indices) == 0:
        return constants[name]
    comp = findComponent(name)
    if comp != None:
        return comp.constant_fold(names[1:]);
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

class ModelListener(dslListener):
    def __init__(self):
        pass

    def enterConstant(self, ctxt):
        #constant: 'const' ID '=' expr ';';
        name = str(ctxt.ID())
        expr = ctxt.expr()
        print("resolve constant: " + name)
        constants[name] = constant_fold_expr(expr)


    def enterComponent(self, ctxt):
        names = ctxt.object_name().ID()

        if len(names) == 1:
            comp = Component(str(names[0]))
            components.append(comp)

            if ctxt.component_property() != None:
                for p in ctxt.component_property():
                    process_datasheet_prop(comp, p.datasheet_prop())
        else:
            limit = str(names[2])
            count = constants[limit]
            for i in range(0, count):
                comp = Component(str(names[0]))
                components.append(comp)
                
            
def read_model(tree):
    ds = ModelListener()
    walker = ParseTreeWalker()
    walker.walk(ds, tree)

    writeModelDot("model.dot")
    return getBoard()
