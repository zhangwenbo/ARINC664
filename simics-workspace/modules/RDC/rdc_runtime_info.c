#include "rdc_runtime_info.h"
#include <stdlib.h>

void set_429_middleware_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_429_middleware_runtime_name(void *p) {
    char *name = "A429Middleware";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_429_middleware_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "A429中间件初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "A429中间件初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_429_middleware_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_429_middleware_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_429_middleware_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_rdc_module_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_rdc_module_runtime_name(void *p) {
    char *name = "RDCModel";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_rdc_module_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "RDC模型初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "RDC模型初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_rdc_module_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_rdc_module_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_rdc_module_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_429_card_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_429_card_runtime_name(void *p) {
    char *name = "A429Card";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_429_card_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "A429板卡初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "A429板卡初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_429_card_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_429_card_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_429_card_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}
