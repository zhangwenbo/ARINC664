#include "untils.h"
#include <string.h>
#include <WINSOCK2.H>

int netStrlen(char *str) {
    return htonl(strlen(str) + 1);
}

int Strlen(char *str) {
    return strlen(str) + 1;
}

/* 
@in, str: 待分割的字符串 
@in, delim: 分隔符字符串 
@in_out, dest: 保存分割后的每个字符串，设为char**的引用，即表示可修改其值 
@out, pCount: 记录一行中分割所得字符串的个数 
*/

void split(char *str, char *delim, char **dest, int *pCount) {
    char *tmp;
    *pCount = 0;

    if (NULL == str || 0 == strlen(str)) {
        return;
    }

    if (NULL == delim || 0 == strlen(str)) {
        return;
    }

    tmp = strtok(str, delim);
    while (tmp != NULL) {
        int j = 0;
        for (; tmp[j] != '\0'; ++j) {
            if (tmp[j] == '\n') {
                break;
            }
            (*dest)[j] = tmp[j];
        }
        (*dest)[j] = '\0';
        ++dest;
        (*pCount)++;

        tmp = strtok(NULL, delim);
    }
}
