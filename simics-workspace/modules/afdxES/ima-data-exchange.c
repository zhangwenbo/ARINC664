#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>

SOCKET ima_client_socket;
SOCKET ima_server_socket;

int ima_sokcet_server_init(int portNum) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);
 
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  
    addr.sin_port = htons(portNum);

    int opt = 1;
    setsockopt(serSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)(&opt), sizeof(opt));

    bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
    
    listen(serSocket, 1);

    SOCKADDR_IN clientsocket;
    int len = sizeof(SOCKADDR);

    if ((ima_server_socket = accept(serSocket, (SOCKADDR*)&clientsocket, &len))!= 0) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    fprintf(stdout, "Socket_server_init ok\n");

    return 0;
}

int ima_socket_client_init(int portNum) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    ima_client_socket = socket(AF_INET, SOCK_STREAM, 0);    

    if (ima_client_socket  == INVALID_SOCKET) {
        fprintf(stderr, "Create socket failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    SOCKADDR_IN serveraddr;   
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portNum);
    serveraddr.sin_addr.S_un.S_addr = inet_addr(INADDR_ANY);   

    if (connect(ima_client_socket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        return -1;
    }

    fprintf(stdout, "Socket_client_init ok\n");

    return 0;
}

int ima_socket_send(unsigned char *sendbuf, int size, SOCKET socketfd) {
    int len = send(socketfd, (char *)sendbuf, size, 0);

    if (len != size) {
        fprintf(stderr, "Socket send failed, error code is %d\n", WSAGetLastError());
    } 

    return len;
}

int ima_socket_recv(unsigned char *recvbuf, int size, SOCKET socketfd) {
    int len = recv(socketfd, (char *)recvbuf, size, 0);

    if (len < 0) {
        fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
    }

    return len;
}
