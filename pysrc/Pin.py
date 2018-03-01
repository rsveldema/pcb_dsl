from phys import Outline
from utils import get_unique_id,normalize,valid_pin_name


class Pin:
    def __init__(self, comp, name):
        self.mode = None
        self.outline = Outline(self)
        self.name = name
        self.component = comp
        self.connections = []
        self.description = ""
        self.id = get_unique_id()

    def sum_connection_lengths(self):
        sum = 0.0
        for other_pin in self.connections:
            sum += self.outline.distance(other_pin.outline)
        return sum

    
    def revector(self, from_pin, to_pin):
        for ix in range(0, len(self.connections)):
            p = self.connections[ix]
            if p == from_pin:
                self.connections[ix] = to_pin


    def shallow_clone(self, comp, map):
        c = Pin(comp, self.name)
        c.description = self.description
        c.mode = self.mode
        c.id = self.id
        c.outline = self.outline.deepclone(c, map)
        return c

    def deepclone(self, orig, map):
        #print("adding connections for " + str(len(orig.connections)))
        for p in orig.connections:
            new_comp = map[p.component]
            new_pin = new_comp.find_pin_by_id(p.id)
            self.connections.append(new_pin)

    def add_connection(self, to_pin):
        self.connections.append(to_pin)

    def setDescription(self, descr):
        self.description = descr
        
    def getDotID(self):
        return self.component.getDotID() +  "___PIN_" + str(self.id)

    def transpose(self, dir):
        self.outline.transpose(dir)

    def can_transpose(self, dir, mw, mh):
        return self.outline.can_transpose(dir, mw, mh)
        
    def writeSVG(self, dwg):
        self.outline.writeSVG(dwg)
        for c in self.connections:
            self.outline.drawLineSVG(dwg, c.outline)
                    
    def writeDotFile(self, fp):
        k = self.getDotID()
        fp.write(k + "[label=\""+self.name+"\"];\n")
        for c in self.connections:
            fp.write(k + " -- " + c.getDotID() + ";\n")



