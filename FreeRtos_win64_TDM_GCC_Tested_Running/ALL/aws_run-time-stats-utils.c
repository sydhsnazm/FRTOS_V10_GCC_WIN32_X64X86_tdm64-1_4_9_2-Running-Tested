/*
 * Amazon FreeRTOS V1.2.7
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


/*
 * Utility functions required to gather run time statistics.  See:
 * http://www.freertos.org/rtos-run-time-stats.html
 *
 * Note that this is a simulated port, where simulated time is a lot slower than
 * real time, therefore the run time counter values have no real meaningful
 * units.
 *
 * Also note that it is assumed this demo is going to be used for short periods
 * of time only, and therefore timer overflows are not handled.
 */

/* FreeRTOS includes. */
#include <FreeRTOS.h>

/* Variables used in the creation of the run time stats time base.  Run time
 * stats record how much time each task spends in the Running state. */
static long long llInitialRunTimeCounterValue = 0LL, llTicksPerHundedthMillisecond = 0LL;

/*-----------------------------------------------------------*/

void vConfigureTimerForRunTimeStats( void )
{
    LARGE_INTEGER liPerformanceCounterFrequency, liInitialRunTimeValue;

    /* Initialise the variables used to create the run time stats time base.
     * Run time stats record how much time each task spends in the Running
     * state. */

    if( QueryPerformanceFrequency( &liPerformanceCounterFrequency ) == 0 )
    {
        llTicksPerHundedthMillisecond = 1;
    }
    else
    {
        /* How many times does the performance counter increment in 1/100th
         * millisecond. */
        llTicksPerHundedthMillisecond = liPerformanceCounterFrequency.QuadPart / 100000LL;

        /* What is the performance counter value now, this will be subtracted
         * from readings taken at run time. */
        QueryPerformanceCounter( &liInitialRunTimeValue );
        llInitialRunTimeCounterValue = liInitialRunTimeValue.QuadPart;
    }
}
/*-----------------------------------------------------------*/

unsigned long ulGetRunTimeCounterValue( void )
{
    LARGE_INTEGER liCurrentCount;
    unsigned long ulReturn;

    /* What is the performance counter value now? */
    QueryPerformanceCounter( &liCurrentCount );

    /* Subtract the performance counter value reading taken when the
     * application started to get a count from that reference point, then
     * scale to (simulated) 1/100ths of a millisecond. */
    if( llTicksPerHundedthMillisecond == 0 )
    {
        /* The trace macros can call this function before the kernel has been
         * started, in which case llTicksPerHundedthMillisecond will not have been
         * initialised. */
        ulReturn = 0;
    }
    else
    {
        ulReturn = ( unsigned long )
                   ( ( liCurrentCount.QuadPart - llInitialRunTimeCounterValue ) /
                     llTicksPerHundedthMillisecond );
    }

    return ulReturn;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If application tasks make use of the
	vTaskDelete() API function to delete themselves then it is also important
	that vApplicationIdleHook() is permitted to return to its calling function,
	because it is the responsibility of the idle task to clean up memory
	allocated by the kernel to any task that has since deleted itself. */

	/* Uncomment the following code to allow the trace to be stopped with any
	key press.  The code is commented out by default as the kbhit() function
	interferes with the run time behaviour. */
	/*
		if( _kbhit() != pdFALSE )
		{
			if( xTraceRunning == pdTRUE )
			{
				vTraceStop();
				prvSaveTraceFile();
				xTraceRunning = pdFALSE;
			}
		}
	*/

	#if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY != 1 )
	{
		/* Call the idle task processing used by the full demo.  The simple
		blinky demo does not use the idle task hook. */
		//vFullDemoIdleFunction();
	}
	#endif
}
/*-----------------------------------------------------------*/
