#include "untils.h"
#include <string.h>
#include <WINSOCK2.H>

int Strlen(char *str) {
    return htonl(strlen(str) + 1);
}
