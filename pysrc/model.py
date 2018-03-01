from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from bs4 import BeautifulSoup
from antlr4 import *
import os
import sys
import random
import svgwrite
from Component import Component
from phys import Outline,Point
from utils import get_unique_id

def get_new_routing_name():
    return "route_" + str(get_unique_id())

def abs_random(max):
    return random.randrange(0, max)

def nat_random(max):
    return random.randrange(-max, max)

class Model:
    def __init__(self):
        self.constants  = {}
        self.components = []
        self.WIRE_WIDTH = 0.1

    def create_router(self):
        #print("creating router")
        comp = Component(self, get_new_routing_name(), True)
        comp.type = "router"
        comp.width  = self.WIRE_WIDTH
        comp.height = self.WIRE_WIDTH
        self.components.append(comp)
        pin_in  = comp.add_pin("in")
        pin_out = comp.add_pin("out")

        s = Point(0, 0, 0)
        e = s.add(comp.width,
                  comp.height)

        comp.outline.addRect(s, e)
        pin_in.outline.addRect(s, e)
        pin_out.outline.addRect(s, e)
        return comp

    
    def crossover(self, other):
        size = len(self.components)
        ix = random.randrange(0, size)

        c1 = self.components[ix]
        c2 = other.components[ix]

        assert c1.id == c2.id
        assert c1.name == c2.name
        
        c1.crossover(c2)

        
    # move components in the given range
    def random_move_components(self, w, h):
        (mw,mh) = self.get_board_size()
        for comp in self.components:
            if comp.fixed_position == None:
                dir = Point(nat_random(w), nat_random(h), comp.layers)
                #print("DIR TO PLACE: " + str(dir) + "  where comp ["+comp.name+"] at " + str(comp.outline.center))
                if comp.can_transpose(dir, mw, mh):
                    comp.transpose(dir)
                    #comp.rotate()

    # move components in the given range
    def initial_random_move_components(self, w, h):
        (mw,mh) = self.get_board_size()
        for comp in self.components:
            if comp.fixed_position == None:
                dir = Point(abs_random(w), abs_random(h), comp.layers)
                print("INITIAL_DIR TO PLACE: " + str(dir) + "  where comp [" + comp.name+"] at " + str(comp.outline.center()))
                if comp.can_transpose(dir, mw, mh):
                    comp.transpose(dir)
                    #comp.rotate()


    def do_place_routing_components(self, mw, mh):
        for c in self.components:
            if not c.is_router:
                c.place_routing_components(self, mw, mh)
        
    def place_routing_components(self, mw, mh):
        p = self.deepclone()
        p.do_place_routing_components(mw, mh)
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

    def sum_connection_lengths(self):
        sum = 0.0
        for c in self.components:
            sum += c.sum_connection_lengths()
        return sum

    def count_overlaps(self):
        c = 0
        for p1 in self.components:
            if p1.is_board:
                continue
            for p2 in self.components:
                if p2.is_board:
                    continue
                if p1 != p2:
                    d = p1.outline.distance(p2.outline)
                    radius = p1.outline.getRadius()
                    if d < radius:
                        print("overlap of " + str(p1.name) + " with " + str(p2.name) + " --- " + str(d) + " radius = " + str(radius))
                        c += 1
        return c


    # the lower the better
    def score(self):
        my_num_overlaps    = self.count_overlaps()
        my_len     =  self.sum_connection_lengths()
        s = (my_num_overlaps * 100) + (my_len * 2)
        return s
        
    def is_better_than(self, other):
        if other == None:
            return True

        s1 = self.score()
        s2 = other.score()
        return s1 < s2