#include <stdio.h>
#include  <unistd.h>
void main(void)
{
    while(1)
    {   
        usleep(1000000);
        printf("test\r\n");
    }
}