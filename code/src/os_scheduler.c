#include "os_def.h"
#include "os_schedule.h"
#include "os_type.h"


static volatile osList_t g_TaskReadyPriorityTable[OS_MAX_TASK_PRIORITY]; /***************全局就绪任务表***********/
static volatile uint32_t g_TaskReadyPriorityGroup;  /***************全局就绪优先级bitmap*****/
static volatile uint8_t g_CurrentTaskPriority;      /***************当前运行任务优先级*******/
static volatile uint8_t g_ReadyTaskHighestPriority; /***************系统就绪表最高优先级*****/
static volatile osTcb_t g_CurrentRunTask;           /***************指向当前运行任务控制块指针*/
static volatile osTcb_t g_HighestPriority;          /***************指向就绪表最高优先级指针***/
volatile uint8_t g_osInteruptNest = 0;
volatile uint8_t g_osSchedulerlockNest = 0;

static uint8_t get_ready_highest_priority(void)
{
    return _osFfs(g_TaskReadyPriorityGroup);
}

void osContextSwitch(void)
{
    return;
}

/**
 *该函数用于引发一次任务切换
 *切换规则是精确的行为:表现为
 *1:在中断中该函数不起作用，表现为直接返回。
 *2:该函数判断任务就绪表最高优先级是否是当前任务，如果不相同就引发任务切换，否则不切换。
 *3:在调度器被关闭的情况下该函数不起作用，直接返回。
 */
void osSchedule(void)
{
    osTcb_t current_task, next_task;
    uint8_t higest_ready_priority;
    if (g_osInteruptNest == 0)
    {
        if (g_osSchedulerlockNest == 0)
        {
            higest_ready_priority = get_ready_highest_priority();
            g_ReadyTaskHighestPriority = higest_ready_priority;
            next_task =
                ListEntry(g_TaskReadyPriorityTable[higest_ready_priority].next, struct task_control_block, tlist);
            if (g_CurrentRunTask != next_task)
            {
                osContextSwitch();
            }
            return;
        }
    }
    return;
}
