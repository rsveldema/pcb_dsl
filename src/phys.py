from svgwrite import cm, mm


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

    def deepclone(self):
        return Point(self.x.deepclone(), self.y.deepclone(), self.layer)
        
    def add(self, x, y):
        return Point(self.x.add(x), self.y.add(y), self.layer)
        
    def transpose(self, pos):
        return Point(self.x.add(pos.x),
                     self.y.add(pos.y),
                     self.layer)

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

    def transpose(self, pos):
        self.f = self.f.transpose(pos)
        self.t = self.t.transpose(pos)

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

    def mul(self, value):
        return Dimension(self.asMM() * value, "mm")
        
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
        
    def transpose(self, pos):
        for p in self.lines:
            p.transpose(pos)
        if self.center != None:
            self.center = self.center.transpose(pos)

    def addLayerLine(self, sx, sy, ex, ey):
        self.lines.append(LayerLine(Point(sx, sy, 0), Point(ex, ey, 0)))

    def addRect(self, s, e):
        self.addLayerLine(s.x, s.y, s.x, e.y)
        self.addLayerLine(s.x, s.y, e.x, s.y)
        self.addLayerLine(e.x, s.y, e.x, e.y)
        self.addLayerLine(s.x, e.y, e.x, e.y)
        self.center = s.average(e)

        
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
