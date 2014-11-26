#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <winsock2.h>

// #define __TCP__    1

SOCKET ima_client_socket = INVALID_SOCKET;
SOCKET ima_server_socket = INVALID_SOCKET;

static char frame[1518];

typedef enum {
    WAIT_FOR_FRAME_SIZE,
    READY_TO_RECV_FRAME,
    BEGIN_TO_HANDLE_FRAME
} RECV_STATE;

static int recv_state;


typedef enum {
    IMA_LOCAL_INIT_ADDR,
    IMA_PEER_INIT_ADDR
} ADDR_TYPE;

#define LOCAL_IP "127.0.0.1"
#define PEER_IP "192.9.230.156"   /* 用于发送，是对端的IP */

#ifndef __TCP__
struct sockaddr_in ima_server_init_addr;
struct sockaddr_in ima_client_init_addr;

static char send_buffer[2000];
static char recv_buffer[2000];
#else
#endif

int ima_server_socket_init(int localPortNum, int peerPortNum) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }
#ifdef __TCP__
    SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);
#else
    SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, 0);
#endif
    
    if (serSocket == INVALID_SOCKET) {
        fprintf(stderr, "Create server socket failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

#ifdef __TCP__
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    addr.sin_port = htons(localPortNum);
#else
    struct sockaddr_in addr;    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(localPortNum);
	
	struct sockaddr_in clientaddr;
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.S_un.S_addr = inet_addr(PEER_IP);
    clientaddr.sin_port = htons(localPortNum); /* 对端的接收端口, 本地的发送端口 */

    ima_server_init_addr = clientaddr; /* send时用到的地址信息 */
#endif
    
    int opt = 1;
    setsockopt(serSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)(&opt), sizeof(opt));

#ifdef __TCP__
    if (bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        fprintf(stderr, "Bind failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }
#else
    /* need it?
    if (bind(serSocket, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf ("Bind failed with error code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    */
#endif

#ifdef __TCP__    
    if (listen(serSocket, 1) == SOCKET_ERROR) {
        fprintf(stderr, "Listen failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }
#else
#endif

#ifdef __TCP__    
    SOCKADDR_IN clientsocket;
    int len = sizeof(SOCKADDR_IN);

    if ((ima_server_socket = accept(serSocket, (SOCKADDR*)&clientsocket, &len)) == SOCKET_ERROR) {
        fprintf(stderr, "Accept failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }
#else
    ima_server_socket = serSocket;
#endif
    
    fprintf(stdout, "Socket_server_init ok\n");

    return 0;
}

int ima_client_socket_init(int peerPortNum, int localPortNum) {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr, "WSAStartup failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

#ifdef __TCP__
    ima_client_socket = socket(AF_INET, SOCK_STREAM, 0);
#else
    ima_client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
    
    if (ima_client_socket  == INVALID_SOCKET) {
        fprintf(stderr, "Create client socket failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }

#ifdef __TCP__
    SOCKADDR_IN serveraddr;   
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(peerPortNum);
    serveraddr.sin_addr.s_addr = inet_addr(PEER_IP);
#else
    struct sockaddr_in serveraddr;
    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(peerPortNum); /* 对端的发送端口 */
    serveraddr.sin_addr.S_un.S_addr = inet_addr(PEER_IP); /* 对端IP */
    
    ima_client_init_addr = serveraddr; 
#endif

#ifdef __TCP__
    if (connect(ima_client_socket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        fprintf(stderr, "Connect failed, error code is %d.\n", WSAGetLastError());
        exit(1);
    }
#else
    struct sockaddr_in addr;    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(peerPortNum); /* 对端端口 */

    if (bind(ima_client_socket, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf ("Bind failed with error code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }    
#endif

    unsigned long ul = 1;
    if (ioctlsocket(ima_client_socket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR) {
        fprintf(stderr, "ioctlsocket failed, error code is %d\n", WSAGetLastError());
        exit(1);
    }

    fprintf(stdout, "Socket_client_init ok\n");

    return 0;
}

void ima_socket_send(void *sendbuf, int size, void *socketfd, int addr_type) {
#ifndef __TCP__
    struct sockaddr_in addr;
    switch (addr_type) {
        case IMA_LOCAL_INIT_ADDR:
            addr = ima_server_init_addr;
            break;
        case IMA_PEER_INIT_ADDR:
            addr = ima_client_init_addr;
            break;
        default:
            fprintf(stderr, "Fatal error: unkown addr type!\n");
            break;
    }
#endif
        
#ifdef __TCP__
    if (send(*(SOCKET*)socketfd, (char *)&size, sizeof(size), 0) != sizeof(size)) {
        fprintf(stderr, "Socket send failed, error code is %d\n", WSAGetLastError());
    } 

    if (send(*(SOCKET*)socketfd, (char *)sendbuf, size, 0) != size) {
        fprintf(stderr, "Socket send failed, error code is %d\n", WSAGetLastError());
    }
#else
    memset(send_buffer, 0, 2000);
    memcpy(send_buffer, sendbuf, size);
    
	// fprintf(stderr, "Send to addr = %d, and port = %d\n", addr.sin_addr.S_un.S_addr, addr.sin_port);
	
    if (sendto(*(SOCKET*)socketfd, send_buffer, size,
               0, (struct sockaddr *)&addr, sizeof(addr)) != size) {
        fprintf(stderr, "sendto() failed with error code: %d\n", WSAGetLastError());
    }
#endif
}

static int chars_to_int(char *array) {
    int ret = (array[3] << 24) |
              (array[2] << 16) |
              (array[1] << 8) |
              (array[0]);

    return ret;
}

int ima_socket_recv(void *recvbuf, int size, void *socketfd, int addr_type) { /* 最后一个参数用作数组下标也不错 */
#ifndef __TCP__
    struct sockaddr_in addr;
    switch (addr_type) {
        case IMA_LOCAL_INIT_ADDR:
            addr = ima_server_init_addr;
            break;
        case IMA_PEER_INIT_ADDR:
            addr = ima_client_init_addr;
            break;
        default:
            fprintf(stderr, "Fatal error: unkown addr type!\n");
            break;
    }
    int addr_len = sizeof(addr);
#endif

#ifdef __TCP__
    if (recv_state == WAIT_FOR_FRAME_SIZE) {
        char frame_size[4];
        int ret = recv(*(SOCKET*)socketfd, (char*)&frame_size, 4, 0);


        if (ret > 0) {
            if (ret != 4) {
                while (4 - ret) {
                    int ret1 = recv(*(SOCKET*)socketfd, frame_size + ret, 4 - ret, 0);

                    if (ret1 > 0) {
                        ret += ret1;
                    } else {
                        switch (WSAGetLastError()) {
                            case WSAEWOULDBLOCK:
                                break;
                            default:
                                fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                                exit(1);
                        }                        
                    }
                }
            }

            recv_state = READY_TO_RECV_FRAME;
            
            return ima_socket_recv(recvbuf, chars_to_int((char*)&frame_size), socketfd, addr_type);
        } else {
            switch (WSAGetLastError()) {
                case WSAEWOULDBLOCK:
                    return 0;
                default:
                    fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                    exit(1);
            }                        
        }
    } else if (recv_state == READY_TO_RECV_FRAME) {
        int ret = recv(*(SOCKET*)socketfd, (char*)&frame, size, 0);

        if (ret > 0) {
            if (ret != size) {
                while (size - ret) {
                    int ret1 = recv(*(SOCKET*)socketfd, frame + ret, size - ret, 0);

                    if (ret1 > 0) {
                        ret += ret1;
                    } else {
                        switch (WSAGetLastError()) {
                            case WSAEWOULDBLOCK:
                                break;
                            default:
                                fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                                exit(1);
                        }                        
                    }
                }
            }

            recv_state = BEGIN_TO_HANDLE_FRAME;
            return ima_socket_recv(recvbuf, size, NULL, addr_type);
        } else {
            switch (WSAGetLastError()) {
                case WSAEWOULDBLOCK:
                    return size;
                default:
                    fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                    exit(1);
            }                                    
        }
    } else if (recv_state == BEGIN_TO_HANDLE_FRAME) {
        memcpy(recvbuf, frame, size);
        memset(frame, 0, 1518);
        return size;
    } else {
        fprintf(stderr, "Fatal error, unsupported recv state!\n");
        exit(1);
    }
#else
    if (recv_state == WAIT_FOR_FRAME_SIZE) {
        memset(recv_buffer, 0, 2000);
        int ret = recvfrom(*(SOCKET*)socketfd, recv_buffer, 2000, 0,
                           (struct sockaddr *)&addr, &addr_len); /* notice here */
		
		// fprintf(stderr, "recv from addr = %d, and port = %d\n", addr.sin_addr.S_un.S_addr, addr.sin_port);
        if (ret > 0) {
            recv_state = BEGIN_TO_HANDLE_FRAME;
            memcpy(recvbuf, recv_buffer, ret);
            return ret;
        } else {
            switch (WSAGetLastError()) {
                case WSAEWOULDBLOCK:
                    return 0;
                default:
                    fprintf(stderr, "Socket recv failed, error code is %d\n", WSAGetLastError());
                    exit(1);
            }                                    
        }
    }
#endif
}

void *get_ima_client_socket(void) {
    return &ima_client_socket;
}

void *get_ima_server_socket(void) {
    return &ima_server_socket;
}

int get_recv_state(void) {
    return recv_state;
}

void change_recv_state(void) {
    recv_state = WAIT_FOR_FRAME_SIZE;
}
