from model import Model
import time

POPULATION_SIZE_PLACEMENT = 100
POPULATION_SIZE_ROUTING   = 100


class Generation:
    def __init__(self):
        self.models = []

    def add(self, m):
        self.models.add(m)

    def optimize(self, iteration):
        for model in self.models:
            (w,h) = model.get_board_size()
            model.random_move_components(w.div(iteration), h.div(iteration))

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
    p = NestedGeneration()
    (w,h) = model.get_board_size()
    
    for i in range(0, POPULATION_SIZE_PLACEMENT):
        nested = NestedGeneration()

        random_placed = model.deepclone()
        random_placed.random_move_components(w, h)
            
        for j in range(0, POPULATION_SIZE_ROUTING):
            inner = Generation()
            nested.add(inner)

            random_routed = random_placed.random_route()
            inner.add(random_routed)
    return p

def optimize_model(model, time_limit_secs):
    nested = create_initial_generation(model)

    iteration = 0
    end = time.time() + time_limit_secs
    while now < end:
        nested.optimize(iteration)
        now = time.time()
        iteration += 1
        
    return nested.find_best()
