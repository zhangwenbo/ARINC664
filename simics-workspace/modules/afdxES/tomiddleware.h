#ifndef __TOMIDDLEWARE_H__
#define __TOMIDDLEWARE_H__
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>
#include "hwa_aes_klib.h"

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;

#define  MAX_RECV_PORTS  128
#define MAX_SEND_PORTS  128
#define MAX_VLS  128

struct analyse_cfg_cam {
	u32 address;

	u32 multicast_id : 1;
	u32 icmp_type_id : 1;
	u32 __reserved : 30;

	u32 dest_ip;

	u16 dest_udp;
	u16 vl_id;
};

struct analyse_cfg_ram {
	u16 port_type : 2;
	u16 network_a_enable : 1;
	u16 network_b_enable : 1;
	u16 __reserved : 12;
};

struct transmit_cfg_ram {
	u32 dst_partition_id;
	u32 user_defined_id_l;
	u32 user_defined_id_h;
	u32 private_ip;

	u32 vl_id ;
	u32 vl_index;
	u32 ip_multicast;
	u32 min_frame_length;
	u32 port_type;

	u32 partition_id;
	u32 interface_id;
	u32 protocol_id;
	u32 user_defined_id;

	u32 sub_vl_id;
	u32 dest_udp_port;
	u32 source_udp_port;
};

struct scheduling_cfg_ram {
	u32 bag;
};

struct rm_cfg_cam {
	u32 address;
	u16 vl_id;
};

struct rm_cfg_ram {
	u32 network_a_enable : 1;
	u32 network_b_enable : 1;
	u32 network_a_ic_enable : 1;
	u32 network_b_ic_enable : 1;
	u32 rm_enable : 1;
	u32 skew_max : 21;
	u32 vl_enable : 1;
	u32 __reserved : 5;
};

struct fragment_cfg_ram {
	u16 max_frame_length;
};

enum netpack_type_t {
	ANALYSE_CFG_CAM = 0,
	ANALYSE_CFG_RAM = 1,
	TRANSMIT_CFG_RAM = 2,
	SCHEDULING_CFG_RAM = 3,
	RM_CFG_CAM = 4,
	RM_CFG_RAM = 5,
	FRAGMENT_CFG_RAM = 6,
	PACKET_SEND = 7,
	PACKET_RECV = 8, // the only pack from midware to simulator.
	DO_LOAD_CONF = 9,
	MAC_MIB = 10,
	RX_MIB = 11,
	TX_MIB = 12
};

extern int Init_664_Work_Mode(void);
extern int Send_To_664_Middleware(unsigned char *recvbuf, int size);
extern int Recv_Data_From_664_Middleware(unsigned char *sendbuf, int size);
extern int Recv_Mib_Info_From_664_Middleware(unsigned char *recvbuf, int size);


#endif
