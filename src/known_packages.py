from phys import Point


class KnownPackageInfo:
    def __init__(self, name, w, h, pin_len, pin_dist, pin_width, handler):
        self.name = name
        self.w = w
        self.h = h
        self.pin_len = pin_len
        self.pin_dist = pin_dist
        self.pin_width = pin_width
        self.handler = handler

    def create_outline(self, comp):
        self.handler(self, comp)

        
def create_common_box(config, comp):
    comp.width  = config.w
    comp.height = config.h
    pos = Point(0, 0, 0)
    end = pos.add(comp.width,
                  comp.height)
    comp.outline.addRect(pos,
                         end)
    print("created: " + str(comp.outline))
    return (pos, end)


def create_pins_RS28(config, comp):
    (pos, end) = create_common_box(config, comp)
    np = len(comp.pins)
    for ix in range(0, np):
        p = comp.pins[ix]
        
        #print("creating pin: " + str(p.name))
        
        mid = len(comp.pins)/2
        
        k = comp.height.mul(1.0/mid)
        starty = k.mul(0.25) #self.pin_dist.mul(0.5)
        if ix >= mid:
            x = comp.width
            y = starty.add(k.mul((np-1) - ix))
        else:
            #print(">>>> " + str(ix))
            x = config.pin_len.mul(-1)                
            y = starty.add(k.mul(ix))
            
        pos = Point(x, y, 0)
        end = pos.add(config.pin_len, config.pin_width)
        #print("creating pin: " + str(p.name) + ", at " + str(pos))
        
        p.outline.addRect(pos, end)


def create_single_row_pin_header(config, comp):
    comp.width  = config.w
    comp.height = config.h * len(comp.pins)
    pos = Point(0, 0, 0)
    end = pos.add(comp.width,
                  comp.height)
    comp.outline.addRect(pos,
                         end)
    np = len(comp.pins)
    for ix in range(0, np):
        p = comp.pins[ix]
        
        x = 0
        y = config.h * ix

        pos = Point(x, y, 0)
        end = pos.add(config.w, config.h)
        #print("creating pin: " + str(p.name) + ", at " + str(pos))
        
        p.outline.addRect(pos, end)

def create_two_row_pin_header(config, comp):
    comp.width  = config.w.mul(2)
    comp.height = config.h.mul(len(comp.pins)/2)
    pos = Point(0, 0, 0)
    end = pos.add(comp.width,
                  comp.height)
    comp.outline.addRect(pos,
                         end)
    np = len(comp.pins)
    for ix in range(0, np):
        p = comp.pins[ix]

        ix1 = (ix % 2)
        ix2 = int(ix / 2)        
        x = config.w.mul(ix1)
        y = config.h.mul(ix2)

        pos = Point(x, y, 0)
        end = pos.add(config.w, config.h)
        #print("creating pin: " + str(p.name) + ", at " + str(pos))
        
        p.outline.addRect(pos, end)
    

packages = [KnownPackageInfo("ground",            
                             2.35, # w
                             2.35, # h
                             0, 0, 0,
                             create_single_row_pin_header),
            KnownPackageInfo("SMD condensator",            
                             2.35, # w
                             2.35, # h
                             0, 0, 0,
                             create_single_row_pin_header),
            KnownPackageInfo("SMD resistor",            
                             2.35, # w
                             2.35, # h
                             0, 0, 0,
                             create_single_row_pin_header),
            KnownPackageInfo("single row pin header",            
                             2.35, # w
                             2.35, # h
                             0, 0, 0,
                             create_single_row_pin_header),
           KnownPackageInfo("two row pin header",            
                            2.35, # w
                            2.35, # h
                            0, 0, 0,
                            create_two_row_pin_header),
            KnownPackageInfo("RS-28",
                             5.38, # w
                             10.34, # h
                             1.26, # pin-len
                             0.65, # pin-dist
                             0.38,# pin-width
                             create_pins_RS28)] 


def findKnownPackage(name):
    for p in packages:
        if p.name == name:
            return p

    print("failed to find package '"+name+"' in database")
    failed_to_find_package()
