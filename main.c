#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include "os_malloc.h"
void main(void)
{   
    void *start = malloc(10*1024);
    void *end = start + 10*1024;
    void *ptr3,*ptr1,*ptr2,*ptr4 ;
    printf("start is:%x\n",start);
    printf("szie is:%d\n",(int)(end - start));
    osHeapInit(start, end);
    
    while(1)
    {   
        usleep(1000000);
        ptr1 = osMalloc(16);
        printf("ptr1 is:%x\n",ptr1);
        ptr2 = osMalloc(16);
        printf("ptr2 is:%x\n",ptr2);
        ptr3 = osMalloc(16);
        printf("ptr3 is:%x\n",ptr3);
        osHeapInfo();
        osFree(ptr1);
        osHeapInfo();
        ptr4 = osMalloc(16);
        printf("ptr4 is:%x\n",ptr4);
        osHeapInfo();
        return ;
        //printf("test\r\n");

    }
}