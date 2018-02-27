from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from bs4 import BeautifulSoup
from antlr4 import *
import os
import sys
import svgwrite
from Component import Component
from phys import Outline,Point,Dimension
from utils import get_unique_id

def get_new_routing_name():
    return "route_" + str(get_unique_id())


class Model:
    def __init__(self):
        self.constants  = {}
        self.components = []
        self.num_bends_per_route = 3
        self.WIRE_WIDTH = Dimension(0.1, "mm")

    def create_router(self):
        print("creating router")
        comp = Component(self, get_new_routing_name(), True)
        comp.type = "router"
        comp.width  = self.WIRE_WIDTH
        comp.height = self.WIRE_WIDTH
        self.components.append(comp)
        pin = comp.add_pin("x")

        s = Point(Dimension(0, "mm"),
                  Dimension(0, "mm"),
                  0)

        e = Point(comp.width,
                  comp.height,
                  0)

        comp.outline.addRect(s, e)
        pin.outline.addRect(s, e)
        return comp
        
    # move components in the given range
    def random_move_components(self, w, h):
        (mw,mh) = self.get_board_size()
        for p in self.components:
            if p.fixed_position == None:
                dir = p.current_pos.add(w.random(), h.random())
                dir.cap(Dimension(0, "mm"),
                        Dimension(0, "mm"),
                        mw, mh)
                p.transpose(dir)
                #p.rotate()


    def do_random_route(self):
        for c in self.components:
            if not c.is_router:
                c.random_route(self)
        
    def random_route(self):
        p = self.deepclone()
        p.do_random_route()
        return p

                
    def get_board_size(self):
        p = self.find_component("board")
        return (p.width, p.height)

    def deepclone(self):
        m = Model()
        m.constants = self.constants

        map = {}
        for comp in self.components:
            c = comp.shallow_clone(m, map)
            m.components.append(c)
        
        for comp in self.components:
            comp.deepclone(m, map)
        return m

    def find_component(self, name):
        for c in self.components:
            if c.name == name:
                return c
        print("ERROR: failed to find: " + name)
        failed_to_find_component()

    def writeSVG(self, filename):
        dwg = svgwrite.Drawing(filename, profile='tiny')
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

    def is_better_than(m):
        if m == None:
            return True
        return False
