from dslListener import dslListener
from antlr4 import *
from utils import destringify
from model import Model,Component
from phys import Dimension,Point
from datasheets import process_datasheet_prop
from known_packages import findKnownPackage

COMPONENT_INDEX_STRING=""

"""
    access_suffix: ('.' ID index?)
"""
def constant_fold_field(comp, access_suffixes):
    name0 = str(access_suffixes[0].ID())
    name1 = str(access_suffixes[1].ID())
    
    #print("constant fold in component " + str(names) + ", list = " + str(self.table_list))
    table = comp.find_table(name0)
    row = table.find_row_by_key(name1)
    value = int(row.get(1).string)
    print("PDF TABLE LOOKUP["+name0+"."+name1+"] = " + str(value))
    return value


"""
access: ID index? access_suffix*
access_suffix: ('.' ID index?)
"""
def constant_fold_access(model, access):
    name  = str(access.ID())
    if len(access.access_suffix()) == 0:
        if access.index() == None:
            return model.constants[name]
        
    comp = model.find_component(name)
    if comp != None:
        return constant_fold_field(comp, access.access_suffix())
    unimpl()


def constant_fold_primary(model, p):
    if p.length != None:
        name = str(p.ID())
        return model.current_component.resolve_length(name)
        
    if p.expr() != None:
        return constant_fold_expr(p.expr())
    if p.access() != None:
        return constant_fold_access(model, p.access())
    if p.unit != None:
        return Dimension(p.n, p.unit())
    print("unrecognized primary expr: " + str(p))
    unimpl()

def constant_fold_expr(model, expr):
    p = expr.primary()
    left = constant_fold_primary(model, p[0])
        
    if len(p) == 1:
        return left
    else:
        right = constant_fold_primary(model, p[1])        
        operand = expr.op().operand.text;
        return right.constant_fold(operand, left)


class ModelVar:
    def __init__(self, name, value):
        self.name = name
        self.value = value


class ModelContext:
    def __init__(self):
        self.vars = []

    def add(self, var):
        self.vars.append(var)

    def indexed_comp_name(self, name, index):
        for v in self.vars:
            if v.name == str(index.ID()):
                return name + COMPONENT_INDEX_STRING + str(v.value)            
        not_found()

    def indexed_pin_name(self, name, index):
        for v in self.vars:
            #print("EXAMINE " + v.name + " vs " + str(index.ID()))
            if v.name == str(index.ID()):
                return name + "" + str(v.value)
        print("ERRROR: failed to find " + str(index.ID()))
        not_found()

# access: ID index? access_suffix*
# 
# comp.P
# comp.P[x]
# comp[x].P
def access_to_component_pin(model, access, context, odd):
    name = str(access.ID())
    if access.index() != None:
        name = context.indexed_comp_name(name, access.index())

    comp = model.find_component(name)
    return comp.get_pin_by_suffixes(access.access_suffix(), context, odd)


def process_location(comp, loc_prop_list):
    model = comp.model
    for loc in loc_prop_list:
        # AT:
        model.current_component = comp
        sx = constant_fold_expr(model, loc.expr()[0])
        sy = constant_fold_expr(model, loc.expr()[1])

        comp.current_position = comp.fixed_position = Point(sx, sy, 0)        
        comp.transpose(None, comp.fixed_position, None, None)
        
        
def process_dimensions(comp, dim_prop_list):
    model = comp.model
    model.current_component = comp
    for dim in dim_prop_list:
        if dim.width != None:
            comp.width = constant_fold_expr(model, dim.width)
        if dim.height != None:
            comp.height = constant_fold_expr(model, dim.height)
        if dim.layers != None:
            comp.layers = constant_fold_expr(model, dim.layers)

    if not comp.has_data_sheet:
        sx = Dimension(0, "cm")
        sy = Dimension(0, "cm")
        if comp.component_type != None:
            pkg = findKnownPackage(comp.component_type)
            pkg.create_outline(comp)
        else:
            print("COMPONENT "+ comp.name + " has no assigned type yet")
            comp.outline.addRect(Point(sx, sy, comp.layers),
                                 Point(comp.width, comp.height, comp.layers))



def add_dimensions(comp, ctxt):
    if ctxt.component_property() != None:
        for p in ctxt.component_property():                    
            process_dimensions(comp, p.dim_prop())

            
def add_location(comp, ctxt):
    if ctxt.component_property() != None:
        for p in ctxt.component_property():                    
            process_location(comp, p.location_prop())
            
def add_datasheet_props(comp, ctxt):
    if ctxt.component_property() != None:
        for p in ctxt.component_property():                    
            process_datasheet_prop(comp, p.datasheet_prop())

def preprocess_component(model, comp, props):
    if comp.name == "board":
        comp.fixed_position = Point(Dimension(0, "mm"),
                                    Dimension(0, "mm"),
                                    0)
    
    model.current_component = comp
    for p in props:
        if len(p.datasheet_prop()) > 0:
            comp.has_data_sheet = True
        if p.component_type != None:
            comp.component_type = destringify(p.component_type.text)
            #print("SAW COMPONENT TYPE: "+ comp.component_type)
            
    for p in props:
        if p.pin_name() != None:
            for pin_name in p.pin_name().ID():
                pin = comp.add_pin(str(pin_name))
                for k in p.pin_prop():
                    pin.mode = k.pinmode
                        


            
class ModelListener(dslListener):
    def __init__(self, model):
        self.model = model

    def enterConstant(self, ctxt):
        #constant: 'const' ID '=' expr ';';
        name = str(ctxt.ID())
        expr = ctxt.expr()
        print("resolve constant: " + name)
        self.model.constants[name] = constant_fold_expr(self.model, expr)

    def add_connections(self, mctxt, ctxt):
        for conn in ctxt.connection():
            for k in range(0, len(conn.access())-1):
                from_access = conn.access()[k]
                to_access   = conn.access()[k + 1]
                from_pin   = access_to_component_pin(self.model, from_access, mctxt, True)
                to_pin     = access_to_component_pin(self.model, to_access, mctxt, False)
                from_pin.add_connection(to_pin)            

    def enterNetwork(self, ctxt):
        names = ctxt.object_name().ID()        
        if len(names) == 1:            
            mctxt = ModelContext()
            self.add_connections(mctxt, ctxt)
        else:
            limit = str(names[2])
            count = self.model.constants[limit]
            for i in range(0, count):
                var = ModelVar(str(names[1]), i)
                mctxt = ModelContext()
                mctxt.add(var)
                self.add_connections(mctxt, ctxt)

    
    def enterComponent(self, ctxt):
        names = ctxt.object_name().ID()
        #print("EXAMINE COMPONENT: " + str(names))
        if len(names) == 1:
            comp = Component(self.model, str(names[0]), False)
            preprocess_component(self.model, comp, ctxt.component_property())
            self.model.components.append(comp)

            add_dimensions(comp, ctxt)
            add_datasheet_props(comp, ctxt)
            add_location(comp, ctxt)            
        else:
            limit = str(names[2])
            count = self.model.constants[limit]
            for i in range(0, count):
                comp = Component(self.model, str(names[0]) + COMPONENT_INDEX_STRING + str(i), False)
                preprocess_component(self.model, comp, ctxt.component_property())
                self.model.components.append(comp)

                if ctxt.component_property() != None:
                    for p in ctxt.component_property():
                        process_dimensions(comp, p.dim_prop())
                
            
def read_model(tree):
    model = Model()
    ds = ModelListener(model)
    walker = ParseTreeWalker()
    walker.walk(ds, tree)
    return model
