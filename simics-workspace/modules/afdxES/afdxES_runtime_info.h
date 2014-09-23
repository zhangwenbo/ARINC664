#ifndef RDC_RUNTIME_INFO_H
#define RDC_RUNTIME_INFO_H

extern void set_afdxES_module_runtime_header(void *p);
extern void set_afdxES_module_runtime_name(void *p);
extern void set_afdxES_module_runtime_description(void *p, int flag);
extern void free_afdxES_module_runtime_header(void *p);
extern void free_afdxES_module_runtime_name(void *p);
extern void free_afdxES_module_runtime_description(void *p);

extern void set_main_board_module_runtime_header(void *p);
extern void set_main_board_module_runtime_name(void *p);
extern void set_main_board_module_runtime_description(void *p, int flag);
extern void free_main_board_module_runtime_header(void *p);
extern void free_main_board_module_runtime_name(void *p);
extern void free_main_board_module_runtime_description(void *p);

extern void set_vxworks_runtime_header(void *p);
extern void set_vxworks_runtime_name(void *p);
extern void set_vxworks_runtime_description(void *p, int flag);
extern void free_vxworks_runtime_header(void *p);
extern void free_vxworks_runtime_name(void *p);
extern void free_vxworks_runtime_description(void *p);

extern void set_a664_driver_middleware_runtime_header(void *p);
extern void set_a664_driver_middleware_runtime_name(void *p);
extern void set_a664_driver_middleware_runtime_description(void *p, int flag);
extern void free_a664_driver_middleware_runtime_header(void *p);
extern void free_a664_driver_middleware_runtime_name(void *p);
extern void free_a664_driver_middleware_runtime_description(void *p);

extern void set_afdxES2_mib_runtime_header(void *p);
extern void set_afdxES2_mib_runtime_name(void *p);
extern void set_afdxES2_mib_runtime_description(void *p, int flag);
extern void free_afdxES2_mib_runtime_header(void *p);
extern void free_afdxES2_mib_runtime_name(void *p);
extern void free_afdxES2_mib_runtime_description(void *p);

extern void set_a664_middleware_runtime_header(void *p);
extern void set_a664_middleware_runtime_name(void *p);
extern void set_a664_middleware_runtime_description(void *p, int flag);
extern void free_a664_middleware_runtime_header(void *p);
extern void free_a664_middleware_runtime_name(void *p);
extern void free_a664_middleware_runtime_description(void *p);

extern void set_a664_card_runtime_header(void *p);
extern void set_a664_card_runtime_name(void *p);
extern void set_a664_card_runtime_description(void *p, int flag);
extern void free_a664_card_runtime_header(void *p);
extern void free_a664_card_runtime_name(void *p);
extern void free_a664_card_runtime_description(void *p);

#endif
