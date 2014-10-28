# MODULE: ARINC_IMAServerQt
# COMPONENT: ARINC_IMAServerQt

# empty_component.py - sample code for a Simics configuration component
# Use this file as a skeleton for your own component implementations.

from comp import *

class ARINC_IMAServerQt(StandardConnectorComponent):
    """The empty component class."""
    _class_desc = "empty component"
    _help_categories = ()

    def setup(self):
        self.add_connector('pci_bus', PciBusUpConnector(0, 'afdxES'))
        afdxES = self.add_pre_obj('afdxES', 'afdxES')
        afdxES.middleware_mode = 3
        afdxES.CS_mode = 1              # server
        afdxES.ui_mode = 2
        
    def add_objects(self):
        self.add_connector('pci_bus', PciBusUpConnector(0, 'afdxES'))
        afdxES = self.add_pre_obj('afdxES', 'afdxES')

    class component_connector(Interface):
        def get_check_data(self, cnt):
            return []
        def get_connect_data(self, cnt):
            return [[[0, self._up.get_slot('afdxES')]]]
        def check(self, cnt, attr):
            return True
        def connect(self, cnt, attr):
            self._up.get_slot('afdxES').pci_bus = attr[1]
        def disconnect(self, cnt):
            self._up.get_slot('afdxES').pci_bus = None
