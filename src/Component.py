from phys import Outline,Dimension,Point
from utils import get_unique_id,normalize,valid_pin_name
from Pin import Pin

class KnownPackageInfo:
    def __init__(self, name, w, h, pin_len, pin_dist, pin_width):
        self.name = name
        self.w = w
        self.h = h
        self.pin_len = pin_len
        self.pin_dist = pin_dist
        self.pin_width = pin_width


    def create_pins_RS28(self, comp):
        np = len(comp.pins)
        for ix in range(0, np):
            p = comp.pins[ix]
            
            print("creating pin: " + str(p.name))

            mid = len(comp.pins)/2

            k = comp.height.mul(1.0/mid)
            starty = k.mul(0.25) #self.pin_dist.mul(0.5)
            if ix >= mid:
                x = comp.width
                y = starty.add(k.mul((np-1) - ix))
            else:
                print(">>>> " + str(ix))
                x = self.pin_len.mul(-1)                
                y = starty.add(k.mul(ix))
            
            pos = Point(x, y, 0)
            end = pos.add(self.pin_len, self.pin_width)
                          

            print("creating pin: " + str(p.name) + ", at " + str(pos))
            
            p.outline.addRect(pos, end)

    def create_outline(self, comp):
        comp.width  = self.w
        comp.height = self.h
        pos = Point(Dimension(0, "cm"),
                    Dimension(0, "cm"),
                    0)
        end = pos.add(comp.width,
                      comp.height)
        comp.outline.addRect(pos,
                             end)
        print("created: " + str(comp.outline))

        if self.name == "RS-28":
            self.create_pins_RS28(comp)
        else:
            unimplemented()

        

packages = [KnownPackageInfo("RS-28",
                             Dimension(5.38, "mm"), # w
                             Dimension(10.34, "mm"), # h
                             Dimension(1.26, "mm"), # pin-len
                             Dimension(0.65, "mm"), # pin-dist
                             Dimension(0.38, "mm"))] # pin-width


def findPackage(name):
    for p in packages:
        if p.name == name:
            return p
    failed_to_find_package()


class Component:
    def __init__(self, model, name):
        self.model = model
        self.fixed_position = None
        self.width = None
        self.height = None
        self.layers = None
        self.outline = Outline(self)
        self.id = get_unique_id()
        self.name = name
        self.pkg_list = []
        self.table_list = []
        self.pins = []


    def transpose(self, pos):
        self.outline.transpose(pos)
        for p in self.pins:
            p.transpose(pos)
        
    def create_outline(self, outline_type):
        p = findPackage(outline_type)
        p.create_outline(self)


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
        self.outline.writeSVG(dwg)
        for p in self.pins:
            p.writeSVG(dwg)
        
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

