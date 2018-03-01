from model import Model
import time
from phys import Dimension
import random


POPULATION_NUM_GROUPS =  1
POPULATION_GROUP_SIZE = 10

SELECTION_FILTER_SIZE   = int(0.3 * POPULATION_GROUP_SIZE)
CROSSOVER_PROBABILITY   = int(0.8 * POPULATION_GROUP_SIZE)
MUTATION_PROBABILTY     = int(0.2 * POPULATION_GROUP_SIZE)


class Generation:
    def __init__(self, group_id):
        self.models = []
        self.group_id = group_id
        
    def add(self, m):
        self.models.append(m)

    def should_mutate(self):        
        k = random.randrange(0, POPULATION_GROUP_SIZE)
        if k < MUTATION_PROBABILTY:
            return True
        return False

    def should_crossover(self):
        k = random.randrange(0, POPULATION_GROUP_SIZE)
        if k < CROSSOVER_PROBABILITY:
            return True
        return False

    def change(self, iteration):
        for model in self.models:
            if self.should_mutate():
                (mw,mh) = model.get_board_size()
                w = Dimension(1.0, "cm")
                h = Dimension(1.0, "cm")
                model.random_move_components(w, h) #w.div(iteration), h.div(iteration))
            if self.should_crossover():
                k = random.randrange(0, len(self.models))
                other = self.models[k]
                if other != model:
                    model.crossover(other)

    def selection(self, iteration):
        scores = []
        for model in self.models:
            score = model.score()
            tuple = (score, model)
            scores.append( tuple )

        s = sorted(scores, key=lambda v : v[0])
        best = s[0:SELECTION_FILTER_SIZE]
        #print("picked "+ str(len(best)) + " of " + str(len(self.models)))
        self.models = []
        for p in best:
            self.models.append(p[1])
            
        for i in range(0,  POPULATION_GROUP_SIZE - len(best)):
            m = best[i % len(best)][1].deepclone()
            w = Dimension(0.5, "cm")
            h = Dimension(0.5, "cm")
            m.random_move_components(w, h) #w.div(iteration), h.div(iteration))
            self.models.append(m)

        best[0][1].writeSVG("group-best-" + str(iteration) + ".svg")

        
    def optimize(self, iteration):
        self.change(iteration)
        self.selection(iteration)
        
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

    random_placed = model.deepclone()
    random_routed = random_placed.place_routing_components(w, h)            
    random_routed.writeSVG("random_routed.svg")
                
    nested = NestedGeneration()
    for i in range(0, POPULATION_NUM_GROUPS):
        inner = Generation(i)
        nested.add(inner)
            
        for j in range(0, POPULATION_GROUP_SIZE):
            clone = random_routed.deepclone()
            clone.initial_random_move_components(w, h)
            inner.add(clone)
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
                pass
            else:
                print("no best found?")

            old = now
            print("left: " + str(int(end - now)) + " secs, done " + str(iteration))
        iteration += 1
        
    return nested.find_best()
