#ifndef __OS_MALLOC__H_
#define __OS_MALLOC__H_
#include "os_type.h"
#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

void  osHeapInit(uint32_t *start, uint32_t *end);
void  *osMalloc(uint32_t size);
void  osFree(void *ptr);

#ifdef __cplusplus
}
#endif

#endif 
