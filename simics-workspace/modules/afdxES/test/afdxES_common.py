import simics

# Extend this function if your device requires any additional attributes to be
# set. It is often sensible to make additional arguments to this function
# optional, and let the function create mock objects if needed.
def create_afdxES(name = None):
    '''Create a new afdxES object'''
    afdxES = simics.pre_conf_object(name, 'afdxES')
    simics.SIM_add_configuration([afdxES], None)
    return simics.SIM_get_object(afdxES.name)
