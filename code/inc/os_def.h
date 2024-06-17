#ifndef __OS_DEF_H__
#define __OS_DEF_H__
#include "os_type.h"
#ifdef __cplusplus
extern "C" {
#endif
/*********************************general*****************************************/
#define OS_NULL ((void *)0)

struct listnode
{
    struct listnode *prev;
    struct listnode *next;
};
typedef struct listnode osList_t;

#define containerof(ptr, type, member) (type *)((uint8_t *)ptr - (ubase_t)(&((type *)0)->member))
#define ListEntry(listnode, type, member)     containerof(listnode, type, member)    

struct osObject
{
    uint32_t type;
    uint32_t flag;
    uint32_t attr;
};
typedef struct osObject* osObject_t;

/********************************task struct define**********************************/
struct task_control_block
{
    void *sp;                        /***************栈指针，任务切换时保存任务当前的栈********************/
    struct osObject parent;          /***************任务内嵌对象****************************************/
    uint32_t taskpriority;           /***************任务优先级******************************************/
    const char *task_name;           /***************任务名**********************************************/
    void *stack_address;             /***************任务栈基地址*****************************************/
    uint32_t stack_size;             /***************任务栈大小******************************************/
    void *entry;                     /***************任务入口函数地址*************************************/
    void *parameter;                 /***************入伍入口函数的参数***********************************/
    oslist_t tlist;                  /***************用于链接任务到就绪表/挂起队列的链表节点****************/
};
typedef struct task_control_block *osTcb_t;

typedef void(*osTaskFun_t)(void *parameter);

struct task_attr
{
    uint32_t priority;
    uint32_t stack_size;
    uint32_t time_slices;
    const char *name;
};
typedef struct task_attr osTaskAttr;

const uint8_t __lowest_bit_bitmap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

unsigned char _osFfs(unsigned int value)
{
    if (value == 0) return 0;

    if (value & 0xff)
        return __lowest_bit_bitmap[value & 0xff] + 1;

    if (value & 0xff00)
        return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;

    if (value & 0xff0000)
        return __lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;

    return __lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}






#ifdef __cplusplus
}
#endif

#endif
