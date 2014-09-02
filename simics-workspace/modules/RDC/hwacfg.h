
#ifndef __HWA_CFG_H__
#define __HWA_CFG_H__


typedef struct
{
	unsigned short vlNum;
	unsigned short bag;
	unsigned short period;
	unsigned short offset;

	//unsigned long  dstIP;
	unsigned short vl_use;
	unsigned short RTC_period;

	unsigned short netSelect;
	unsigned short subvlTotal;

	unsigned short allow_redu;
	//unsigned short fragAble;
	//unsigned short allow_slice;
	unsigned short back0;

	//unsigned short fragLen;
	unsigned short maxLen;
	unsigned short minLen;
}SENDVL_STRUCT_t;

typedef struct
{
	unsigned short vlNum;
	unsigned short skewMax;
	unsigned short redundantAble;
	unsigned short integrityAble;

	//unsigned long  dstIP;
	unsigned short vl_use;
	unsigned short back0;

	//unsigned long  blank;
	unsigned short back1;
	unsigned short back2;
}REVVL_STRUCT_t;

typedef struct
{
	unsigned short maxlen;
	unsigned short echoVlNum;
	unsigned short replyVlNum;
	unsigned short replySubVlNum;
	//  unsigned short udpSrcPort;
	//by wj 100226 unsigned short udpDstIPemp;
	unsigned int udpDstIPemp;
	unsigned int blank1;
}ICMP_STRUCT_t;

typedef struct
{
	unsigned short flag;
	unsigned short blank1;
	unsigned short sendvl_num;
	unsigned short revvl_num;
	unsigned short domain;
	unsigned short side;
	unsigned short position;
	unsigned short blank2;

	SENDVL_STRUCT_t sendVlSet[128];
	REVVL_STRUCT_t recvVlSet[256];
	ICMP_STRUCT_t IcmpSet[16];
}HWACFG_STRUCT_t;

#endif /* __HWA_CFG_H__ */