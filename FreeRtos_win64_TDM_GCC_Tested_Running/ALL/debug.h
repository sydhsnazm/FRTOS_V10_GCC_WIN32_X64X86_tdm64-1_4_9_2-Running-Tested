#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "FreeRTOS.h"
//edited main.c
//__asm{NOP}


//comment out
//vFullDemoIdleFunction
//line number

#define debug(STRING) printf("%s",STRING);


extern void err(int num);

//at line #66
//port macro edited -1 to 1





#endif // _DEBUG_H_
