import random

__uniq=0

""" 
Return a random value from min...max
For example, from -123 to +42
"""
def ranged_random(min, max):
    return random.randrange(min, max)

def destringify(s):
    #print("string ----- " + s)
    assert s[0] == '"'
    assert s[len(s)-1] == '"'
    return s[1:len(s)-1]

def normalize(s):
    s = s.replace('-', '_')
    s = s.replace(' ', '_')
    return s

def valid_pin_name(name):
    if name == "Name":
        return False
    return True

def get_unique_id():
    global __uniq
    __uniq +=1 
    return __uniq

