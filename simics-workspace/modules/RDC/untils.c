#include "untils.h"
#include <string.h>
#include <WINSOCK2.H>

int netStrlen(char *str) {
    return htonl(strlen(str) + 1);
}

int Strlen(char *str) {
    return strlen(str) + 1;
}
