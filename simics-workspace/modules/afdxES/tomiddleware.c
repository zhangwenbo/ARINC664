#include "tomiddleware.h"

#define __DEBUG__

SOCKET client_socket;
#define MAX_RECV_PORTS 128
#define MAX_SEND_PORTS 128
#define MAX_PACK_LEN 8192

SOCKET client_socket;
static unsigned send_ports[MAX_SEND_PORTS];
static unsigned recv_ports[MAX_RECV_PORTS];
static int send_port_num;
static int recv_port_num;
static char send_port_name[30]="send_port_";
static char recv_port_name[30]="recv_port_";

int Init_664_Work_Mode(void) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    client_socket = socket(AF_INET, SOCK_STREAM , 0);    

    if (client_socket  == INVALID_SOCKET) {
        fprintf(stderr, "Create socket failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    SOCKADDR_IN serveraddr;   
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(10087);
    serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");   

    if (connect(client_socket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    fprintf(stdout, "Socket_init ok\n");

    return 0;
}

int Send_To_664_Middleware(unsigned char *sendbuf, int size) {
    int len = send(client_socket, (char *)sendbuf, size, 0);

    if (len == size) {
     //   fprintf(stdout, "Socket send sucessfully, send %d bytes.\n", len);
        return len;
    } else {
		fprintf(stderr, "Socket send failed, size = %d, sended len = %d!\n", size, len);
        return 0;
    }
}

int Recv_Data_From_664_Middleware(unsigned char *recvbuf, int size) {
    fd_set rfds;
    FD_ZERO(&rfds);                
    FD_SET(client_socket, &rfds);  

    struct timeval tv = {0};             

    int retval = select(0, &rfds, NULL, NULL, &tv);   
    if (retval == -1) {
        fprintf(stderr, "Socket recv select failed, error code is %d\n.", WSAGetLastError());
        return -1;
    }
    else if (retval == 0) {
        return 0;
    } else {
        int len = 0;

        if (FD_ISSET(client_socket, &rfds)) {
            memset(recvbuf, 0, size);

            len = recv(client_socket, (char *)recvbuf, size, 0);
            if (len > 0) {
                fprintf(stdout, "Socket recv sucessfully, recv %d size!\n", len);
            } else {
                fprintf(stderr, "Socket recv failed, error code is %d.\n", WSAGetLastError());
            }
        }

        return len;
    }
}

int Recv_Mib_Info_From_664_Middleware(unsigned char *recvbuf, int size) {
    int len = recv(client_socket, (char *)recvbuf, size, 0);
    if (len > 0) {
        fprintf(stdout, "Socket recv successfully, recv %d size!\n", len);
    } else {
        fprintf(stderr, "Socket recv failed, error code is %d.\n", WSAGetLastError());
    }
    return len;
}

const int analyse_cfg_cam_array_len = MAX_RECV_PORTS;
struct analyse_cfg_cam analyse_cfg_cam_array[MAX_RECV_PORTS];

const int analyse_cfg_ram_array_len = MAX_RECV_PORTS;
struct analyse_cfg_ram analyse_cfg_ram_array[MAX_RECV_PORTS];

const int transmit_cfg_ram_array_len = MAX_SEND_PORTS;
struct transmit_cfg_ram transmit_cfg_ram_array[MAX_SEND_PORTS];

const int scheduling_cfg_ram_array_len = MAX_SEND_PORTS;
struct scheduling_cfg_ram scheduling_cfg_ram_array[ MAX_SEND_PORTS];

const int fragment_cfg_ram_array_len = MAX_SEND_PORTS;
struct fragment_cfg_ram fragment_cfg_ram_array[MAX_SEND_PORTS];

const int rm_cfg_cam_array_len = MAX_VLS;
struct rm_cfg_cam rm_cfg_cam_array[MAX_VLS];

const int rm_cfg_ram_array_len = MAX_VLS;
struct rm_cfg_ram rm_cfg_ram_array[MAX_VLS];

void write_cfg_table(int type ,unsigned char *buf, int size) {
	
	switch(type){	
		case ANALYSE_CFG_CAM:
				memcpy(analyse_cfg_cam_array,buf,size);
				break;
		case ANALYSE_CFG_RAM:
				memcpy(analyse_cfg_ram_array,buf,size);
				break;
		case TRANSMIT_CFG_RAM:
				memcpy(transmit_cfg_ram_array,buf,size);
				break;
		case SCHEDULING_CFG_RAM:
				memcpy(scheduling_cfg_ram_array,buf,size);
				break;
		case RM_CFG_CAM:
				memcpy(rm_cfg_cam_array,buf,size);
				break;
		case RM_CFG_RAM:
				memcpy(rm_cfg_ram_array,buf,size);
				break;
		case FRAGMENT_CFG_RAM:
				memcpy(fragment_cfg_ram_array,buf,size);
				break;
		default:
			break;
	}
}

static int all_zeroes(char *buf, int buf_len)
{
	for (int i = 0; i < buf_len; i++)
		if (buf[i] != 0)
			return 0;
	return 1;
}

static char* port_type_string(u16 port_type)
{
	switch (port_type) {
	case 0:
		return "Queue";
	case 1:
		return "Sample";
	case 2:
		return "SAP";
	case 3:
		return "ICMP";
	default:
		printf( "port_type_string(): unrecognized port type.\n");
		return "";
	}
}

static char* ab_enable_string(u32 enable_a, u32 enable_b)
{
	if (enable_a && enable_b)
		return "AB";
	else if (enable_a)
		return "A";
	else if (enable_b)
		return "B";
	else
		printf( "ab_enable_string(): at least one of network a/b must be enabled.\n");
	return "";
}


void send_port_string(FILE *fp) {
	int i;
	for (i = 0; i < transmit_cfg_ram_array_len; i++) {
		struct transmit_cfg_ram *ram = &transmit_cfg_ram_array[i];
		if (all_zeroes((char *)ram, sizeof(*ram)))
			continue;
		send_port_num++;
		sprintf(send_port_name,"send_port_%d",i);
		fprintf(fp,"<AFDXPort ");
		fprintf(fp,"BAG=\"%d\" ",scheduling_cfg_ram_array[ram->vl_index].bag / 1000);
		fprintf(fp,"DirectionType=\"Send\" ");
		fprintf(fp,"DstIP_2=\"%d\" ",ram->user_defined_id_h<<6|ram->user_defined_id_l>>8);
		fprintf(fp,"DstIP_3=\"%d\" ",ram->user_defined_id_l & 0xff);
		fprintf(fp,"DstIP_4=\"%d\" ",ram->dst_partition_id);
		fprintf(fp,"DstUDP=\"%d\" ",ram->dest_udp_port);
		fprintf(fp,"MaxFrameSize=\"%d\" ",fragment_cfg_ram_array[i].max_frame_length);
		fprintf(fp,"MinFrameSize=\"%d\" ",ram->min_frame_length);
		fprintf(fp,"Multicast=\"%s\" ",ram->ip_multicast? "Enable" : "Disable");
		fprintf(fp,"PartitionID=\"%d\" ",ram->partition_id);
		fprintf(fp,"PortName=\"%s\" ",send_port_name);
		fprintf(fp,"PortNetwork=\"%s\" ",ab_enable_string(ram->interface_id & 1, ram->interface_id & 2));
		fprintf(fp,"PortType=\"%s\" ", port_type_string(ram->port_type));
		fprintf(fp,"SrcUDP=\"%d\" ",ram->source_udp_port);
		fprintf(fp,"SubVL=\"%d\" ",ram->sub_vl_id);
		fprintf(fp,"VL=\"%d\" ",ram->vl_id);
		fprintf(fp,"VLNetwork=\"%s\" ",ab_enable_string(ram->interface_id & 1, ram->interface_id & 2));
		fprintf(fp,"/>\n");
	}
}

struct rm_cfg_ram* get_vl_conf(u16 vl_id)
{
	for (int i = 0; i < rm_cfg_cam_array_len; i++)
		if (rm_cfg_cam_array[i].vl_id == vl_id)
			return &rm_cfg_ram_array[rm_cfg_cam_array[i].address];
	return NULL;
}

static unsigned ip_part(u32 ip, unsigned offset)
{
	return (unsigned)((unsigned char *)&ip)[offset - 1]; // NOTE: offset is 1-based.
}

void recv_port_string(FILE *fp) {
	int i;
	for (i = 0; i < analyse_cfg_cam_array_len; i++) {
		
		struct analyse_cfg_cam *cam = &analyse_cfg_cam_array[i];
		struct analyse_cfg_ram *ram = &analyse_cfg_ram_array[cam->address];
		if (all_zeroes((char *)cam, sizeof(*cam)) || all_zeroes((char *)ram, sizeof(*ram)))
			continue;

		recv_port_num++;
		struct rm_cfg_ram *vl_ram = get_vl_conf(cam->vl_id);
		sprintf(recv_port_name,"recv_port_%d",i);
		fprintf(fp,"<AFDXPort ");
		fprintf(fp,"DirectionType=\"Recv\" ");
		fprintf(fp,"DstIP_2=\"%d\" ",ip_part(cam->dest_ip, 3));
		fprintf(fp,"DstIP_3=\"%d\" ",ip_part(cam->dest_ip, 2));
		fprintf(fp,"DstIP_4=\"%d\" ",ip_part(cam->dest_ip, 1));	
		fprintf(fp,"DstUDP=\"%d\" ",cam->dest_udp);
		fprintf(fp,"IntegralityCheckA=\"%s\" ",vl_ram->network_a_ic_enable? "Enable" : "Disable");
		fprintf(fp,"IntegralityCheckB=\"%s\" ",vl_ram->network_b_ic_enable? "Enable" : "Disable");
		fprintf(fp,"Multicast=\"%s\" ",cam->multicast_id? "Enable" : "Disable");
		fprintf(fp,"PartitionID=\"%d\" ",ip_part(cam->dest_ip, 1));
		fprintf(fp,"PortName=\"%s\" ",recv_port_name);
		fprintf(fp,"PortNetwork=\"%s\" ",ab_enable_string(ram->network_a_enable, ram->network_b_enable));
		fprintf(fp,"PortType=\"%s\" ",port_type_string(ram->port_type));
		fprintf(fp,"Redund=\"%s\" ",vl_ram->rm_enable?  "Enable" : "Disable");
		fprintf(fp,"SkewMax=\"%d\" ",vl_ram->skew_max);
		fprintf(fp,"SrcUDP=\"0\" ");
		fprintf(fp,"VL=\"%d\" ",cam->vl_id);
		fprintf(fp,"VLNetwork=\"%s\" ",ab_enable_string(vl_ram->network_a_enable, vl_ram->network_b_enable));
		fprintf(fp,"/>\n");
	}
}

void LoadCfgTo664Middleware() {
	FILE *fp;
	fp = fopen("a664conf.xml","w+");
	if(fp == NULL){
		printf("open rx_mib.txt failed\n");
	} else {
		printf("open rx_mib.txt succeed\n");
	}
	
	fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fp,"<AFDXCard CreateTime=\"2011-12-27 13:39:29\" Company=\"Hwa Create\">\n");
	fprintf(fp,"<AFDXNetwork Speed=\"100\">\n");
//	fprintf(fp,"<AFDXEs UserDefinedID=\"%d\">\n",transmit_cfg_ram_array[0].user_defined_id_h<<14 | transmit_cfg_ram_array[0].user_defined_id_l);
	fprintf(fp,"<AFDXEs UserDefinedID=\"%d\">\n",transmit_cfg_ram_array[0].user_defined_id);
	send_port_string(fp);
	recv_port_string(fp);
	fprintf(fp,"</AFDXEs>\n");
	fprintf(fp,"</AFDXNetwork>\n");
	fprintf(fp,"</AFDXCard>\n");
	
	fclose(fp);
}

#ifndef __DEBUG__
int Init_664_Card(void) {
	int cardnum;
	int card_count;
	int ret =0;
	int i;

		
	//find card
	card_count = hwa_aes_find_card();
	if (card_count <= 0) {
		printf("No Card : %d\n", card_count);
		hwa_aes_free_card();
		getchar();
		return -1;
	}
	//for test
	cardnum = 0;                /* 可扩展 */
	
//	hwa_aes_set_mode(cardnum,mode_normal);
    hwa_aes_set_mode(cardnum, mode_inject);
		
	//open card
	printf("Opening Card...\n");
	if ((ret=hwa_aes_open_card(cardnum)) != HWA_AES_OK) {
		printf("open failed\n");	
		getchar();
		return ret;
	}
	printf ("open card OK!\n");

	//load config
	printf("load afdx config ...\n");
	if( (ret=hwa_aes_load_afdx_config (cardnum, "a664conf.xml")) != HWA_AES_OK)	{
		printf ("load afdx config failed with %d!\n",ret);
		getchar();
		return -4;
	}
	printf ("load afdx config OK!\n");

	for (i=0; i < send_port_num; i++) {
		sprintf(send_port_name,"send_port_%d",i);
		if((ret=hwa_aes_create_afdx_port(cardnum,send_port_name,vl_send,send_ports+i)) != HWA_AES_OK) {
			printf ("create send port error\n");
			getchar();
			if(i==0)
				return 100;
			return i;
		}
	}
	for (i=0; i < recv_port_num; i++) {
		sprintf(recv_port_name,"recv_port_%d",i);
		if((ret=hwa_aes_create_afdx_port(cardnum,recv_port_name,vl_recv,recv_ports+i)) != HWA_AES_OK) {
			printf ("create recv port error\n");
			getchar();
			return -8;
		}
	}
	
	return 0;
}
#else
int Init_664_Card(void) {
}
#endif

#ifndef __DEBUG__
int Recv_From_A664(int card_nr, int port_id, unsigned char *buf,unsigned *network, unsigned *valid) {
	HwaRecvTime time;
	
	int len = hwa_aes_recv(card_nr, recv_ports[port_id], buf, MAX_PACK_LEN, &time, network, valid);
	
	return len;
}
#else
int Recv_From_A664(int card_nr, int port_id, unsigned char *buf,unsigned *network, unsigned *valid) {
}
#endif

#ifndef __DEBUG__
int Send_To_A664(int card_nr, int port_id, unsigned char *buf, int len) {
	int ret = hwa_aes_send (card_nr, send_ports[port_id], buf, len);
	
	return ret;
}
#else
int Send_To_A664(int card_nr, int port_id, unsigned char *buf, int len) {
}
#endif

int get_recv_port_num() {
	return recv_port_num;
}

