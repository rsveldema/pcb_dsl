from phys import Outline,Dimension,Point
from utils import get_unique_id,normalize,valid_pin_name
from Pin import Pin
from known_packages import findKnownPackage

class Component:
    def __init__(self, model, name):
        self.model = model
        self.current_pos = Point(Dimension(0, "mm"), Dimension(0, "mm"), 0)
        self.fixed_position = None
        self.width = None
        self.height = None
        self.layers = None
        self.component_type = None
        self.outline = Outline(self)
        self.id = get_unique_id()
        self.name = name
        self.pkg_list = []
        self.table_list = []
        self.pins = []
        self.has_data_sheet = False


    def find_pin_by_id(self, id):
        for p in self.pins:
            if p.id == id:
                return p
        print("failed to find pin " + str(id))
        failed_to_find_pin();

    def shallow_clone(self, model, map):
        c = Component(model, self.name)

        c.fixed_position = self.fixed_position
        c.width = self.width
        c.height = self.height
        c.layers = self.layers
        c.component_type = self.component_type
        c.id = self.id
        c.pkg_list = self.pkg_list
        c.table_list = self.table_list
        c.has_data_sheet = self.has_data_sheet

        for p in self.pins:
            cloned_pin = p.shallow_clone(c, map)
            c.pins.append(cloned_pin)
            
        map[self] = c
        return c
        
    def deepclone(self, model, map):
        c = map[self]
        for ix in range(0, len(self.pins)):
            orig = self.pins[ix]
            clone = c.pins[ix]
            clone.deepclone(orig, map)
        c.outline = self.outline.deepclone(self, map)
        
        
    def resolve_length(self, name):
        if name == "pins":
            return len(self.pins)
        unknown_constant_fold()
        
    def transpose(self, pos):
        self.current_pos = self.current_pos.transpose(pos)
        self.outline.transpose(pos)
        for p in self.pins:
            p.transpose(pos)
        
    def create_outline(self):
        p = findKnownPackage(self.component_type)
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

