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

    def writeSVG(self, dwg):
        self.outline.writeSVG(dwg)
        
    def add_connection(self, to_pin):
        self.connections.append(to_pin)

    def setDescription(self, descr):
        self.description = descr
        
    def getDotID(self):
        return self.component.getDotID() +  "___PIN_" + str(self.id)

    def transpose(self, pos):
        self.outline.transpose(pos)

    def writeDotFile(self, fp):
        k = self.getDotID()
        fp.write(k + "[label=\""+self.name+"\"];\n")
        for c in self.connections:
            fp.write(k + " -- " + c.getDotID() + ";\n")




