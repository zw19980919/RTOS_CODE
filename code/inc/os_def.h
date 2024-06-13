#ifndef __OS_DEF_H__
#define __OS_DEF_H__
#include "os_type.h"
#ifdef __cplusplus
extern "C" {
#endif

#define OS_NULL ((void *)0)

struct listnode
{
    struct listnode *prev;
    struct listnode *next;
};
typedef struct listnode listnode_t;

#define containerof(ptr, type, member) (type *)((uint8_t *)ptr - (ubase_t)(&((type *)0)->member))
#define ListEntry(listnode, member)     containerof(listnode, struct listnode, member)    












#ifdef __cplusplus
}
#endif

#endif
