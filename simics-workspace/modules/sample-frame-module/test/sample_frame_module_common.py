import simics

# Extend this function if your device requires any additional attributes to be
# set. It is often sensible to make additional arguments to this function
# optional, and let the function create mock objects if needed.
def create_sample_frame_module(name = None):
    '''Create a new sample_frame_module object'''
    sample_frame_module = simics.pre_conf_object(name, 'sample_frame_module')
    simics.SIM_add_configuration([sample_frame_module], None)
    return simics.SIM_get_object(sample_frame_module.name)
