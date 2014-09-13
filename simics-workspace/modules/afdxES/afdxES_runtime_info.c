#include "afdxES_runtime_info.h"
#include <stdlib.h>

void set_afdxES_module_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_afdxES_module_runtime_name(void *p) {
    char *name = "A664Model";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_afdxES_module_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "A664模型初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "A664模型初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_afdxES_module_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_afdxES_module_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_afdxES_module_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_main_board_module_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_main_board_module_runtime_name(void *p) {
    char *name = "MainboardModel";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_main_board_module_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "主机板模型初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "主机板模型初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_main_board_module_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_main_board_module_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_main_board_module_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_vxworks_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_vxworks_runtime_name(void *p) {
    char *name = "VxWorks";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_vxworks_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "VxWorks操作系统加载初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "VxWorks操作系统加载初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_vxworks_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_vxworks_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_vxworks_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_a664_driver_middleware_runtime_header(void *p) {
    char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_a664_driver_middleware_runtime_name(void *p) {
    char *name = "A664DriveMiddleware";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_a664_driver_middleware_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        char *description = "A664驱动中间件初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        char *description = "A664驱动中间件初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_a664_driver_middleware_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_a664_driver_middleware_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_a664_driver_middleware_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}
