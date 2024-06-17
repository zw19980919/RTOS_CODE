#include "os_task.h"


/**
 ***********************************************************************************************************************
 * 
 *
 * @attention       该函数创建一个任务，并把它加入到就绪队列，如果该函数优先级足够高，那么会引发一次任务调度，从而运行新创建的任务。
 *
 * @param[in]       func            任务入口函数
 * @param[in]       argument        任务入口函数的参数的指针
 * @param[in]       attr            任务属性结构体; NULL: 默认任务属性
 *
 * @return          指向任务控制块的指针
 ***********************************************************************************************************************
 */
 osTaskAttr_t  default_TCB=
 {
      . priority = 16;
 . stack_si
 uint32_t time_sli
 const char *name;
 }
void *osTaskNew(osTaskFun_t entry, void *argument, const osTaskAttr_t *attr)
{
    osTaskAttr_t temp_attr = OS_NULL;
    if(entry == OS_NULL)
    {
        osPrintf("invalid entry\n");
        return (void*)0;
    }
    
    if(attr == OS_NULL)
    {

    }
    

}


