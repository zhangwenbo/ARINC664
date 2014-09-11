#include "untils.h"
#include <WINSOCK2.H>

int netStrlen(char *str) {
#ifndef __DEBUG__
    return htonl(strlen(str) + 1);
#else
    return strlen(str) + 1;
#endif
}

int Strlen(char *str) {
    return strlen(str) + 1;
}

int Ntohl(int data) {
    return ntohl(data);
}

int Htonl(int data) {
    return htonl(data);
}
