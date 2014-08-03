import simics

# Extend this function if your device requires any additional attributes to be
# set. It is often sensible to make additional arguments to this function
# optional, and let the function create mock objects if needed.
def create_afdxES2(name = None):
    '''Create a new afdxES2 object'''
    afdxES2 = simics.pre_conf_object(name, 'afdxES2')
    simics.SIM_add_configuration([afdxES2], None)
    return simics.SIM_get_object(afdxES2.name)
