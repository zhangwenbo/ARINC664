import simics

# Extend this function if your device requires any additional attributes to be
# set. It is often sensible to make additional arguments to this function
# optional, and let the function create mock objects if needed.
def create_rtc_module(name = None):
    '''Create a new rtc_module object'''
    rtc_module = simics.pre_conf_object(name, 'rtc_module')
    simics.SIM_add_configuration([rtc_module], None)
    return simics.SIM_get_object(rtc_module.name)
