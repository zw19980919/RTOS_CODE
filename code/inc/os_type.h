/*****************************定义与操作系统无关的数据类型*************************/
/*****************************这些数据类型定义和操作系统无关***********************/
/*****************************这些代码均运行在32位机器架构下***********************/
/*****************************filename :: os_type.h*****************************/
/*****************************author   :: zhongwen******************************/

#ifndef __OS_TYPE_H__
#define __OS_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long      ubase_t;
typedef signed char        int_least8_t;
typedef short              int_least16_t;
typedef int                int_least32_t;
typedef long long          int_least64_t;
typedef unsigned char      uint_least8_t;
typedef unsigned short     uint_least16_t;
typedef unsigned int       uint_least32_t;
typedef unsigned long long uint_least64_t;

typedef signed char        int_fast8_t;
typedef int                int_fast16_t;
typedef int                int_fast32_t;
typedef long long          int_fast64_t;
typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned int       uint_fast32_t;
typedef unsigned long long uint_fast64_t;

typedef long long          intmax_t;
typedef unsigned long long uintmax_t;

#ifdef __cplusplus
}
#endif

#endif 

