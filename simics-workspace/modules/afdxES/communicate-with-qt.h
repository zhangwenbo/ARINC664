#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>

extern SOCKET client_socket;

extern int qt_socket_init(void);
extern int qt_socket_recv(unsigned char *recvbuf, int size);
extern int qt_socket_send(unsigned char *sendbuf, int size);
