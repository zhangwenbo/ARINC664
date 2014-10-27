#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>

SOCKET ima_client_socket = INVALID_SOCKET;
SOCKET ima_server_socket = INVALID_SOCKET;

int ima_server_socket_init(int portNum) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

    SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serSocket == INVALID_SOCKET) {
        fprintf(stderr, "Create server socket failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }
 
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    addr.sin_port = htons(portNum);

    int opt = 1;
    setsockopt(serSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)(&opt), sizeof(opt));

    if (bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        fprintf(stderr, "Bind failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }
    
    if (listen(serSocket, 1) == SOCKET_ERROR) {
        fprintf(stderr, "Listen failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }

    SOCKADDR_IN clientsocket;
    int len = sizeof(SOCKADDR_IN);

    if ((ima_server_socket = accept(serSocket, (SOCKADDR*)&clientsocket, &len)) == SOCKET_ERROR) {
        fprintf(stderr, "Accept failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

    fprintf(stdout, "Socket_server_init ok\n");

    return 0;
}

int ima_client_socket_init(int portNum) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

    ima_client_socket = socket(AF_INET, SOCK_STREAM, 0);    

    if (ima_client_socket  == INVALID_SOCKET) {
        fprintf(stderr, "Create client socket failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

    unsigned long ul = 1;
    if (ioctlsocket(ima_client_socket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR) {
        fprintf(stderr, "ioctlsocket failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }

    SOCKADDR_IN serveraddr;   
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portNum);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(ima_client_socket, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
    if ((ret == SOCKET_ERROR) && (WSAGetLastError() != WSAEWOULDBLOCK)) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

    fprintf(stdout, "Socket_client_init ok\n");

    return 0;
}

int ima_socket_send(void *sendbuf, int size, void *socketfd) {
    int len = send(*(SOCKET*)socketfd, (char *)sendbuf, size, 0);

    if (len != size) {
        fprintf(stderr, "Socket send failed, error code is %d\n", WSAGetLastError());
    } 

    return len;
}

int ima_socket_recv(void *recvbuf, int size, void *socketfd) {
    int len = recv(*(SOCKET*)socketfd, (char *)recvbuf, size, 0);

    if ((len < 0) && WSAGetLastError() != WSAEWOULDBLOCK) {
        fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
    }

    return len;
}

void *get_ima_client_socket(void) {
    return &ima_client_socket;
}

void *get_ima_server_socket(void) {
    return &ima_server_socket;
}
