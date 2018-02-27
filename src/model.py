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


class Model:
    def __init__(self):
        self.constants  = {}
        self.components = []

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
        self.writeSVG("random_loc.svg")

                
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
