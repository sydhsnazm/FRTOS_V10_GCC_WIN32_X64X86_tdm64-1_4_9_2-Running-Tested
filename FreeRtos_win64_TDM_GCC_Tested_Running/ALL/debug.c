#include <stdio.h>
#include "debug.h"

typedef unsigned int uint32_t;

void vAssertCalled( uint32_t ulLine, const char * const pcFileName )
{
    printf("\nLine#[%i], FileName[%s]",ulLine,pcFileName);
    printf("\nLine#[%i], FileName[%s]", __LINE__,__FILE__ );
}

void err(int num){
    if(num == -1)
        printf("\nerr:[COULD_NOT_ALLOCATE_REQUIRED_MEMORY]\n");
    else if(num == -4)
        printf("\nerr:[QUEUE_BLOCKED]\n");
    else if(num == -5)
            printf("\nerr:[QUEUE_YIELD]\n");
    else
            printf("\nerr:[NO_ERROR]\n");

    num = 0;
}
