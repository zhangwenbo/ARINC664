# MODULE: ARINC-664MonitorMode
# COMPONENT: ARINC_664MonitorMode

# empty_component.py - sample code for a Simics configuration component
# Use this file as a skeleton for your own component implementations.

from comp import *

class ARINC_664MonitorMode(StandardConnectorComponent):
    """The empty component class."""
    _class_desc = "empty component"
    _help_categories = ()

    def setup(self):
        StandardConnectorComponent.setup(self)
        if not self.instantiated.val:
            self.add_objects()

    def add_objects(self):
        self.add_connector('pci_bus', PciBusUpConnector(0, 'afdxES'))
        afdxES = self.add_pre_obj('afdxES', 'afdxES')
        afdxES.middleware_mode = 2
        sample_frame_module = self.add_pre_obj('sample_frame_module', 'sample_frame_module')
        afdxES.sample_frame_module = sample_frame_module
        afdxES.enable_sample_frame = True

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
