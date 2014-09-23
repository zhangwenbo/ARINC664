struct mac_mib_t {
	u32 crc_error;              
	u32 delete_little_64;		
	u32 delete_big_1518;
	u32 input_frame_count;
	u32 input_64_127_count;
	u32 input_128_255_count;
	u32 input_256_511_count;
	u32 input_512_1023_count;
	u32 input_1024_1518_count;
	u32 input_frame_byte_count;
	u32 output_frame_count;
	u32 output_64_127_count;
	u32 output_128_255_count;
	u32 output_256_511_count;
	u32 output_512_1023_count;
	u32 output_1024_1518_count;
	u32 output_frame_byte_count;
	u32 first_bit_error_count;
	u32 ipchecksum_error_count;
	u32 delete_big_2048_count;
};

struct rx_mib_t {
	u32 disable_a_filt_count;
	u32 disable_b_filt_count;
	u32 a_integrated_filt_count;
	u32 b_integrated_filt_count;
	u32 vl_id_filt_count;
	u32 redunt_filt_count;
	u32 port_filt_count;
	u32 ip_checksum_filt_count;
	u32 ip_length_error_filt_count;
	u32 udp_length_error_filt_count;
	u32 ip_fragment_error_filt_count;
	u32 overflow_count;
	u32 rx_icmp_reback_count;
	u32 rx_ip_data_count;
	u32 rx_udp_data_count;
	u32 rx_icmp_data_count;
	u32 icmp_overflow_count;
	u32 rx_icmp_big_max_count;
	u32 rx_buffer_clear_delete_count;
};

struct tx_mib_t {
	u32 tx_ip_count;
	u32 tx_udp_count;
	u32 tx_icmp_count;
};
