#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <WINSOCK2.H>

SOCKET ima_client_socket = INVALID_SOCKET;
SOCKET ima_server_socket = INVALID_SOCKET;

#define BUFFER_SIZE          4
#define BUFFER_MAXLENGTH      1518 * 2

static char frame_buffer[BUFFER_SIZE + BUFFER_MAXLENGTH];
static int pbegin = 0;
static int pend = 0;
static int recv_state;

typedef enum {
    WAIT_FOR_FRAME_SIZE,
    READY_TO_RECV_FRAME,
    READY_TO_HANDLE_FRAME
} RECV_STATE;
    
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

    SOCKADDR_IN serveraddr;   
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portNum);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(ima_client_socket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

    unsigned long ul = 1;
    if (ioctlsocket(ima_client_socket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR) {
        fprintf(stderr, "ioctlsocket failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }

    fprintf(stdout, "Socket_client_init ok\n");

    return 0;
}

void ima_socket_send(void *sendbuf, int size, void *socketfd) {
    if (send(*(SOCKET*)socketfd, (char *)&size, size, 0) != size) {
        fprintf(stderr, "Socket send failed, error code is %d\n", WSAGetLastError());
    } 

    if (send(*(SOCKET*)socketfd, (char *)sendbuf, size, 0) != size) {
        fprintf(stderr, "Socket send failed, error code is %d\n", WSAGetLastError());
    } 
}

static int chars_to_int(void) {
    int ret = 0;
    if ((pbegin < pend) && (pend - pbegin == BUFFER_SIZE) &&
        (pbegin < BUFFER_MAXLENGTH) && (pend < BUFFER_MAXLENGTH)) {
        ret = (frame_buffer[pbegin] << 24) |
              (frame_buffer[pbegin+1] << 16) |
              (frame_buffer[pbegin+2] << 8) |
              (frame_buffer[pbegin+3]);
    } else if ((pbegin > pend) && (pend + BUFFER_MAXLENGTH - pbegin == BUFFER_SIZE) &&
               (pbegin < BUFFER_MAXLENGTH) && (pend < BUFFER_MAXLENGTH)) {
        int i = 0;
        int j = 0;
        for (; i < BUFFER_MAXLENGTH - pbegin; ++i) {
            ret |= (frame_buffer[pbegin + i] << (24 - i * 8));
        }
        for (; j < pend; ++j) {
            ret |= (frame_buffer[j] << (j * 8));
        }
    } else {
        fprintf(stderr, "Error, pbegin and pend value is wrong!\n");
        exit(1);
    }

    return ret;
}

int ima_socket_recv(void *recvbuf, int size, void *socketfd) {
    if (recv_state == WAIT_FOR_FRAME_SIZE) {
        int frame_size = recv(*(SOCKET*)socketfd, frame_buffer + pend, BUFFER_SIZE - (pend % BUFFER_SIZE), 0); /* size == BUFFER_SIZE (sizeof(int)) */
        
        if ((frame_size > 0) && (frame_size != BUFFER_SIZE)) {
            pbegin = pend;
            if (pend + frame_size < BUFFER_MAXLENGTH) {
                pend += frame_size;
            } else {
                pend = pend + frame_size - BUFFER_MAXLENGTH;
            }
            return 0;
        } else if (frame_size < 0) { /* 非阻塞 */
            switch (WSAGetLastError()) {
                case WSAEWOULDBLOCK:
                    return 0;
                default:
                    fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                    exit(1);
            }
        } else {
            recv_state = READY_TO_RECV_FRAME;
            // char[0..3] -> int;
            return ima_socket_recv(recvbuf, chars_to_int(), socketfd);
        }
    } else if (recv_state == READY_TO_RECV_FRAME) {
        int recved_frame_size = recv(*(SOCKET*)socketfd, frame_buffer + pend, size, 0); /* size == frame size */
        if ((recved_frame_size > 0) && (recved_frame_size != size)) {
            pbegin = pend;
            if (pend + recved_frame_size < BUFFER_MAXLENGTH) {
                pend += recved_frame_size;
            } else {
                pend = pend + recved_frame_size - BUFFER_MAXLENGTH;
            }            
            return 0;
        } else if (recved_frame_size < 0) { /* 非阻塞 */
            switch (WSAGetLastError()) {
                case WSAEWOULDBLOCK:
                    return 0;
                default:
                    fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                    exit(1);
            }
        } else {
            recv_state = READY_TO_HANDLE_FRAME;
            return ima_socket_recv(recvbuf, recved_frame_size, socketfd);
        }
    } else if (recv_state == READY_TO_HANDLE_FRAME) {
        memcpy(recvbuf, frame_buffer + pbegin, size);
        recv_state = WAIT_FOR_FRAME_SIZE;
        
        return size;
    }
}

void *get_ima_client_socket(void) {
    return &ima_client_socket;
}

void *get_ima_server_socket(void) {
    return &ima_server_socket;
}
