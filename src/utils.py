
__uniq=0

 
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

