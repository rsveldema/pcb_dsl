from phys import Outline,Dimension
from utils import get_unique_id,normalize,valid_pin_name
from Pin import Pin

class PackageInfo:
    def __init__(self, name, w, h, pin_len):
        self.name = name
        self.w = w
        self.h = h
        self.pin_len = pin_len

packages = [PackageInfo("RS-28",
                        Dimension(5.38, "mm"),
                        Dimension(10.34, "mm"),
                        Dimension(1.26, "mm"))]


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


    def create_outline(self, outline_type):
        p = findPackage(outline_type)
        self.width = p.w
        self.height = p.h

        if self.fixed_position != None:
            self.outline.addRect(self.fixed_position, self.fixed_position.add(self.width, self.height))
            print("outline =============> " + str(self.outline))
        else:
            print("outline =============> NO FIXED POS")


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

