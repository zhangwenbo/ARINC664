#ifndef RDC_RUNTIME_INFO_H
#define RDC_RUNTIME_INFO_H

extern void set_afdxES_module_runtime_header(void *p);
extern void set_afdxES_module_runtime_name(void *p);
extern void set_afdxES_module_runtime_description(void *p, int flag);
extern void free_afdxES_module_runtime_header(void *p);
extern void free_afdxES_module_runtime_name(void *p);
extern void free_afdxES_module_runtime_description(void *p);

extern void set_rdc_module_runtime_header(void *p);
extern void set_rdc_module_runtime_name(void *p);
extern void set_rdc_module_runtime_description(void *p, int flag);
extern void free_rdc_module_runtime_header(void *p);
extern void free_rdc_module_runtime_name(void *p);
extern void free_rdc_module_runtime_description(void *p);

#endif