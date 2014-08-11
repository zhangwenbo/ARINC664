#ifndef RECORD_MIB_H
#define RECORD_MIB_H

#include <stdio.h>

typedef unsigned int uint32;

typedef struct _MAC_MIB {
    uint32 crc_error;   				//crc checksum error
    uint32 delete_little_64;  			//delete the frame that size is little than 64B
    uint32 delete_big_1518;   			//delete the frame that size is bigger than 1518B
    uint32 input_frame_count;  			// input frame count
    uint32 input_64_127_count;			//input frame size between 64 and 127
    uint32 input_128_255_count;			//input frame size between 128 and 255
    uint32 input_256_511_count;			//input frame size between 256 and 511
    uint32 input_512_1023_count;		//input frame size between 512 and 1023
    uint32 input_1024_1518_count;		//input frame size between 1024 and 1023
    uint32 input_frame_byte_count; 		// input frame byte count
    uint32 output_frame_count;  		// output frame byte count
    uint32 output_64_127_count;			//output frame size between 64 and 127
    uint32 output_128_255_count;		//output frame size between 128 and 255
    uint32 output_256_511_count;		//output frame size between 256 and 511
    uint32 output_512_1023_count;		//output frame size between 512 and 1023
    uint32 output_1024_1518_count;		//output frame size between 1024 and 1023
    uint32 output_frame_byte_count;  	// output frame byte count
    uint32 first_bit_error_count;		//first bit error
    uint32 ipchecksum_error_count;		//ip checksum error
    uint32 delete_bit_2048_count;		//delete the frame bigger than 2048
} MAC_MIB;

typedef struct _RX_MIB {
    uint32 disable_A_filt_count;
    uint32 disable_B_filt_count;
    uint32 A_integrated_filt_count;
    uint32 B_integrated_filt_count;
    uint32 vl_id_filt_count;
    uint32 redunt_filt_count;
    uint32 port_filt_count;
    uint32 ip_checksum_filt_count;
    uint32 ip_length_error_filt_count;
    uint32 udp_length_error_filt_count;
    uint32 ip_fragment_error_filt_count ;
    uint32 overflow_count;
    uint32 rx_icmp_reback_count;
    uint32 rx_ip_data_count;
    uint32 rx_udp_data_count;
    uint32 rx_icmp_data_count;
    uint32 icmp_overflow_count;
    uint32 rx_icmp_big_max_count;
    uint32 rx_buffer_clear_delete_count;
    uint32 size;
} RX_MIB;

typedef struct _TX_MIB {
    uint32 tx_ip_count;
    uint32 tx_udp_count;
    uint32 tx_icmp_count;
} TX_MIB;

extern void write_mid(MAC_MIB *maca_mib, MAC_MIB *macb_mib, RX_MIB *rx_mib, TX_MIB *tx_mib);

#endif
