#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>

SOCKET client_socket;

/*
extern int qt_socket_init(void);
extern int qt_socket_recv(unsigned char *recvbuf, int size);
extern int qt_socket_send(unsigned char *sendbuf, int size);
*/

int qt_socket_init(void) {
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
    serveraddr.sin_port = htons(3237);
    serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");   

    if (connect(client_socket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    fprintf(stdout, "Socket_init ok\n");

    return 0;
}

int qt_socket_send(unsigned char *sendbuf, int size) {
    int len = send(client_socket, (char *)sendbuf, size, 0);
    if (len == size) {
        fprintf(stdout, "Socket send sucessfully, send %d bytes.\n", len);
        return len;
    } else {
        fprintf(stderr, "Socket send failed, size = %d, sended len = %d!\n", size, len);
        return 0;
    }
}


void qt_socket_transmit_module_runtime_info(int msg_type) {
    
}
