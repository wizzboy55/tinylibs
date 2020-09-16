/*
 * faults.c
 *
 * Created: 2020-07-09 10:23:12 AM
 *  Author: charl
 */ 

#include "faults.h"

#include "FreeRTOS.h"
#include "task.h"

#include "utilities.h"
//#include "debug_interface.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {

//	DEBUG_printf( ("StackOverflow! Task: %s\tHandle: %d\n", pcTaskGetName(xTaskGetCurrentTaskHandle()), (uint32_t)xTaskGetCurrentTaskHandle()) );

	#ifdef DEBUG
	for(;;){}
	#else
	utils_SystemReset();
	#endif
}

void vApplicationMallocFailedHook(void) {

//	DEBUG_printf( ("Malloc Fail!\n") );

	#ifdef DEBUG
	for(;;){}
	#else
	utils_SystemReset();
	#endif
}

void vAssertCalled(const char *pcFileName, unsigned long ulLine) {

//	DEBUG_printf( ("ASSERT! F: %s L: %lu\n", pcFileName, ulLine) );

	#ifdef DEBUG
	for(;;){}
	#else
	utils_SystemReset();
	#endif
}