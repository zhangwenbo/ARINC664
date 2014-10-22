#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>

extern SOCKET ima_client_socket;
extern SOCKET ima_server_socket;

extern int ima_socket_server_init(int portNum);
extern int ima_socket_client_init(int portNum);
extern int ima_socket_recv(unsigned char *recvbuf, int size, SOCKET socketfd);
extern int ima_socket_send(unsigned char *sendbuf, int size, SOCKET socketfd);
