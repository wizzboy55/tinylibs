/*
 * twi.h
 *
 * Created: 2020-10-09 2:48:38 PM
 *  Author: charl
 */ 


#ifndef TWI_H_
#define TWI_H_

#include "tinylibdef.h"

#include <avr/io.h>

enum TwiCommand_e {TWI_NoAction = 0x00, TWI_CompleteTransaction = 0x02, TWI_Response = 0x03};

#define TWI_SET_ADDRESS(twi, x) twi.SADDR = x << 1;

#ifndef TWI_BUFFER_SIZE
	#define TWI_BUFFER_SIZE 16
#endif

typedef struct {
	void (*pfMasterReadCallback)(void);
	void (*pfMasterWriteCallback)(void);
	uint8_t *pucMasterReadBuffer;
	uint8_t ucMasterReadIndex;
	uint8_t ucMasterReadSize;
	uint8_t pucMasterWriteBuffer[TWI_BUFFER_SIZE];
	uint8_t ucMasterWriteIndex;
} TWI_Slave_State_t;

void vTinyTWISetupSlave(TWI_t* pxTwi, uint8_t addr, TWI_Slave_State_t *pxTwiState);
void vTinyTWISlaveInterruptHandler(TWI_t* pxTwi, TWI_Slave_State_t* pxTwiState);

#endif /* TWI_H_ */