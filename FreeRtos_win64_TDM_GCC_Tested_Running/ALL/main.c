/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 *
 *  VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  This file is part of the FreeRTOS distribution.
 *
 *  This contains the Windows port implementation of the examples listed in the
 *  FreeRTOS book Mastering_the_FreeRTOS_Real_Time_Kernel.
 *
 */
#include <stdio.h>
/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "supporting_functions.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )

/* The task functions. */
void vTask1( void * pvParameters );
void vTask2( void * pvParameters );
void vTask3( void * pvParameters );
/*-----------------------------------------------------------*/

int main( void )
{
    //vPrintString("vPrintString\n");
    configASSERT( vTask1 );
    printf("FreeRTOS Kernel V10.5.1");
    /* Create one of the two tasks. */
    printf("\nxTaskCreate() start()\n");
    xTaskCreate( vTask1,   /* Pointer to the function that implements the task. */
                 "Task 1", /* Text name for the task.  This is to facilitate debugging only. */
                 1000,     /* Stack depth - most small microcontrollers will use much less stack than this. */
                 NULL,     /* We are not using the task parameter. */
                 1,        /* This task will run at priority 1. */
                 NULL );   /* We are not using the task handle. */
    printf("\nxTaskCreate() end()\n");
    /* Create the other task in exactly the same way. */

    printf("\n\nxTaskCreate() start()\n");
    xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );
    printf("\nxTaskCreate() end()\n");


    printf("\n\nxTaskCreate() start()");
    xTaskCreate( vTask3, "Task 3", 1000, NULL, 1, NULL );
    printf("xTaskCreate() end()\n");

    /* Start the scheduler to start the tasks executing. */
    printf("\nvTaskStartScheduler() start()");
    vTaskStartScheduler();
    printf("\nvTaskStartScheduler() error()\n");

    /* The following line should never be reached because vTaskStartScheduler()
    *  will only return if there was not enough FreeRTOS heap memory available to
    *  create the Idle and (if configured) Timer tasks.  Heap management, and
    *  techniques for trapping heap exhaustion, are described in the book text. */
    for( ; ; )
    {
        //vPrintString("\n348s:sse int76.");
    }

    return 1;
}
/*-----------------------------------------------------------*/

void vTask1( void * pvParameters )
{
    const char * pcTaskName = "Task 1 is standing.\r\n";
    volatile uint32_t ul;

    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ; ; )
    {
        /* Print out the name of this task. */
        vPrintString( pcTaskName );

        /* Delay for a period. */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            //sleep(50);
            /* This loop is just a very crude delay implementation.  There is
             * nothing to do in here.  Later exercises will replace this crude
             * loop with a proper delay/sleep function. */
        }
    }
}
/*-----------------------------------------------------------*/

void vTask2( void * pvParameters )
{
    const char * pcTaskName = "Task 2 is watching.\r\n";
    volatile uint32_t ul;

    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ; ; )
    {
        /* Print out the name of this task. */
        vPrintString( pcTaskName );

        /* Delay for a period. */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            //sleep(50);
            /* This loop is just a very crude delay implementation.  There is
             * nothing to do in here.  Later exercises will replace this crude
             * loop with a proper delay/sleep function. */
        }
    }
}

void vTask3( void *pvParameters ){
    char *pcTaskName = "Task 3 is enjoying.\r\n";
    volatile uint32_t ul;

    for(;;){
        vPrintString( pcTaskName );
         /* Delay for a period. */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            //sleep(50);
            /* This loop is just a very crude delay implementation.  There is
             * nothing to do in here.  Later exercises will replace this crude
             * loop with a proper delay/sleep function. */
        }
    }
}
