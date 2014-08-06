#ifndef __TO42MIDDLE_H__
#define __TO42MIDDLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>


extern int socket_init(void);
extern int socket_recv(unsigned char *recvbuf, int size);
extern int socket_send(unsigned char *sendbuf, int size);

#endif
