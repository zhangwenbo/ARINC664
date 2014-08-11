#ifndef __TOMIDDLEWARE_H__
#define __TOMIDDLEWARE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>


extern int Init_664_Work_Mode(void);
extern int Send_To_664_Middleware(unsigned char *recvbuf, int size);
extern int Recv_Data_From_664_Middleware(unsigned char *sendbuf, int size);
extern int Recv_Mib_Info_From_664_Middleware(unsigned char *recvbuf, int size);


#endif
