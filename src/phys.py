from svgwrite import cm, mm
from utils import ranged_random
import math

#svgwrite.rgb(10, 10, 16, '%')

def draw_line(dwg, from_pos, to_pos):
    x = from_pos.x * mm
    y = from_pos.y * mm
    ex = to_pos.x * mm
    ey = to_pos.y * mm
    layer = from_pos.layer
    dwg.add(dwg.line( (x,y), (ex, ey), 
                      stroke_width = "1",
                      stroke='green'))   


no_displayed_required = ["board"]


def grid(v):
    return int(v)


def can_add_without_clip(v1, v2, max):
    k = v1 + v2
    if k < 0:
        return False
    if k > max:
        return False
    return True


"""
   x/y of a point are of type int of unit 'mm'
"""
class Point:
    def __init__(self, x, y, layer):
        self.x = x
        self.y = y
        self.layer = layer

    def distance(self, other):
        x1 = self.x
        x2 = other.x
        
        y1 = self.y
        y2 = other.y

        dx = x2 - x1
        dy = y2 - y1

        return math.sqrt((dx*dx) + (dy*dy))

    def cap(self, startx, starty, endx, endy):
        self.x.cap(startx, endx)
        self.y.cap(starty, endy)
        
    def deepclone(self):
        return Point(self.x, self.y, self.layer)
        
    def add(self, x, y):
        return Point(self.x + x, self.y + y, self.layer)

    def sub(self, x, y):
        return Point(self.x - x, self.y - y, self.layer)

    def clip(self, mw, mh):
        return Point(self.x.clip(mw), self.y.clip(mh), self.layer)


    def clip_add(self, x, y, mw, mh):
        return Point(self.x.clip_add(x, mw), self.y.clip_add(y, mh), self.layer)

    def can_add_without_clip(self, x, y, mw, mh):
        return can_add_without_clip(self.x, x, mw) and can_add_without_clip(self.y, y, mh)
    
    def transpose(self, dir):
        return self.add(dir.x, dir.y)

    def can_transpose(self, dir, mw, mh):
        return self.can_add_without_clip(dir.x, dir.y, mw, mh)

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

    def can_transpose(self, pos, mw, mh):
        return self.f.can_transpose(pos, mw, mh) and self.t.can_transpose(pos, mw, mh)

    
    def transpose(self, dir):
        self.f = self.f.transpose(dir)
        self.t = self.t.transpose(dir)

    def __repr__(self):
        return "line(" + str(self.f) + " -> " + str(self.t) + ")"

class Outline:
    def __init__(self, parent):
        self.lines = []
        self.xparent = parent # either component or pin

        
    def distance(self, other):
        return self.center().distance(other.center())

    def deepclone(self, parent, map):
        c = Outline(parent)
        for p in self.lines:
            c.lines.append(p.deepclone())
        return c
        
    def transpose(self, dir):
        for p in self.lines:
            p.transpose(dir)

    def can_transpose(self, dir, mw, mh):
        for p in self.lines:
            if not p.can_transpose(dir, mw, mh):
                return False
        return True
            
    def addLayerLine(self, sx, sy, ex, ey):
        self.lines.append(LayerLine(Point(sx, sy, 0), Point(ex, ey, 0)))

    def addRect(self, s, e):
        self.addLayerLine(s.x, s.y, s.x, e.y)
        self.addLayerLine(s.x, s.y, e.x, s.y)
        self.addLayerLine(e.x, s.y, e.x, e.y)
        self.addLayerLine(s.x, e.y, e.x, e.y)

    
    def getRadius(self):
        radius = self.center().distance(self.lines[0].f)
        return radius

    def center(self):
        x = 0
        y = 0
        cnt = 0
        for p in self.lines:
            x += p.f.x
            y += p.f.y
            cnt += 1
            
            x += p.t.x
            y += p.t.y
            cnt += 1

        return Point(x / cnt, y / cnt, 0)
        
    # todo: create a better test later.
    def overlaps(self, f, t):
        radius = self.getRadius()
        c = self.center()
        fd = c.distance(f)
        td = c.distance(t)

        if fd < radius:
            return True

        if td < radius:
            return True

        return False
        
    def drawLineSVG(self, dwg, other):
        draw_line(dwg, self.center(), other.center())
        
    def writeSVG(self, dwg):
        #print("writing " + self.parent.name + " with " + str(len(self.lines)));
        for line in self.lines:
            draw_line(dwg, line.f, line.t)

        name = self.xparent.name
        if  name != None and not (name in no_displayed_required):
            c = self.lines[0].f #self.center()
            x = c.x * mm
            y = c.y * mm
            #print("pos["+name+"] = "  + str(x) + ","+str(y) + " ==> "+ self.parent.name + ", UL="+str(self.lines[0].f)+ "LL="+str(self.lines[0].t))
            
            dwg.add(dwg.text(name, (x,y),
                             stroke='red',
                             stroke_width = "0.1",
                             font_size="2px"))

    def __repr__(self):
        return str(self.lines)
