#include "record-mib.h"

void write_mid(MAC_MIB *maca_mib, MAC_MIB *macb_mib, RX_MIB *rx_mib, TX_MIB *tx_mib) {
    FILE *mib_file = fopen("./mib_file.conf", "w");    
    fprintf(mib_file, "========================================= Mac A mib begin ===================================================\n");
    fprintf(mib_file, "crc_error: %d\n", maca_mib->crc_error);
    fprintf(mib_file, "delete_little_64: %d\n", maca_mib->delete_little_64);
    fprintf(mib_file, "delete_big_1518: %d\n", maca_mib->delete_big_1518);
    fprintf(mib_file, "input_frame_count: %d\n", maca_mib->input_frame_count);
    fprintf(mib_file, "input_64_127_count: %d\n", maca_mib->input_64_127_count);
    fprintf(mib_file, "input_128_255_count: %d\n", maca_mib->input_128_255_count);
    fprintf(mib_file, "input_256_511_count: %d\n", maca_mib->input_256_511_count);
    fprintf(mib_file, "input_512_1023_count: %d\n", maca_mib->input_512_1023_count);
    fprintf(mib_file, "input_1024_1518_count: %d\n", maca_mib->input_1024_1518_count);
    fprintf(mib_file, "input_frame_byte_count: %d\n", maca_mib->input_frame_byte_count);
    fprintf(mib_file, "output_frame_count: %d\n", maca_mib->output_frame_count);
    fprintf(mib_file, "output_64_127_count: %d\n", maca_mib->output_64_127_count);
    fprintf(mib_file, "output_128_255_count: %d\n", maca_mib->output_128_255_count);
    fprintf(mib_file, "output_256_511_count: %d\n", maca_mib->output_256_511_count);
    fprintf(mib_file, "output_512_1023_count: %d\n", maca_mib->output_512_1023_count);
    fprintf(mib_file, "output_1024_1518_count: %d\n", maca_mib->output_1024_1518_count);
    fprintf(mib_file, "output_frame_byte_count: %d\n", maca_mib->output_frame_byte_count);
    fprintf(mib_file, "first_bit_error_count: %d\n", maca_mib->first_bit_error_count);
    fprintf(mib_file, "ipchecksum_error_count: %d\n", maca_mib->ipchecksum_error_count);
    fprintf(mib_file, "delete_bit_2048_count: %d\n", maca_mib->delete_bit_2048_count);
	
    fprintf(mib_file, "========================================= Mac B mib begin ===================================================\n");
    fprintf(mib_file, "crc_error: %d\n", macb_mib->crc_error);
    fprintf(mib_file, "delete_little_64: %d\n", macb_mib->delete_little_64);
    fprintf(mib_file, "delete_big_1518: %d\n", macb_mib->delete_big_1518);
    fprintf(mib_file, "input_frame_count: %d\n", macb_mib->input_frame_count);
    fprintf(mib_file, "input_64_127_count: %d\n", macb_mib->input_64_127_count);
    fprintf(mib_file, "input_128_255_count: %d\n", macb_mib->input_128_255_count);
    fprintf(mib_file, "input_256_511_count: %d\n", macb_mib->input_256_511_count);
    fprintf(mib_file, "input_512_1023_count: %d\n", macb_mib->input_512_1023_count);
    fprintf(mib_file, "input_1024_1518_count: %d\n", macb_mib->input_1024_1518_count);
    fprintf(mib_file, "input_frame_byte_count: %d\n", macb_mib->input_frame_byte_count);
    fprintf(mib_file, "output_frame_count: %d\n", macb_mib->output_frame_count);
    fprintf(mib_file, "output_64_127_count: %d\n", macb_mib->output_64_127_count);
    fprintf(mib_file, "output_128_255_count: %d\n", macb_mib->output_128_255_count);
    fprintf(mib_file, "output_256_511_count: %d\n", macb_mib->output_256_511_count);
    fprintf(mib_file, "output_512_1023_count: %d\n", macb_mib->output_512_1023_count);
    fprintf(mib_file, "output_1024_1518_count: %d\n", macb_mib->output_1024_1518_count);
    fprintf(mib_file, "output_frame_byte_count: %d\n", macb_mib->output_frame_byte_count);
    fprintf(mib_file, "first_bit_error_count: %d\n", macb_mib->first_bit_error_count);
    fprintf(mib_file, "ipchecksum_error_count: %d\n", macb_mib->ipchecksum_error_count);
    fprintf(mib_file, "delete_bit_2048_count: %d\n", macb_mib->delete_bit_2048_count);
	
	
    fprintf(mib_file, "========================================= rx mib begin =====================================================\n");
    fprintf(mib_file, "disable_A_filt_count: %d\n", rx_mib->disable_A_filt_count);
    fprintf(mib_file, "disable_B_filt_count: %d\n", rx_mib->disable_B_filt_count);
    fprintf(mib_file, "A_integrated_filt_count: %d\n", rx_mib->A_integrated_filt_count);
    fprintf(mib_file, "B_integrated_filt_count: %d\n", rx_mib->B_integrated_filt_count);
    fprintf(mib_file, "vl_id_filt_count: %d\n", rx_mib->vl_id_filt_count);
    fprintf(mib_file, "redunt_filt_count: %d\n", rx_mib->redunt_filt_count);
    fprintf(mib_file, "port_filt_count: %d\n", rx_mib->port_filt_count);
    fprintf(mib_file, "ip_checksum_filt_count: %d\n", rx_mib->ip_checksum_filt_count);
    fprintf(mib_file, "ip_length_error_filt_count: %d\n", rx_mib->ip_length_error_filt_count);
    fprintf(mib_file, "udp_length_error_filt_count: %d\n", rx_mib->udp_length_error_filt_count);
    fprintf(mib_file, "ip_fragment_error_filt_count: %d\n", rx_mib->ip_fragment_error_filt_count);
    fprintf(mib_file, "overflow_count: %d\n", rx_mib->overflow_count);
    fprintf(mib_file, "rx_icmp_reback_count: %d\n", rx_mib->rx_icmp_reback_count);
    fprintf(mib_file, "rx_ip_data_count: %d\n", rx_mib->rx_ip_data_count);
    fprintf(mib_file, "rx_udp_data_count: %d\n", rx_mib->rx_udp_data_count);
    fprintf(mib_file, "rx_icmp_data_count: %d\n", rx_mib->rx_icmp_data_count);
    fprintf(mib_file, "icmp_overflow_count: %d\n", rx_mib->icmp_overflow_count);
    fprintf(mib_file, "rx_icmp_big_max_count: %d\n", rx_mib->rx_icmp_big_max_count);
    fprintf(mib_file, "rx_buffer_clear_delete_count: %d\n", rx_mib->rx_buffer_clear_delete_count);
	
    fprintf(mib_file, "========================================= tx mib begin =====================================================\n");
    fprintf(mib_file, "tx_ip_count: %d\n", tx_mib->tx_ip_count);
    fprintf(mib_file, "tx_udp_count: %d\n", tx_mib->tx_udp_count);
    fprintf(mib_file, "tx_icmp_count: %d\n", tx_mib->tx_icmp_count);
	
    fclose(mib_file);
}
