/*
 * utilities.c
 *
 * Created: 2019-05-20 2:05:59 PM
 *  Author: Wizz
 */ 

#include "utilities.h"

#include <avr/io.h>

//#include "debug_interface.h"

#include "ccp.h"

uint8_t utils_rcause;

void utils_SaveResetCause(void) {
	utils_rcause = RSTCTRL.RSTFR;
}

void utils_DebugPrintResetCause(void) {
#if DEBUG_VERBOSE_LEVEL > 0
	char *str_cause = 0;
	
	char str_cause_SOFT[] = "SoftRst";
	char str_cause_WDT[] = "WDT";
	char str_cause_POR[] = "POR";
	char str_cause_EXT[] = "ExtRst";
	char str_cause_BOD[] = "BOD";

	if(utils_rcause & RSTCTRL_SWRF_bm) {
		str_cause = str_cause_SOFT;
	} else if(utils_rcause & RSTCTRL_WDRF_bm) {
		str_cause = str_cause_WDT;
	} else if(utils_rcause & RSTCTRL_PORF_bm) {
		str_cause = str_cause_POR;
	} else if(utils_rcause & RSTCTRL_EXTRF_bm) {
		str_cause = str_cause_EXT;
	} else if(utils_rcause & RSTCTRL_BORF_bm) {
		str_cause = str_cause_BOD;
	}

	//DEBUG_printf( ("Rst: %s\n", str_cause) );
#endif
}

inline BaseType_t utils_IsSoftwareReset(void) {
	return utils_rcause & RSTCTRL_SWRF_bm;
}

inline BaseType_t utils_IsExternalResetType(void) {
	return utils_rcause & (RSTCTRL_BORF_bm || RSTCTRL_EXTRF_bm || RSTCTRL_PORF_bm);
}

inline BaseType_t utils_IsWatchDogTimerReset(void) {
	return utils_rcause & RSTCTRL_WDRF_bm;
}

void utils_SystemReset(void) {
	CCP_UNLOCK_IO_REGISTERS();
	RSTCTRL.SWRR = RSTCTRL_SWRE_bm;
}

inline void utils_SetupUPDI(void) {
	#ifdef TINYx14
		PORTA_PIN0CTRL = PORT_PULLUPEN_bm | PORT_ISC_INPUT_DISABLE_gc;
	#else
		#error CPU not supported!
	#endif
}

uint8_t hexCharToUint(const char c) {
	uint8_t hexValue = 0;
	if((c >= '0') && (c <= '9')) {
		hexValue = (c - '0');
	} else if((c >= 'A') && (c <= 'F')) {
		hexValue = (c - ('A' - 0x0A));
	} else if((c >= 'a') && (c <= 'f')) {
		hexValue = (c - ('a' - 0x0A));
	} else {
		//configASSERT(0);
	}

	return hexValue;
}

uint8_t hexConverter(const char *data) {
	return (hexCharToUint(data[0]) << 4) | hexCharToUint(data[1]);
}

uint8_t hexParseUint8(const char **c) {
	uint8_t val = hexConverter(*c);
	(*c) += 2 * sizeof(char);
	return val;
}

uint16_t hexParseUint16(const char **c) {
	uint16_t val = (hexConverter(*c) << 8);
	(*c) += 2 * sizeof(char);
	val |= hexConverter(*c);
	(*c) += 2 * sizeof(char);
	return val;
}

uint32_t hexParseUint32(const char **c) {
	uint32_t val = ((uint32_t)hexParseUint16(c) << 16);
	val |= hexParseUint16(c);
	return val;
}