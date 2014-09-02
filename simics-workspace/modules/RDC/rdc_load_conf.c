// filetest.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "hwacfg.h"
#include "softcfg.h"

typedef struct
{
	char version[16];
	char SqlName[32];
	char cfgDate[16];
}CFG_HEADER_STRUCT_t;

#define SOFT_CFG_OFFSET 0x1E10
#define HARD_CFG_SIZE   0x1D10

CFG_HEADER_STRUCT_t cfg_header;
HWACFG_STRUCT_t     cfg_hwa;
SOFTCFG_STRUCT_t    cfg_soft;

SEND_UDP_STRUCT_t *pSendUdpCfg;
RECV_UDP_STRUCT_t *pRecvUdpCfg;
unsigned int nSendUdpCfgCnt;
unsigned int nRecvUdpCfgCnt;
	
#define A429_CHANNEL_SIZE  16
#define A429_LABEL_NUM  256



A429_TO_UDP_ARRAY A429ToUdpArry;
A429_TO_A429_ARRAY A429To429Arry;
/*A429TOA429_STRUCT_t        nA429ToA429[A429_CHANNEL_SIZE][A429_LABEL_NUM];*/


AUDPTOA429_STRUCT_t nUdpTo429[0x10000];

AFDXFRAME_STRUCT_t *pAfdxFrameBlock;
int AfdxFrameBlockNum;

SEND_UDP_STRUCT_t * getSendUdpCfg()
{
	return pSendUdpCfg;
}

RECV_UDP_STRUCT_t * getRecvUdpCfg()
{
	return pRecvUdpCfg;
}

 int getSendUdpCnt()
{
	return nSendUdpCfgCnt;
}

 int getRecvUdpCnt()
{
	return nRecvUdpCfgCnt;
}

int getAfdxFrameBlockNum()
{
	return AfdxFrameBlockNum;
} 
A429_TO_A429_ARRAY* GetnA429ToA429()
{
	return &A429To429Arry;
}

A429_TO_UDP_ARRAY* GetnA429ToAudp()
{
	return &A429ToUdpArry;
}

AFDXFRAME_STRUCT_t *getpAfdxFrameBlock()
{
	return pAfdxFrameBlock;
}

AUDPTOA429_STRUCT_t* GetnUdpTo429()
{
    return &nUdpTo429;
}

HWACFG_STRUCT_t *GetHwaCfg()
{
	return &cfg_hwa;
}

int ReadHwaCfg(FILE *fp)
{
	int nReadCnt=0;
	int nHwaHeadSize = 0;
	int nHwaSendVlSize = 0;
	int nHwaRecvVlSize = 0;
	int nHwaIcmpSize = 0;
	char buf[0x1D10] = {0};
	//fseek(fp,0x100, SEEK_SET);
	rewind(fp);
	fseek(fp,0x100, SEEK_SET);
	nReadCnt = fread(buf,sizeof(char),0x1D10,fp);

	nHwaHeadSize = 8* sizeof(unsigned short);
	memcpy(&cfg_hwa,buf,nHwaHeadSize);

	nHwaSendVlSize = 128*sizeof(SENDVL_STRUCT_t);
	memcpy(cfg_hwa.sendVlSet,buf+nHwaHeadSize,nHwaSendVlSize);

	nHwaRecvVlSize = 256*sizeof(REVVL_STRUCT_t);
	memcpy(cfg_hwa.recvVlSet,buf+nHwaHeadSize+nHwaSendVlSize,nHwaRecvVlSize);

	nHwaIcmpSize = 16*sizeof(ICMP_STRUCT_t);
	memcpy(cfg_hwa.IcmpSet,buf+nHwaHeadSize+nHwaSendVlSize+nHwaRecvVlSize,nHwaIcmpSize);
	

	return 0;
}

int ReadSoftCfg(FILE *fp)
{
	int nReadCnt=0;
	int nRet;
	unsigned char buf[16] = {0};
	int ret = 0;
	int i=0,j=0,k=0;
	unsigned int nLabelBaseAddr;
	
	int nA429ChannelNum;
	
	A429_STRUCT_t     *pA429Cfg;
	unsigned int nA429CfgCnt;

	ALABEL_STRUCT_t  *pAlabelCfg;
	unsigned int nAlabelCfgCnt;
	
	ALABEL_STRUCT_t *pAlabel;
	nFrameR * pFrameR;
	unsigned int softLen=0;
	int nFileOffset;
	rewind(fp);
	fseek(fp,SOFT_CFG_OFFSET, SEEK_SET);
	ret = sizeof(SOFTCFG_STRUCT_t);
	nReadCnt = fread(buf,sizeof(char),ret,fp);
	memcpy(&cfg_soft,buf,ret);
	softLen += nReadCnt;
    nSendUdpCfgCnt = cfg_soft.nSendUdpNum;
    nRecvUdpCfgCnt = cfg_soft.nRecvUdpNum;
	/*read send udp cfg*/
	rewind(fp);
	fseek(fp,SOFT_CFG_OFFSET+cfg_soft.nSendUdpCfgOffset, SEEK_SET);
	long fileoffset=ftell(fp);
	ret = cfg_soft.nSendUdpNum*sizeof(SEND_UDP_STRUCT_t);
	pSendUdpCfg = (SEND_UDP_STRUCT_t *)malloc(cfg_soft.nSendUdpNum*sizeof(SEND_UDP_STRUCT_t));
	nReadCnt = fread(pSendUdpCfg,sizeof(SEND_UDP_STRUCT_t),cfg_soft.nSendUdpNum,fp);
	softLen += nReadCnt;
	fileoffset=ftell(fp);
	nRet=feof(fp);
	pAfdxFrameBlock = (AFDXFRAME_STRUCT_t *)malloc(cfg_soft.nSendUdpNum*sizeof(AFDXFRAME_STRUCT_t));
	AfdxFrameBlockNum = cfg_soft.nSendUdpNum;
	/*read recv udp cfg*/
	rewind(fp);
	fseek(fp,SOFT_CFG_OFFSET+cfg_soft.nRecvUdpCfgOffset, SEEK_SET);
	ret = sizeof(RECV_UDP_STRUCT_t);
	pRecvUdpCfg = (RECV_UDP_STRUCT_t *)malloc(cfg_soft.nRecvUdpNum*sizeof(RECV_UDP_STRUCT_t));
	nReadCnt = fread(pRecvUdpCfg,sizeof(char),cfg_soft.nRecvUdpNum*sizeof(RECV_UDP_STRUCT_t),fp);
	softLen += nReadCnt;

	/*read  A429 cfg*/
	rewind(fp);
	fseek(fp,SOFT_CFG_OFFSET+cfg_soft.n429PortCfgOffset, SEEK_SET);
	ret = cfg_soft.n429PortNum*sizeof(A429_STRUCT_t);
	pA429Cfg = (A429_STRUCT_t *)malloc(20*20*sizeof(A429_STRUCT_t));
	nReadCnt = fread(pA429Cfg,sizeof(char),cfg_soft.n429PortNum*sizeof(A429_STRUCT_t),fp);
	softLen += nReadCnt;
    
	nLabelBaseAddr = SOFT_CFG_OFFSET+cfg_soft.n429PortCfgOffset+20*20*sizeof(A429_STRUCT_t);
	for (i=0;i<cfg_soft.nSendUdpNum;i++)
	{
		rewind(fp);
		nFileOffset =nLabelBaseAddr + pSendUdpCfg[i].nLabelOffset;
		fseek(fp,nFileOffset, SEEK_SET);
		pAlabel = (ALABEL_STRUCT_t *)malloc(sizeof(ALABEL_STRUCT_t));
		nReadCnt = fread(pAlabel,sizeof(char),sizeof(ALABEL_STRUCT_t),fp);
		
		for(j=0;j<256;j++)
		{
			if(pAlabel->nLabelMap[j/32]&(1<<(j%32)))
			{
				printf("%03d_",j);
				if (pSendUdpCfg[i].nA429RecvChannel > 20)
				{
					printf("Channel err!\n");
				}
				if (pSendUdpCfg[i].nA429RecvChannel > 16)
				{
					//printf("Channel not support:0x%x!i:%x\n",pSendUdpCfg[i].nA429RecvChannel,i);
					continue;
				}
                nA429ChannelNum = pSendUdpCfg[i].nA429RecvChannel;
				A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].nUsed += 1;
				if (A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].nUsed==1)
				{
					A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR = (nFrameR *)malloc(sizeof(nFrameR));
					A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR->pA429ToUdp = &pSendUdpCfg[i];
					A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR->pAlabel = pAlabel;
					A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR->pNext = NULL;
                    A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR->nPortId = i;
                   #if 0
					for (k=0;k<128;k++)
					{
						if ((A429ToUdpArry.nA429ToUdp[pSendUdpCfg[i].nA429RecvChannel][j].pFrameR->pA429ToUdp->nSubVlIndex >> 2) == cfg_hwa.sendVlSet[k].vlNum)
						{
							A429ToUdpArry.nA429ToUdp[pSendUdpCfg[i].nA429RecvChannel][j].pFrameR->pSendVl  = &cfg_hwa.sendVlSet[k];
						}
					}
                    #endif
				}else{
					pFrameR = (nFrameR *)malloc(sizeof(nFrameR));
					pFrameR->pNext = A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR;
					pFrameR->pA429ToUdp = &pSendUdpCfg[i];
					pFrameR->pAlabel = pAlabel;
                    pFrameR->nPortId  = i;
					#if 0
                    for (k=0;k<128;k++)
					{
						if ((A429ToUdpArry.nA429ToUdp[pSendUdpCfg[i].nA429RecvChannel][j].pFrameR->pA429ToUdp->nSubVlIndex >> 2) == cfg_hwa.sendVlSet[k].vlNum)
						{
							pFrameR->pSendVl  = &cfg_hwa.sendVlSet[k];
						}
					}
                    #endif
					A429ToUdpArry.nA429ToUdp[nA429ChannelNum][j].pFrameR = pFrameR;
				}
				
				
// 				nA429ToUdp[pSendUdpCfg[i].nA429RecvChannel][j].nA429ToUdp = pSendUdpCfg[cfg_soft.nSendUdpNum];
// 				nA429ToUdp[pSendUdpCfg[i].nA429RecvChannel][j].nHeadLabel = pAlabel->nHeadLabel;
// 				nA429ToUdp[pSendUdpCfg[i].nA429RecvChannel][j].nHeadLabel = pAlabel->nTailLabel;
				
			}
		}
		printf("head[%03d]_",pAlabel->nHeadLabel);
		printf("tail[%03d]_",pAlabel->nTailLabel);
		printf("portID:%d\n",i);
// 		free(pAlabel);
// 		pAlabel = NULL;
	 }
// 	free(pRecvUdpCfg);
// 	pRecvUdpCfg = NULL;

	for (i=0;i<20;i++)
	{
		for (k=0;k<20;k++)
		{
			for (j=0;j<256;j++)
			{
				if (pA429Cfg[i*20+k].Labelmap[j/32]&(1<<(j%32)))
				{
					A429To429Arry.nA429ToA429[i][j] |= 1<<k;;
				}	
			}
		}
		
	}
	
	for (i=0;i<cfg_soft.nRecvUdpNum;i++)
	{
		if (pRecvUdpCfg[i].nRecvUdpPort > 65535)
		{
			printf("nRecvUdpPort err!\n");
			continue;
		}
		nUdpTo429[pRecvUdpCfg[i].nRecvUdpPort].nA429SendChannel1 |= pRecvUdpCfg[i].nA429RecvChannel1;
		nUdpTo429[pRecvUdpCfg[i].nRecvUdpPort].nUseType =  pRecvUdpCfg[i].nUseType;
	}
// 	free(pA429Cfg);
// 	pA429Cfg = NULL;	

	
	return 0;
}

int ReadHeaderCfg(FILE *fp)
{
	int nReadCnt=0;
	char buf[0x100] = {0};
	rewind(fp);
	nReadCnt = fread(buf,sizeof(char),0x100,fp);
	memcpy(cfg_header.version,buf,16);
	memcpy(cfg_header.SqlName,buf+16,32);
	memcpy(cfg_header.cfgDate,buf+48,16);
	printf("version:%s!\n",cfg_header.version);
	printf("sqlname:%s!\n",cfg_header.SqlName);
	printf("create date:%s!\n",cfg_header.cfgDate);
	return 0;
}

int hwa_load_conf_file()
{
	/*
	FILE *fp;
	char ch;
	fp=fopen("d:\\a.txt","r");
	ch = fgetc(fp);
	printf("ch is:0x%x\n",ch);
	*/
	FILE *fp;
	fp=fopen("d:\\CARRDC_L_CFG.bin","rb");
	memset(&A429ToUdpArry,0,sizeof(A429ToUdpArry));
//	memset(nA429ToA429,0,20*256*sizeof(A429TOA429_STRUCT_t));
	ReadSoftCfg(fp);
	ReadHeaderCfg(fp);
	ReadHwaCfg(fp);
	
	return 0;
}

#if 0
void send429(char channel,unsigned int data)
{
	
}
void nSendToAfdx()
{

}
void A429To429(char channel,unsigned int data)
{
	char nLabel;
	nLabel = data&0xff;
	int i = 0;
	for (i=0;i<16;i++)
	{
		if (nA429ToA429[channel][nLabel]&(1<<i))
		{
			send429(i,data);
		}
		
	}
	
	
}


void A429ToAfdx(char channel,unsigned int data)
{
	int i = 0;
	nFrameR * pFrameR;
	char nLabel;
	unsigned int nData;
	int nA429ToAfdxCfgIndex = 0;
	unsigned int nFramebit = 0; 
	unsigned char nArryIndex,nBitIndex;
	nLabel = data&0xff;
	nData = (data&0x1FFFFC00)>>10;
	
	if(nA429ToUdp[channel][nLabel].nUsed ==0)
	{
		A429To429(channel,data);
	}else{
		pFrameR = nA429ToUdp[channel][data&0xff].pFrameR;
		for (i=0;i<nA429ToUdp[channel][data&0xff].nUsed;i++)
		{
			if (pFrameR->pA429ToUdp->nUseType == 0)
			{
				nA429ToAfdxCfgIndex = pFrameR->pA429ToUdp->nPortId;
				if (pFrameR->pAlabel->nHeadLabel == nLabel)
				{
					pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum = 0;

					nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
					nArryIndex = nFramebit/32;
					nBitIndex = nFramebit%32;
					if (32-nBitIndex > 19)
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
					}else 
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
					}
					pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum++;
				}else if (pFrameR->pAlabel->nTailLabel == nLabel)
				{
					nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
					nArryIndex = nFramebit/32;
					nBitIndex = nFramebit%32;
					if (32-nBitIndex > 19)
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
					}else 
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
					}
					nSendToAfdx();
					pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum = 0;
				}else{
					
					nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
					nArryIndex = nFramebit/32;
					nBitIndex = nFramebit%32;
					if (32-nBitIndex > 19)
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
					}else 
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
					}
					pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum++;
					if (pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum > 100)
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum = 0;
					}
				}


			}
		}
		
		
		


	}

}



method AfdxTo429()
{
	local int i = 0;
	local nFrameR * pFrameR;
	local char nLabel;
	local uint32 nData;
	local int nA429ToAfdxCfgIndex = 0;
	local uint32 nFramebit = 0; 
	local uint8 nArryIndex;
	local uint8 nBitIndex;
	nLabel = data&0xff;
	nData = (data&0x1FFFFC00)>>10;
	local BLOCK_TIME_STRUCT_t * pBlockTime;
	local uint8 nAfdxFlag;/*组包方式*/
	
	pBlockTime = cast($regs.afdx_block_adr,BLOCK_TIME_STRUCT_t *);
	
	local A429_TO_UDP_STRUCT_t ** nA429ToUdp;
	local AFDXFRAME_STRUCT_t *pAfdxFrameBlock;

	nA429ToUdp = GetnA429ToAudp();	
	pAfdxFrameBlock=getpAfdxFrameBlock();
	
	

	if(nA429ToUdp[channel][nLabel].nUsed ==0)/*如果没用则转发到429*/
	{
		call $A429To429(channel,data);
	}else{																	/*转发AFDX*/
		if(nAfdxFlag == 1)/*定时组包*/
		{
			pFrameR = nA429ToUdp[channel][data&0xff].pFrameR;
			for (i=0;i<nA429ToUdp[channel][data&0xff].nUsed;i++)
			{
				if(i>0)
				{
					pFrameR= pFrameR->pNext;
				}
					if(pFrameR->pA429ToUdp->nUseType == 0)
					{
						nA429ToAfdxCfgIndex = pFrameR->pA429ToUdp->nPortId;
						nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
						nArryIndex = nFramebit/32;
						nBitIndex = nFramebit%32;
						if (32-nBitIndex > 19)
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
						}else 
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
						}
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum++;
						
					}
						
				
			}
		}else{/*顺序组包*/
			pFrameR = nA429ToUdp[channel][data&0xff].pFrameR;
			for (i=0;i<nA429ToUdp[channel][data&0xff].nUsed;i++)
			{
				if(i>0)
				{
					pFrameR= pFrameR->pNext;
				}
				if (pFrameR->pA429ToUdp->nUseType == 0)/*正常模式则检查是否头包尾包*/
				{
					nA429ToAfdxCfgIndex = pFrameR->pA429ToUdp->nPortId;
					if (pFrameR->pAlabel->nHeadLabel == nLabel)     /*头包*/
					{
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum = 0;
	
						nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
						nArryIndex = nFramebit/32;
						nBitIndex = nFramebit%32;
						if (32-nBitIndex > 19)
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
						}else 
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
						}
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum++;
						if(pFrameR->pAlabel->nTailLabel == nLabel)
							{
								call $nSendToAfdx();
								continue ;
							}else{
								inline $AfdxTimer.post(400000,&(pBlockTime->pAfdxBlockTime[nA429ToAfdxCfgIndex]));
							}
					}else if (pFrameR->pAlabel->nTailLabel == nLabel)/*尾包*/
					{
						nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
						nArryIndex = nFramebit/32;
						nBitIndex = nFramebit%32;
						if (32-nBitIndex > 19)
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
						}else 
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
						}
						call $nSendToAfdx();
						inline $AfdxTimer.remove(&(pBlockTime->pAfdxBlockTime[nA429ToAfdxCfgIndex]));
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum = 0;
					}else{
	
						nFramebit=pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum*19;
						nArryIndex = nFramebit/32;
						nBitIndex = nFramebit%32;
						if (32-nBitIndex > 19)
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData<<(32-nBitIndex));
						}else 
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex] |= (nData>>(19-(32-nBitIndex)));
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].pAfdxFrameBlock[nArryIndex+1] |= (nData<<(32-nBitIndex));
						}
						pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum++;
						if (pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum > 100)
						{
							pAfdxFrameBlock[nA429ToAfdxCfgIndex].nFrameNum = 0;
						}
					}
				}/*usetype*/
			}/*for*/
		}/*end of 顺序组包*/
	}



}
#endif