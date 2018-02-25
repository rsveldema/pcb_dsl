from svgwrite import cm, mm


#svgwrite.rgb(10, 10, 16, '%')

def draw_line(dwg, from_pos, to_pos):
    x = from_pos.x.svg()
    y = from_pos.y.svg()
    ex = to_pos.x.svg()
    ey = to_pos.y.svg()
    layer=from_pos.layer
    dwg.add(dwg.line( (x,y), (ex, ey), stroke='green'))   




"""
   x/y of a point are of type Dimension
"""
class Point:
    def __init__(self, x, y, layer):
        self.x = x;
        self.y = y
        self.layer = layer

    def clone(self):
        return Point(self.x.clone(), self.y.clone(), self.layer)
        
    def add(self, x, y):
        self.x.add(x)
        self.y.add(y)

class LayerLine:
    def __init__(self, f, t):
        self.f = f;
        self.t = t;

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

    def clone(self):
        return Dimension(self.value, self.unit)
            
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
            
    def add(self, value):
        if self.unit == "mm":
            self.value += value.asMM()
        elif self.unit == "cm":
            self.value += value.asCM()
        else:
            print("don't know unit: " + self.unit)
            unimplemented();
            
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
    def __init__(self, comp):
        self.lines = []
        self.comp = comp

    def addLayerLine(self, sx, sy, ex, ey):
        self.lines.append(LayerLine(Point(sx, sy, 0), Point(ex, ey, 0)))

    def addRect(self, s, e):
        self.addLayerLine(s.x, s.y, s.x, e.y)
        self.addLayerLine(s.x, s.y, e.x, s.y)
        self.addLayerLine(e.x, s.y, e.x, e.y)
        self.addLayerLine(s.x, e.y, e.x, e.y)
        
    def writeSVG(self, dwg):
        #print("writing " + self.comp.name + " with " + str(len(self.lines)));
        for line in self.lines:
            draw_line(dwg, line.f, line.t)

    def __repr__(self):
        return str(self.lines)
