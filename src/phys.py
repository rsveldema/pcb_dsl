from svgwrite import cm, mm
from utils import ranged_random
import math

#svgwrite.rgb(10, 10, 16, '%')

def draw_line(dwg, from_pos, to_pos):
    x = from_pos.x.svg()
    y = from_pos.y.svg()
    ex = to_pos.x.svg()
    ey = to_pos.y.svg()
    layer=from_pos.layer
    dwg.add(dwg.line( (x,y), (ex, ey), 
                      stroke_width = "1",
                      stroke='green'))   


no_displayed_required = ["board"]


"""
   x/y of a point are of type Dimension
"""
class Point:
    def __init__(self, x, y, layer):
        self.x = x.deepclone()
        self.y = y.deepclone()
        self.layer = layer

    def distance(self, other):
        x1 = self.x.asMM()
        x2 = other.x.asMM()
        
        y1 = self.y.asMM()
        y2 = other.y.asMM()

        dx = x2 - x1
        dy = y2 - y1

        return math.sqrt((dx*dx) + (dy*dy))

    def cap(self, startx, starty, endx, endy):
        self.x.cap(startx, endx)
        self.y.cap(starty, endy)
        
    def deepclone(self):
        return Point(self.x.deepclone(), self.y.deepclone(), self.layer)
        
    def add(self, x, y):
        return Point(self.x.add(x), self.y.add(y), self.layer)

    def sub(self, x, y):
        return Point(self.x.sub(x), self.y.sub(y), self.layer)

    def clip(self, mw, mh):
        return Point(self.x.clip(mw), self.y.clip(mh), self.layer)


    def clip_add(self, x, y, mw, mh):
        return Point(self.x.clip_add(x, mw), self.y.clip_add(y, mh), self.layer)
    
    def transpose(self, pos, mw, mh):
        return self.clip_add(pos.x, pos.y, mw, mh)

    def average(self, pt):
        return Point(self.x.average(pt.x),
                     self.y.average(pt.y),
                     self.layer)

    def __repr__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"


class LayerLine:
    def __init__(self, f, t):
        self.f = f.deepclone();
        self.t = t.deepclone();

    def deepclone(self):
        return LayerLine(self.f.deepclone(), self.t.deepclone())

    def transpose(self, pos, mw, mh):
        self.f = self.f.transpose(pos, mw, mh)
        self.t = self.t.transpose(pos, mw, mh)

    def __repr__(self):
        return "line(" + str(self.f) + " -> " + str(self.t) + ")"

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

    
    def cap(self, s, e):
        if self.asMM() < s.asMM():
            self.value = s.asMM()
            self.unit = "mm"
        if self.asMM() > e.asMM():
            self.value = e.asMM()
            self.unit = "mm"
            
    def random(self):
        v = self.asMM()
        return Dimension(ranged_random(-int(v), int(v)), "mm")

    def abs_random(self):
        v = self.asMM()
        return Dimension(ranged_random(0, int(v)), "mm") 
            
    def deepclone(self):
        return Dimension(self.value, self.unit)

    def constant_fold(self, op, count):
        if op == "*":
            return self.mul(count)
        if op == "/":
            return self.mul(1.0/count)
        unknown()
            
    def asMM(self):
        if self.unit == "mm":
            return self.value
        elif self.unit == "cm":
            return self.value * 10.0
        print("don't know unit: " + self.unit)
        unimplemented()
        
    def asCM(self):
        if self.unit == "mm":
            return self.value / 10.0
        elif self.unit == "cm":
            return self.value
        print("don't know unit: " + self.unit)
        unimplemented()        

    def average(self, value):
        return Dimension((self.asMM() + value.asMM()) / 2.0, "mm")
        
    def add(self, value):
        return Dimension(self.asMM() + value.asMM(), "mm")


    def sub(self, value):
        return Dimension(self.asMM() - value.asMM(), "mm")

    def clip_add(self, value, mv):
        k = self.asMM() + value.asMM()
        if k < 0:
            k = 0
        elif mv != None:
            m = mv.asMM()
            if k > m:
                k = m
        
        return Dimension(k, "mm")

    def clip(self, value):
        if value == None:
            return self
        
        if self.value < 0:
            return Dimension(0, "mm")

        if self.asMM() > value.asMM():
            return value
        return self

    
    def mul(self, value):
        return Dimension(self.asMM() * value, "mm")

    def div(self, value):
        return Dimension(self.asMM() / value, "mm")

    def svg(self):
        if self.unit == "mm":
            return self.value * mm
        if self.unit == "cm":
            return self.value * cm
        print("unknown unit for svg: " + self.unit)
        error()


    def __repr__(self):
        return str(self.value) + self.unit
        


class Outline:
    def __init__(self, parent):
        self.lines = []
        self.parent = parent # either component or pin
        self.center = None
        
    def distance(self, other):
        return self.center.distance(other.center)

    def deepclone(self, parent, map):
        c = Outline(parent)
        c.center = self.center
        for p in self.lines:
            c.lines.append(p.deepclone())
        return c
        
    def transpose(self, pos, mw, mh):
        for p in self.lines:
            p.transpose(pos, mw, mh)
        if self.center != None:
            self.center = self.center.transpose(pos, mw, mh)

    def addLayerLine(self, sx, sy, ex, ey):
        self.lines.append(LayerLine(Point(sx, sy, 0), Point(ex, ey, 0)))

    def addRect(self, s, e):
        self.addLayerLine(s.x, s.y, s.x, e.y)
        self.addLayerLine(s.x, s.y, e.x, s.y)
        self.addLayerLine(e.x, s.y, e.x, e.y)
        self.addLayerLine(s.x, e.y, e.x, e.y)
        self.center = s.average(e)

    # todo: create a better test later.
    def overlaps(self, f, t):
        radius = self.center.distance(self.lines[0].f)
        fd = self.center.distance(f)
        td = self.center.distance(t)

        if fd < radius:
            return True

        if td < radius:
            return True

        return False
        
    def drawLineSVG(self, dwg, other):
        draw_line(dwg, self.center, other.center)
        
    def writeSVG(self, dwg):
        #print("writing " + self.parent.name + " with " + str(len(self.lines)));
        for line in self.lines:
            draw_line(dwg, line.f, line.t)

        name = self.parent.name
        if self.center != None and name != None and not (name in no_displayed_required):
            x = self.center.x.svg()
            y = self.center.y.svg()
            #print("pos = "  + str(x) + ","+str(y) + " ==> "+ self.parent.name)
            
            dwg.add(dwg.text(str(name), (x,y),
                             stroke='red',
                             stroke_width = "0.1",
                             font_size="2px"))

    def __repr__(self):
        return str(self.lines)
