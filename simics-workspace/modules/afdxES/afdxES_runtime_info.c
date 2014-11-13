#include "afdxES_runtime_info.h"
#include <stdlib.h>
#include <string.h>

void set_afdxES_module_runtime_header(void *p) {
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_afdxES_module_runtime_name(void *p) {
    const char *name = "A664Model";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_afdxES_module_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        const char *description = "A664模型初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        const char *description = "A664模型初始化失败";
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
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_main_board_module_runtime_name(void *p) {
    const char *name = "MainboardModel";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_main_board_module_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        const char *description = "主机板模型初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        const char *description = "主机板模型初始化失败";
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
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_vxworks_runtime_name(void *p) {
    const char *name = "VxWorks";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_vxworks_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        const char *description = "VxWorks操作系统加载初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        const char *description = "VxWorks操作系统加载初始化失败";
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
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_a664_driver_middleware_runtime_name(void *p) {
    const char *name = "A664DriveMiddleware";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_a664_driver_middleware_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        const char *description = "A664驱动中间件初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        const char *description = "A664驱动中间件初始化失败";
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

void set_afdxES2_mib_runtime_header(void *p) {
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void free_afdxES2_mib_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_a664_middleware_runtime_header(void *p) {
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_a664_middleware_runtime_name(void *p) {
    const char *name = "A664Middleware";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_a664_middleware_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        const char *description = "A664中间件初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        const char *description = "A664中间件初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_a664_middleware_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_a664_middleware_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_a664_middleware_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void set_a664_card_runtime_header(void *p) {
    const char *header = "Hwa";
    int header_length = strlen(header) + 1;

    *(char **)p = (char *)malloc(header_length);
    memcpy(*(char **)p, header, header_length);
}

void set_a664_card_runtime_name(void *p) {
    const char *name = "A664Card";
    int name_length = strlen(name) + 1;

    *(char **)p = (char *)malloc(name_length);
    memcpy(*(char **)p, name, name_length);
}

void set_a664_card_runtime_description(void *p, int flag) {
    if (flag == 0) {            /* success */
        const char *description = "A664板卡初始化成功";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    } else {
        const char *description = "A664板卡初始化失败";
        int description_length = strlen(description) + 1;
        *(char **)p = (char *)malloc(description_length);
        memcpy(*(char **)p, description, description_length);
    }
}

void free_a664_card_runtime_header(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_a664_card_runtime_name(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}

void free_a664_card_runtime_description(void *p) {
    free(*(char **)p);
    *(char **)p = NULL;
}
