/*
 * sigrow.h
 *
 * Created: 2020-10-19 7:33:27 PM
 *  Author: charl
 */ 


#ifndef SIGROW_H_
#define SIGROW_H_

#include "tinylibdef.h"

typedef struct __attribute__((packed)) {
	uint8_t DeviceId0;
	uint8_t DeviceId1;
	uint8_t DeviceId2;
} DeviceId_t;

typedef struct __attribute__((packed)) {
	uint8_t SerialNumber0;
	uint8_t SerialNumber1;
	uint8_t SerialNumber2;
	uint8_t SerialNumber3;
	uint8_t SerialNumber4;
	uint8_t SerialNumber5;
	uint8_t SerialNumber6;
	uint8_t SerialNumber7;
	uint8_t SerialNumber8;
	uint8_t SerialNumber9;
} SerialNumber_t;

#define SIGROW_LOAD_DEVICEID(x)				\
	do {									\
		x.DeviceId0 = SIGROW.DEVICEID0;		\
		x.DeviceId1 = SIGROW.DEVICEID1;		\
		x.DeviceId2 = SIGROW.DEVICEID2;		\
	} while(0)

#define SIGROW_LOAD_SERIALNUMBER(x)			\
	do {									\
		x.SerialNumber0 = SIGROW.SERNUM0;	\
		x.SerialNumber1 = SIGROW.SERNUM1;	\
		x.SerialNumber2 = SIGROW.SERNUM2;	\
		x.SerialNumber3 = SIGROW.SERNUM3;	\
		x.SerialNumber4 = SIGROW.SERNUM4;	\
		x.SerialNumber5 = SIGROW.SERNUM5;	\
		x.SerialNumber6 = SIGROW.SERNUM6;	\
		x.SerialNumber7 = SIGROW.SERNUM7;	\
		x.SerialNumber8 = SIGROW.SERNUM8;	\
		x.SerialNumber9 = SIGROW.SERNUM9;	\
	} while(0)

#endif /* SIGROW_H_ */