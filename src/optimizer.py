from model import Model
import time
from phys import Dimension

POPULATION_SIZE_PLACEMENT = 1
POPULATION_SIZE_ROUTING   = 1



class Generation:
    def __init__(self):
        self.models = []

    def add(self, m):
        self.models.append(m)

    def optimize(self, iteration):
        for model in self.models:
            #(w,h) = model.get_board_size()
            w = Dimension(1, "cm")
            h = Dimension(1, "cm")
            model.random_move_components(w.div(iteration),
                                         h.div(iteration))

    def find_best(self):
        best = None
        for m in self.models:
            if m.is_better_than(best):
                best = m
        return best

class NestedGeneration:
    def __init__(self):
        self.nest = []

    def optimize(self, iteration):
        for p in self.nest:
            p.optimize(iteration)
    
    def add(self, p):
        self.nest.append(p)

    def find_best(self):
        best = None
        for k in self.nest:
            b = k.find_best()
            if b.is_better_than(best):
                best = b
        return best


def create_initial_generation(model):
    (w,h) = model.get_board_size()

    nested = NestedGeneration()
    for i in range(0, POPULATION_SIZE_PLACEMENT):
        random_placed = model.deepclone()
            
        for j in range(0, POPULATION_SIZE_ROUTING):
            inner = Generation()
            nested.add(inner)

            random_routed = random_placed.random_route()
            random_routed.random_move_components(w, h)
            inner.add(random_routed)

            random_routed.writeSVG("random_routed.svg")
    return nested

def optimize_model(model, time_limit_secs):
    print("creating initial population")
    nested = create_initial_generation(model)
    print("DONE: starting optimization process")

    iteration = 1
    old = now = time.time()
    end = now + time_limit_secs
    while now < end:
        nested.optimize(iteration)        
        now = time.time()
        if int(now) != int(old):            
            best = nested.find_best()
            if best != None:
                best.writeSVG("best-iteration-"+str(iteration)+".svg")
            else:
                print("no best found?")

            old = now
            print("left: " + str(int(end - now)) + " secs, done " + str(iteration))
        iteration += 1
        
    return nested.find_best()
