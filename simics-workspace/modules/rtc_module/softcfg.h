


#ifndef __SOFT_CFG_H__
#define __SOFT_CFG_H__

#define A429_CHANNEL_SIZE  16
#define A429_LABEL_NUM  256

typedef struct
{
	
	unsigned short nPortId;
	unsigned short nSrcUdp;

	unsigned short nSubVlIndex;
	unsigned short nDstUdp;

	unsigned short nPortType;
	unsigned short nA429RecvChannel;

	unsigned int nDstIP;
	unsigned short nUseType;
	unsigned short nDataSrcPatition;
	unsigned short n;/*·ÖÆ¬*/

	unsigned short nLabelOffset;
	unsigned int nIcdid;
	unsigned short nMessageLength;
	unsigned short nRecvBufLength;

}SEND_UDP_STRUCT_t;

typedef struct
{
	unsigned short nPortId;
	unsigned short nRecvUdpPort;
	
	unsigned short nA429RecvChannel1;
	unsigned short nMessageLength;

	unsigned short nRecvBufLength;
	unsigned short nPortType;
	
	unsigned short nUseType;
	unsigned short nVlId;
	unsigned short n;/*·ÖÆ¬*/

	unsigned short nA429RecvChannel2;
	unsigned int nIcdid;
	
}RECV_UDP_STRUCT_t;

typedef struct
{
	unsigned int A429RecvChannel;
	unsigned int A429SendChannel;
	unsigned int nSendCheck;
	unsigned int Labelmap[8];
}A429_STRUCT_t;

typedef struct
{
	unsigned short nHeadLabel;
	unsigned short nTailLabel;
	unsigned int nLabelMap[8];
}ALABEL_STRUCT_t;

typedef struct
{
	unsigned int nSoftCfgLength;
	unsigned short n429PortNum;
	unsigned short n429PortCfgOffset;

	unsigned short nSendUdpNum;
	unsigned short nSendUdpCfgOffset;

	unsigned short nRecvUdpNum;
	unsigned short nRecvUdpCfgOffset;

}SOFTCFG_STRUCT_t;

typedef struct FrameR
{
	SEND_UDP_STRUCT_t * pA429ToUdp;
	ALABEL_STRUCT_t *pAlabel;
	SENDVL_STRUCT_t * pSendVl;
    int nPortId;
	struct FrameR *pNext;
}nFrameR;

/*nomal struct*/
typedef struct
{
	nFrameR * pFrameR;
	unsigned short nUsed;
}A429_TO_UDP_STRUCT_t;


// typedef struct
// {
// 	A429_STRUCT_t nA429To429;
// 	unsigned int nUsed;
// }A429TOA429_STRUCT_t;

typedef struct
{
	unsigned short nUseType;
	unsigned short  nA429SendChannel1;
}AUDPTOA429_STRUCT_t;

typedef struct
{
	unsigned int pAfdxFrameBlock[100];
	unsigned char nFrameNum;
}AFDXFRAME_STRUCT_t;

typedef struct
{
	A429_TO_UDP_STRUCT_t nA429ToUdp[A429_CHANNEL_SIZE][A429_LABEL_NUM];
}A429_TO_UDP_ARRAY;

typedef struct
{
	unsigned short nA429ToA429[20][A429_LABEL_NUM];
}A429_TO_A429_ARRAY;
#endif