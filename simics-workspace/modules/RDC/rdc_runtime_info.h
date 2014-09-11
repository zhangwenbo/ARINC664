#ifndef RDC_RUNTIME_INFO_H
#define RDC_RUNTIME_INFO_H

extern void set_runtime_header(void *p);
extern void set_runtime_name(void *p);
extern void set_runtime_description(void *p, int flag);
extern void free_runtime_header(void *p);
extern void free_runtime_name(void *p);
extern void free_runtime_description(void *p);

#endif
