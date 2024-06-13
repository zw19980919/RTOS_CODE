#ifndef __OS_MALLOC__H_
#define __OS_MALLOC__H_
#include "os_type.h"
#include "os_kservice.h"
#ifdef __cplusplus
extern "C" {
#endif

void  osHeapInit(uint32_t *start, uint32_t *end);
void  *osMalloc(uint32_t size);
void  osFree(void *ptr);
void osHeapInfo(void);
#ifdef __cplusplus
}
#endif

#endif 
