#ifndef __OS_MALLOC__H_
#define __OS_MALLOC__H_
#include "os_type.h"
#include "os_kservice.h"
#include "os_def.h"

#ifdef __cplusplus
extern "C" {
#endif

void *osTaskNew(osTaskFun_t entry, void *argument, const osTaskAttr_t *attr);
void osTaskStart(void *osTcb);
void osTaskStop(void *osTcb);
void osTaskDelte(void *osTcb);
void osTaskInit(void *osTcb);

#ifdef __cplusplus
}
#endif

#endif 
