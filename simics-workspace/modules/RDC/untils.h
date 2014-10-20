#ifndef UNTILS_H
#define UNTILS_H

extern int Strlen(char *str);
extern int netStrlen(char *str);
extern void set_runtime_header(void *p);
extern void split(char *str, char *delim, char **dest, int *pCount);

#endif
