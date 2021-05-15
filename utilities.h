/*
 * utilities.h
 *
 * Created: 2019-05-20 2:07:36 PM
 *  Author: Wizz
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "tinylibdef.h"

void utils_SaveResetCause(void);
void utils_DebugPrintResetCause(void);

BaseType_t utils_IsSoftwareReset(void);
BaseType_t utils_IsExternalResetType(void);
BaseType_t utils_IsWatchDogTimerReset(void);

uint8_t utils_getResetCause(void);

void utils_SystemReset(void);
void utils_WatchDogReset(void);

void utils_SetupUPDI(void);

uint8_t hexCharToUint(const char c);
uint8_t hexConverter(const char *data);
uint8_t hexParseUint8(const char **c);
uint16_t hexParseUint16(const char **c);
uint32_t hexParseUint32(const char **c);

#define UNUSED(expr) do { (void)(expr); } while(0)

#define NOP() do { __asm__ __volatile__ ("nop"); } while (0)

#endif /* UTILITIES_H_ */