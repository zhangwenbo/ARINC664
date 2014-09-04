# empty_python_device.py - sample code for a Simics device

# Use this file as a skeleton for your own device implementation in Python.

# MODULE: hwa-mv64560-comp
# CLASS: board_mv64560

import configuration
from comp import *
from flash_memory import *
from mod_discovery_v_comp import *

# def for mv64560
class board_mv64560(discovery_v_sc):
    """Marvell DB64560 evaluation board with 64560 system controller."""
    _class_desc = "Marvell DB64560 evaluation board"
    _help_categories = ()

    class basename(StandardConnectorComponent.basename):
        val = "db64560"

    class top_level(StandardConnectorComponent.top_level):
        def _initialize(self):
            self.val = True

    class cpu_list(StandardConnectorComponent.cpu_list):
        def getter(self):
            if sim_commands.get_writing_template() or not self._up.instantiated.val:
                return []
            cpus = self._up.get_slot('MV64560').cpus
            return [cpu for cpu in cpus if cpu != None]

    def setup(self):
        StandardConnectorComponent.setup(self)
        if not self.instantiated.val:
            self.add_objects()
        self.add_connectors()

    def add_connectors(self):
        # CPU
        self.add_connector('cpu', SystemDownConnector(
                            0, 'MV64560', required=True))

        # UART
        self.add_slot('uart', [self.add_connector(
                       None, SerialDownConnector('MV64560_uart[%d]' % i))
                               for i in xrange(2)])

        # PCI slot
        self.add_slot('pci_slot', [self.add_connector(
                       None, PciBusDownConnector(i + 1, 'pci_bus[0]'))
                                   for i in xrange(2)])

        # DDR DIMM
        self.add_slot('ddr_slot', [self.add_connector(
                       None, MemBusDownConnector('i2c_bus', (0x56, 0x54)[i],
                       (self.connect_mem_bus1, self.connect_mem_bus2)[i], False))
                       for i in xrange(2)])

        # ETH
        self.add_slot('eth', [self.add_connector(
                       None, EthernetLinkDownConnector('phy[%d]' % i))
                                for i in xrange(3)])

    def add_objects(self):
        discovery_v_sc.add_objects(self, sc_type='MV64560',
                                   pci_bus_count=2)

        mv64560 = self.get_slot('MV64560')
        mv64560_nand = self.get_slot('MV64560_nand')
        mii_bus = self.get_slot('mii_bus')

        # Device CS 0
        led_swt = self.add_pre_obj('sbc74xx_led_swt', 'sbc74xx-led-swt')
        lw_space = self.add_pre_obj('lw_space', 'memory-space')
        lw_space.map = [[0x0, led_swt, 0, 0, 0x100000]]
        mv64560.DevCS_0 = lw_space

        #kkkk reset PCI_1_MEM3 0x9800_0000 -> 0x5c00_0000
        mv64560.regs_CPU_Decode_PCI_1_Memory_3_base = 0x5c00
        mv64560.regs_CPU_Decode_PCI_1_Memory_3_size = 0x03ff
        
        # set MV64560 register before instantiate
        mv64560.regs_CPU_Decode_DevCS_1_base =0x9800
        mv64560.regs_CPU_Decode_DevCS_1_size = 0x7ff

        # Device CS1 - 128M Board main flash
        ([nor_flash, nor_flash_ram, nor_flash_image], nor_flash_size) = (
            flash_create_memory_anon('S29GL01GP', 1, 16, [], big_endian = 1))
        nor_flash_space = self.add_pre_obj('nor_flash_space', 'memory-space')
        nor_flash_space.map = [[0, nor_flash, 0, 0, nor_flash_size, nor_flash_ram, 0]]

        self.add_slot('nor_flash', nor_flash)
        self.add_slot('nor_flash_ram', nor_flash_ram)
        self.add_slot('nor_flash_image', nor_flash_image)
        mv64560.DevCS_1 = nor_flash_space

        # Device CS2 - NAND Flash SAMSUNG K9F5616Q0C (32M) (not supported)
        nand_data_image = self.add_pre_obj('nand_data_image', 'image')
        nand_data_image.size = 256 * 32 * 2048
        nand_data_image.init_pattern = 0xff

        nand_spare_image = self.add_pre_obj('nand_spare_image', 'image')
        nand_spare_image.size = 2048 * 32 * 8
        nand_spare_image.init_pattern = 0xff

        nand_flash = self.add_pre_obj('nand_flash', 'onfi_flash')
        nand_flash.bus_width = 8
        nand_flash.spare_image = nand_spare_image
        nand_flash.data_image = nand_data_image
        nand_flash.data_bytes_per_page = 512
        nand_flash.pages_per_block = 32
        nand_flash.blocks = 2048
        nand_flash.id_bytes = [0xec, 0x45, 0x51, 0x95, 0x58]
        # TODO: find the exact info
        nand_flash.parameter_page = [
            # 0 - 3 "ONFI"
            0x4f, 0x4e, 0x46, 0x49,
            # 4 - 5 revision number - ONFI 1.0
            0x02, 0x00,
            # 6 - 7 feature supported
            0x1f, 0x00,
            # 8 - 9 optional commands supported
            0x3f, 0x00,
            # 10 - 31 Reserved 0
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            # 32 - 43 device manufacturer
            0x4E, 0x55, 0x4D, 0x4F, 0x4E, 0x59, 0x58,
            0x00, 0x00, 0x00, 0x00, 0x00,
            # 44 - 63 device model
            0x4E, 0x41, 0x4E, 0x44, 0x30, 0x38, 0x47, 0x57,
            0x33, 0x42, 0x32, 0x43, 0x4E, 0x31, 0x45, 0x00,
            0x00, 0x00, 0x00, 0x00,
            # 64 JEDEC manufacturer ID
            0x20,
            # 65 - 66 Date code
            0x07, 0x00,
            # 67 - 79 Reserved 0
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            # 80 - 83 number of data bytes per page
            0x00, 0x10, 0x00, 0x00,
            # 84 - 85 number of spare bytes per page
            0x80, 0x00,
            # 86 - 89 number of data bytes per partial page
            0x00, 0x10, 0x00, 0x00,
            # 90 - 91 number of spare bytes per partial page
            0x80, 0x00,
            # 92 - 95 number of pages per block
            0x80, 0x00, 0x00, 0x00,
            # 96 - 99 number of blocks per logical unit
            0x00, 0x20, 0x00, 0x00,
            # 100 number of local units
            0x01,
            # 101 column/row address cycles
            0x23,
            # 102 number of bits per cell
            0x08,
            # 103 - 104 bad blocks maximum per LUN
            0x00, 0x00,
            # 105 - 106 block endurance
            0x01, 0x05,
            # 107 guaranteed valid blcks at beginning of target
            0x01,
            # 108 - 109 block endurenace for guaranteed valid blocks
            0x00, 0x00,
            # 110 number of programs per page
            0xff,
            # 111 partial programming attributes
            0x11,
            # 112 number of bits ECC correctability
            0x00,
            # 113 number of interleaved address bits
            0x00,
            # 114 interleaved operation attributes
            0x06,
            # 115 - 127 reserved 0
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            # 128 I/O pin capacitance
            0x0A,
            # 129 - 130 timing mode support
            0x3F, 0x00,
            # 131 - 132 program cache timing mode support
            0x3F, 0x00,
            # 133 - 134 tPROG maximum page program time (us)
            0x01, 0x00,
            # 135 - 136 tBERS maximum block erase time (us)
            0x02, 0x00,
            # 137 - 138 tR maximum page read time (us)
            0x01, 0x00,
            # 139 - 163 reserved 0
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            # 164 - 165 vendor specific revision number
            0x04, 0x00,
            # 165 - 253 vendor specific
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            # 254 - 255 integrity CRC
            0x4e, 0x4f]
        mv64560_nand.nand = nand_flash
        nand_flash_space = self.add_pre_obj('nand_flash_space', 'memory-space')
        nand_flash_space.map = [[0x0, [mv64560_nand, 'regs'], 0, 0, 1], # Data
                                [0x1, [mv64560_nand, 'regs'], 0, 2, 1], # Command
                                [0x2, [mv64560_nand, 'regs'], 0, 4, 1]] # Address
        mv64560.DevCS_2 = nand_flash_space

        # Boot CS - 16M Boot flash
        ([flash, flash_ram, flash_image], flash_size) = (
            flash_create_memory_anon('28F128J3A', 1, 8, [], big_endian = 1))
        flash_space = self.add_pre_obj('flash_space', 'memory-space')
        flash_space.map = [[0, flash, 0, 0, flash_size, flash_ram, 0]]

        self.add_slot('flash', flash)
        self.add_slot('flash_ram', flash_ram)
        self.add_slot('flash_image', flash_image)
        mv64560.BootCS = flash_space

        mv64560.regs_CPU_Decode_BootCS_base = base_to_reg(0xfff00000)
        mv64560.regs_CPU_Decode_BootCS_size = size_to_reg(0x00100000)

        # PHYs
        phy_addr = [0x8, 0xa, 0x9]
        phy = self.add_pre_obj('phy[3]', 'generic_eth_phy')
        for i in xrange(3):
            # BCM5421S
            phy[i].tx_bandwidth = 0
            phy[i].mac = mv64560
            phy[i].register_defaults = [None] * 32
            phy[i].register_defaults[0] = 0x1000 # enable AN
            phy[i].phy_id = 0x001378f2
            phy[i].address = i + 25
            mii_bus.devices += [[phy[i], phy_addr[i]]]
        mv64560.phys = phy

        # U-Boot uses the cache as memory before the memory
        # controller is configured properly. Create a cache-space
        # which we can temporarily map.
        l1_cache_image = self.add_pre_obj('l1_cache_image', 'image')
        l1_cache_image.size = 0x1000
        l1_cache = self.add_pre_obj('l1_cache', 'ram')
        l1_cache.image = l1_cache_image

        # EEPROM for CPU, No L3 cache supported
        eeprom = self.add_pre_obj('eeprom', 'AT24Cxx')
        eeprom.i2c_bus = self.get_slot('i2c_bus')
        eeprom.i2c_address = 0x51
        eeprom.memory = (0xff,) * 256

        # Simics FS
        hfs = self.add_pre_obj('hfs', 'hostfs')
        self.get_slot('phys_mem').map += [
            [0xf3000000, hfs, 0, 0, 0x10]]

    def connect_mem_bus1(self, cnt, attr):
        (memory_megs, memory_ranks) = attr
        for i in xrange(memory_ranks):
            size = (memory_megs * (1 << 20)) / (memory_ranks)
            self.get_slot('cs_image[%d]' %i).size = size
            self.get_slot('cs_space[%d]' %i).map = [
                [0x0, self.get_slot('cs[%d]' %i), 0, 0, size]]

    def connect_mem_bus2(self, cnt, attr):
        (memory_megs, memory_ranks) = attr
        for i in xrange(memory_ranks):
            size = (memory_megs * (1 << 20)) / (memory_ranks)
            self.get_slot('cs_image[%d]' % (i + 2)).size = size
            self.get_slot('cs_space[%d]' % (i + 2)).map = [
                [0x0, self.get_slot('cs[%d]' % (i + 2)), 0, 0, size]]
