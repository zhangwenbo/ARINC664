#ifndef _HWA_AES_KLIB_H_
#define _HWA_AES_KLIB_H_

#ifdef WIN32_NORMAL  /* For Windows */

#ifdef _AFDX_EXPORT
#ifdef __cplusplus
#define _AFDX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define _AFDX_DLL_EXPORT __declspec(dllexport)
#endif
#else
#ifdef __cplusplus
#define _AFDX_DLL_EXPORT extern "C" __declspec(dllimport)
#else
#define _AFDX_DLL_EXPORT __declspec(dllimport)
#endif
#endif

#else  /* For VxWorks */

#ifdef __cplusplus
#define _AFDX_DLL_EXPORT extern "C" __declspec(dllimport)
#else
#define _AFDX_DLL_EXPORT __declspec(dllimport)
#endif

#endif

/* Error Code */
#define HWA_AES_OK			        0
#define HWA_AES_CARD_NOT_FOUND				-1
#define HWA_AES_CARD_NOT_OPEN				-2
#define HWA_AES_CARD_INVALID				-3
#define HWA_AES_OPEN_FILE_ERR				-4
#define HWA_AES_AFDX_615A_LOAD_MODE			-5
#define HWA_AES_RESET_ERR					-6
#define HWA_AES_XML_FILE_ERR				-7
#define HWA_AES_PARAMETER_ERR				-8
#define HWA_AES_SEM_ERR						-9
#define HWA_AES_CHECK_DMA_TIMEOUT			-10
#define HWA_AES_BUF_OVERFLOW				-11
#define HWA_AES_ISR_ERR						-12
#define HWA_AES_RECV_DATA_ERR				-13
#define HWA_AES_NO_MEM						-14
#define HWA_AES_INIT_ERR					-15
#define HWA_AES_UNKNOWN_ERR					-16
#define HWA_AES_PORT_EXIST                  -17
#define HWA_AES_MSGQ_ERR                    -18
#define HWA_AES_MSGQ_TIMEOUT         -18
#define HWA_AES_TASK_ERR        			-19
#define HWA_AES_PHY_ERR          			-20
#define HWA_AES_PHY_NO_LINK  				-21
#define HWA_AES_LOAD_FPGA 					-22
#define HWA_AES_LOAD_XML_FROM_FLASH_MAGICNUM	-23
#define HWA_AES_LOAD_XML_FORM_FLASH 			-24
#define HWA_AES_DMA_INIT_ERR 					-25
#define HWA_AES_SET_PCI_ERR 					-26
#define HWA_AES_ONLY_NORMAL_MODE 				-27
#define HWA_AES_CARD_ALREADY_OPEN 				-28
#define HWA_AES_CARD_CLOSE 						-29
#define HWA_AES_UNINIT_ERR 						-30
#define HWA_AES_OPEN_ERR 						-31
#define HWA_AES_LOAD_XML 						-32
#define HWA_AES_NOT_SUPPORT 					-33
#define HWA_AES_CLOSE_ERR 						-34
#define HWA_AES_PORT_BUSY 						-35
#define HWA_AES_PORT_NOTFOUND 					-36
#define HWA_AES_PORT_TOO_MANY					-37
#define HWA_AES_PORT_DUPLICATE  				-38
#define HWA_AES_PACKET_LENGTH_ERR				-39

/*Monitor Mode*/
#define HWA_AES_MONITOR_START_EXIST -130
#define HWA_AES_FINISHED_FIND -131
#define HWA_AES_ONLY_MONITOR_MODE -132


/*Inject Mode*/
#define HWA_AES_INJECT_START_EXIST  -200
#define HWA_AES_ONLY_INJECT_MODE   -201

typedef enum{
	MIB_TX_SEND_IP_TOTAL_NUM=0,
	MIB_TX_SEND_UDP_TOTAL_NUM,
	MIB_TX_SEND_ICMP_TOTAL_NUM,
	MIB_TX_NR
}HwaTxMibType;


typedef enum{
	MIB_RX_A_DISABLE_TO_FILTER_FRAME_NUM = 0,
	MIB_RX_B_DISABLE_TO_FILTER_FRAME_NUM ,
	MIB_RX_A_SN_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_B_SN_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_VL_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_REDUND_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_DSTPORT_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_IP_CHECKSUM_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_IP_LEN_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_UDP_LEN_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_IP_FRAGMENT_ERR_TO_FILTER_FRAME_NUM ,
	MIB_RX_BUF_LOST_NUM,
	MIB_RX_RECIVE_IP_PACKET_TOTAL_NUM,
	MIB_RX_RECIVE_UDP_PACKET_TOTAL_NUM,
	MIB_RX_RECIVE_ICMP_PACKET_TOTAL_NUM,
	MIB_RX_RECIVE_ICMP_BACK_TOTAL_NUM,
	MIB_RX_RECIVE_ICMP_BACK_LOST_TOTAL_NUM,
	MIB_RX_RECIVE_ICMP_TLONG_FILTER_NUM,
	MIB_RX_RECIVE_BUF_BACK_TOTAL_NUM,
	MIB_RX_NR
}HwaRxMibType;


typedef enum{
	MIB_CRC_ERR_NUM=0	,
	MIB_SHORT_FRAME_ERR_NUM	,
	MIB_LONG_1518_FRAME_ERR_NUM	,
	MIB_RECV_FRAME_NUM,
	MIB_RECV_FRAME_64TO127_NUM,
	MIB_RECV_FRAME_128TO255_NUM,
	MIB_RECV_FRAME_256TO511_NUM,
	MIB_RECV_FRAME_512TO1023_NUM,
	MIB_RECV_FRAME_1024TO1518_NUM,
	MIB_RECV_FRAME_BYTES,
	MIB_SEND_FRAME_NUM,
	MIB_SEND_FRAME_64TO127_NUM,
	MIB_SEND_FRAME_128TO255_NUM,
	MIB_SEND_FRAME_256TO511_NUM,
	MIB_SEND_FRAME_512TO1023_NUM,
	MIB_SEND_FRAME_1024TO1518_NUM,
	MIB_SEND_FRAME_BYTES,
	MIB_RECV_FRAME_PRE_ERR_NUM ,
	MIB_RECV_FRAME_IPCHECKSUM_ERR_NUM ,
	MIB_LONG_2048_FRAME_ERR_NUM,
	MIB_NET_NR
}HwaNetMibType;


/* data struct */
typedef enum  /* Afdx Card Work Mode */
{
	mode_normal = 0,
	mode_test,
	mode_monitor,
	mode_inject
}HwaWorkMode;

typedef enum	/* VL Direction*/
{
	vl_send	= 0,
	vl_recv
}HwaVlDirection;

typedef enum /* Port Type */
{
	port_queue	= 0,
	port_sample,
	port_sap,
	port_icmp,
	port_type_nr
}HwaPortType;

typedef enum /* Net Type */
{
	net_a = 1,
	net_b ,
#if HWA_AES_8
	net_c,
	net_d,
	net_e,
	net_f,
	net_g,
	net_h,
#endif
	net_ab
}HwaNetwork;

typedef enum   /* Recv Mode (POLL or Interrupt)*/
{
	mode_poll =0,
	mode_int
}HwaRecvMode;

typedef enum /* IRIGB Mode*/
{
	mode_slave =0 ,
	mode_master
}HwaIrigbMode;

typedef enum /* OutPut Select (Rj45 or PMC J4)*/
{
	mode_j4=0,
	mode_rj45
}HwaOutputMode;

typedef enum  /* Sampling Port Mode (Capture or No Capture)*/
{
	mode_nocapure=0,
	mode_capture

}HwaCaptureMode;

typedef enum   /* Ip muliticast mode */
{
	mode_singlecast=0,
	mode_multicast
}HwaMulticastMode;

typedef struct 		/* Card Info*/
{
	unsigned int vendor_id;
	unsigned int device_id;
	unsigned int bus_num;
	unsigned int slot_num;
	unsigned int func_num;
	unsigned int hw_ver;
	unsigned int work_mode;
	char serial[16];
}HwaCardInfo;

typedef struct  /* packet stamp*/
{
	unsigned int day;
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
	unsigned int ms;
	unsigned int us;
}HwaTime;

typedef struct    /* recv time*/
{
	unsigned int time_low;   /* sec,min,us,ms*/
	unsigned int time_high;  /* day ,hour*/
}HwaRecvTime;

typedef struct /* Monitor Mode ,resolved packet info*/
{
	unsigned char net;
	int packet_len;
	HwaRecvTime time;
	unsigned int pre_error;
	unsigned int ip_checksum_error;
	unsigned int crc_error;
	unsigned short startbit_pos;
}HwaPackInfo;

#define HWA_AES_IP_LEN 32
typedef struct/*sap port information*/
{
	unsigned int local_udp;
	unsigned int remote_udp;
	char remote_ip[HWA_AES_IP_LEN];
	HwaRecvTime time;
	unsigned int network;
	unsigned int valid;
}HwaPktSrc;

/* API */
/* find all card,return the count of card */
_AFDX_DLL_EXPORT int hwa_aes_find_card (void);

/* free all card resource */
_AFDX_DLL_EXPORT int hwa_aes_free_card(void);

/* get card info */
_AFDX_DLL_EXPORT int hwa_aes_get_card_info(int cardnum,HwaCardInfo *card_info);

/* set addr remap ,only for vxworks */
_AFDX_DLL_EXPORT int hwa_aes_set_addr_map(unsigned int (*func)());

/* set card mode */
_AFDX_DLL_EXPORT int hwa_aes_set_mode(int cardnum, unsigned int work_mode);

/* open card */
_AFDX_DLL_EXPORT int hwa_aes_open_card (int cardnum);

/* close card */
_AFDX_DLL_EXPORT int hwa_aes_close_card (int cardnum);

/* set recv mode (poll or interrupt) */
_AFDX_DLL_EXPORT int hwa_aes_set_recv_mode(int cardnum,int recv_mode);

/* set irigb mode (slave or master)*/
_AFDX_DLL_EXPORT int hwa_aes_set_irigb_mode(int cardnum,int irigb_mode);

/* set card output(Rj45 or PMC j4)*/
_AFDX_DLL_EXPORT int hwa_aes_set_output(int cardnum,int output);

/*Set Caputure Mode*/
_AFDX_DLL_EXPORT int hwa_aes_set_capture(int cardnum, int caputure);

/*set user id*/
_AFDX_DLL_EXPORT int hwa_aes_set_user_id(int cardnum,int user_id);

/*load afdx xml*/
_AFDX_DLL_EXPORT int hwa_aes_load_afdx_config (int cardnum, const char *cfgfilepath);

/*Create VL and Port with Port_name*/
_AFDX_DLL_EXPORT int hwa_aes_create_afdx_port (int cardnum,char *portName,unsigned int vlDirection,unsigned int *portId);

/*Create VL*/
_AFDX_DLL_EXPORT int hwa_aes_create_vl (int cardnum,unsigned int vlId,	unsigned int vlDirection,float bag,unsigned int skewMax,unsigned int vlNetwork,unsigned int *vlHandle);

/*Create Port*/
_AFDX_DLL_EXPORT int hwa_aes_create_port (int cardnum,unsigned int vlId,	unsigned int portType,unsigned short dstUDPPort,unsigned short srcUDPPort,unsigned int vlHandle,unsigned int *portId);

/*Send Afdx Data*/
_AFDX_DLL_EXPORT int hwa_aes_send (int cardnum,unsigned int portId,unsigned char *pPacket,int len);

/*Receive Afdx Data*/
_AFDX_DLL_EXPORT int hwa_aes_recv (int cardnum,	unsigned int portId,unsigned char *pPacket,int len,HwaRecvTime *time,unsigned int *network,unsigned int *valid);

/*Receive Afdx Data*/
_AFDX_DLL_EXPORT int hwa_aes_recv_ex(int cardnum, unsigned int hPort,unsigned char* pPacket, int len,int waittime,HwaPktSrc *pInfo);

/*get port overflow info*/
_AFDX_DLL_EXPORT int hwa_aes_mib_port_buf_overflow (int cardnum,unsigned int portId, int direction, unsigned int *value);

/*get mib info*/
_AFDX_DLL_EXPORT int hwa_aes_mib_net_state (int cardnum,HwaNetwork network, HwaNetMibType statType, unsigned int *value);

/*get rx info*/
_AFDX_DLL_EXPORT int hwa_aes_mib_rx_state (int cardnum,HwaRxMibType statType, unsigned int *value);

/*get tx info*/
_AFDX_DLL_EXPORT int hwa_aes_mib_tx_state (int cardnum,HwaTxMibType statType, unsigned int *value);

/*clear mib info*/
_AFDX_DLL_EXPORT int hwa_aes_mib_clear (int cardnum,unsigned int  mask);

/*Close Port*/
_AFDX_DLL_EXPORT int hwa_aes_close_port(int cardnum,unsigned int portId);

/*resolve time*/
_AFDX_DLL_EXPORT int hwa_aes_get_time(HwaRecvTime *time,HwaTime *localtime);

/*get software version*/
_AFDX_DLL_EXPORT int hwa_aes_get_soft_version(unsigned int *version);

/*get hardware version*/
_AFDX_DLL_EXPORT int hwa_aes_get_hard_version(int cardnum,unsigned int *version);

/*get firmware version*/
_AFDX_DLL_EXPORT int hwa_aes_get_firmware_version(int cardnum,unsigned int *version);

/*check phy state*/
_AFDX_DLL_EXPORT int hwa_aes_get_phystate(int cardnum,unsigned int *pState);

/* Monitor Mode*/

/*Monitor mode,start recv*/
_AFDX_DLL_EXPORT int hwa_aes_monitor_start_recv(int cardnum);

/*Monitor mode,stop recv*/
_AFDX_DLL_EXPORT int hwa_aes_monitor_stop_recv(int cardnum);

/*Monitor mode ,reslove packet*/
_AFDX_DLL_EXPORT int hwa_aes_packet_find_next(unsigned char* pRecvBuff,int nSize,unsigned char ** ppPacket,HwaPackInfo* pPacketInfo,unsigned char** pCurPacketPos);

/*creat a sap prot*/
_AFDX_DLL_EXPORT int hwa_aes_create_sap_port(int cardNum,char *portName,unsigned int vlDir,unsigned int Udp,unsigned int subVl,unsigned int *portID);

/*send AFDX data by a sap port*/
_AFDX_DLL_EXPORT int hwa_aes_sap_send(int cardNum,unsigned int portId,unsigned char *buf,unsigned int bufLen, HwaPktSrc sapInfo);

/*receive AFDX data from a sap port*/
_AFDX_DLL_EXPORT int hwa_aes_sap_recv(int cardNum,unsigned int portId,unsigned char *buf,unsigned int bufLen,int waittime,HwaPktSrc *sapInfo);

/*delete a sap port*/
_AFDX_DLL_EXPORT int hwa_aes_close_sap_port(int cardNum,unsigned int portId);

/*creat an ICMP port*/
_AFDX_DLL_EXPORT int hwa_aes_create_icmp(int cardNum,char * portName,unsigned int vlDir,unsigned int * portID);

/*send AFDX data by an ICMP port*/
_AFDX_DLL_EXPORT int hwa_aes_icmp_send(int cardnum,unsigned int portId,unsigned char * buf,int bufLen,char *dstIp);
/*recv AFDX data from an ICMP port */
_AFDX_DLL_EXPORT int hwa_aes_icmp_recv(int cardnum,unsigned int portId,unsigned char * pPacket,int len,int waittime,HwaPktSrc *sapInfo);

/*delete an ICMP port*/
_AFDX_DLL_EXPORT int hwa_aes_close_icmp(int cardNum,unsigned int portId);

/*read FPGA register*/
_AFDX_DLL_EXPORT unsigned int hwa_aes_reg_read(int cardnum,unsigned int addr,int dev);

/*write FPGA register*/
_AFDX_DLL_EXPORT unsigned int hwa_aes_reg_write(int cardnum,unsigned int addr,unsigned int value,int dev);

/*get local time*/
_AFDX_DLL_EXPORT  int hwa_aes_get_local_time(int cardnum,HwaTime *localtime);

/*get soft version*/
_AFDX_DLL_EXPORT void hwa_aes_get_soft_build_version(char *version);


/*inject mode*/

/*start send and set time*/
 _AFDX_DLL_EXPORT  int hwa_aes_inject_start_send(int cardnum,unsigned int time);

 /*stop send*/
_AFDX_DLL_EXPORT  int hwa_aes_inject_stop_send(int cardnum);

/* set ifg */
_AFDX_DLL_EXPORT  int hwa_aes_inject_set_ifg(int cardnum, unsigned int num);

_AFDX_DLL_EXPORT  char* hwa_afdx_get_error();

_AFDX_DLL_EXPORT int  hwa_aes_port_check_data(unsigned int cardnum,unsigned int portId);
_AFDX_DLL_EXPORT int hwa_aes_get_rtc(int cardnum,HwaRecvTime *time);
_AFDX_DLL_EXPORT int hwa_aes_set_rtc(int cardnum,HwaTime *localtime);
#endif
