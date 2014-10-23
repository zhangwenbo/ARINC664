typedef unsigned int u32;
#include "hwa_aes_klib.h"
#include "mib.h"
#include <stdio.h>

#define __DEBUG__

static card_nr = 0;

#ifndef __DEBUG__
static void get_mac_mib_value(HwaNetMibType type, int a_or_b, u32 *value) {
	hwa_aes_mib_net_state(card_nr, a_or_b,type, value);
}
#else
static void get_mac_mib_value(HwaNetMibType type, int a_or_b, u32 *value) {
}
#endif

#ifndef __DEBUG__
static void get_rx_mib_value(HwaRxMibType type, u32 *value) {
	hwa_aes_mib_rx_state(card_nr, type, value) ;
}
#else
static void get_rx_mib_value(HwaRxMibType type, u32 *value) {
}
#endif

#ifndef __DEBUG__
static void get_tx_mib_value(HwaTxMibType type, u32 *value) {
	hwa_aes_mib_tx_state(card_nr, type, value);
}
#else
static void get_tx_mib_value(HwaTxMibType type, u32 *value) {
}
#endif

void get_mac_mib(int a_or_b, unsigned char *mib_t) {
	struct mac_mib_t *mib = (struct mac_mib_t *)mib_t;
	get_mac_mib_value(MIB_CRC_ERR_NUM, a_or_b, &mib->crc_error);
	get_mac_mib_value(MIB_SHORT_FRAME_ERR_NUM, a_or_b, &mib->delete_little_64);
	get_mac_mib_value(MIB_LONG_1518_FRAME_ERR_NUM, a_or_b, &mib->delete_big_1518);
	get_mac_mib_value(MIB_RECV_FRAME_NUM, a_or_b, &mib->input_frame_count);
	get_mac_mib_value(MIB_RECV_FRAME_64TO127_NUM, a_or_b, &mib->input_64_127_count);
	get_mac_mib_value(MIB_RECV_FRAME_128TO255_NUM, a_or_b, &mib->input_128_255_count);
	get_mac_mib_value(MIB_RECV_FRAME_256TO511_NUM, a_or_b, &mib->input_256_511_count);
	get_mac_mib_value(MIB_RECV_FRAME_512TO1023_NUM, a_or_b, &mib->input_512_1023_count);
	get_mac_mib_value(MIB_RECV_FRAME_1024TO1518_NUM, a_or_b, &mib->input_1024_1518_count);
	get_mac_mib_value(MIB_RECV_FRAME_BYTES, a_or_b, &mib->input_frame_byte_count);
	get_mac_mib_value(MIB_SEND_FRAME_NUM, a_or_b, &mib->output_frame_count);
	get_mac_mib_value(MIB_SEND_FRAME_64TO127_NUM, a_or_b, &mib->output_64_127_count);
	get_mac_mib_value(MIB_SEND_FRAME_128TO255_NUM, a_or_b, &mib->output_128_255_count);
	get_mac_mib_value(MIB_SEND_FRAME_256TO511_NUM, a_or_b, &mib->output_256_511_count);
	get_mac_mib_value(MIB_SEND_FRAME_512TO1023_NUM, a_or_b, &mib->output_512_1023_count);
	get_mac_mib_value(MIB_SEND_FRAME_1024TO1518_NUM, a_or_b, &mib->output_1024_1518_count);
	get_mac_mib_value(MIB_SEND_FRAME_BYTES, a_or_b, &mib->output_frame_byte_count);
	get_mac_mib_value(MIB_RECV_FRAME_PRE_ERR_NUM, a_or_b, &mib->first_bit_error_count);
	get_mac_mib_value(MIB_RECV_FRAME_IPCHECKSUM_ERR_NUM, a_or_b, &mib->ipchecksum_error_count);
	get_mac_mib_value(MIB_LONG_2048_FRAME_ERR_NUM, a_or_b, &mib->delete_big_2048_count);
}

void get_rx_mib(unsigned char *mib_t) {
	struct rx_mib_t *mib=(struct rx_mib *)mib_t;
	get_rx_mib_value(MIB_RX_A_DISABLE_TO_FILTER_FRAME_NUM, &mib->disable_a_filt_count);
	get_rx_mib_value(MIB_RX_B_DISABLE_TO_FILTER_FRAME_NUM, &mib->disable_b_filt_count);
	get_rx_mib_value(MIB_RX_A_SN_ERR_TO_FILTER_FRAME_NUM, &mib->a_integrated_filt_count);
	get_rx_mib_value(MIB_RX_B_SN_ERR_TO_FILTER_FRAME_NUM, &mib->b_integrated_filt_count);
	get_rx_mib_value(MIB_RX_VL_ERR_TO_FILTER_FRAME_NUM, &mib->vl_id_filt_count);
	get_rx_mib_value(MIB_RX_REDUND_ERR_TO_FILTER_FRAME_NUM, &mib->redunt_filt_count);
	get_rx_mib_value(MIB_RX_DSTPORT_ERR_TO_FILTER_FRAME_NUM, &mib->port_filt_count);
	get_rx_mib_value(MIB_RX_IP_CHECKSUM_ERR_TO_FILTER_FRAME_NUM, &mib->ip_checksum_filt_count);
	get_rx_mib_value(MIB_RX_IP_LEN_ERR_TO_FILTER_FRAME_NUM, &mib->ip_length_error_filt_count);
	get_rx_mib_value(MIB_RX_UDP_LEN_ERR_TO_FILTER_FRAME_NUM, &mib->udp_length_error_filt_count);
	get_rx_mib_value(MIB_RX_IP_FRAGMENT_ERR_TO_FILTER_FRAME_NUM, &mib->ip_fragment_error_filt_count);
	get_rx_mib_value(MIB_RX_BUF_LOST_NUM, &mib->overflow_count);
	get_rx_mib_value(MIB_RX_RECIVE_ICMP_BACK_TOTAL_NUM, &mib->rx_icmp_reback_count);
	get_rx_mib_value(MIB_RX_RECIVE_IP_PACKET_TOTAL_NUM, &mib->rx_ip_data_count);
	get_rx_mib_value(MIB_RX_RECIVE_UDP_PACKET_TOTAL_NUM, &mib->rx_udp_data_count);
	get_rx_mib_value(MIB_RX_RECIVE_ICMP_PACKET_TOTAL_NUM, &mib->rx_icmp_data_count);
	get_rx_mib_value(MIB_RX_RECIVE_ICMP_BACK_LOST_TOTAL_NUM, &mib->icmp_overflow_count);
	get_rx_mib_value(MIB_RX_RECIVE_ICMP_TLONG_FILTER_NUM, &mib->rx_icmp_big_max_count);
	get_rx_mib_value(MIB_RX_RECIVE_BUF_BACK_TOTAL_NUM, &mib->rx_buffer_clear_delete_count);
}


void get_tx_mib(unsigned char  *mib_t) {
	struct tx_mib_t *mib = (struct tx_mib_t *)mib_t;
	get_tx_mib_value(MIB_TX_SEND_IP_TOTAL_NUM, &mib->tx_ip_count);
	get_tx_mib_value(MIB_TX_SEND_UDP_TOTAL_NUM, &mib->tx_udp_count);
	get_tx_mib_value(MIB_TX_SEND_ICMP_TOTAL_NUM, &mib->tx_icmp_count);
}
