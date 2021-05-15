/*
 * twi.c
 *
 * Created: 2020-10-09 2:48:44 PM
 *  Author: charl
 */ 

#include "twi.h"

uint8_t dump;

void vTinyTWISetupSlave(TWI_t* pxTwi, uint8_t addr, TWI_Slave_State_t *pxTwiState) {
	pxTwiState->ucMasterReadIndex = 0;
	pxTwiState->pucMasterReadBuffer = NULL;
	pxTwiState->ucMasterWriteIndex = 0;

	pxTwi->SADDR = addr << 1;
	pxTwi->SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm | TWI_ENABLE_bm;
}

void vTinyTWISlaveInterruptHandler(TWI_t* pxTwi, TWI_Slave_State_t* pxTwiState) {
	
	if(pxTwi->SSTATUS & TWI_COLL_bm) {
		// Collision
	}
	
	if(pxTwi->SSTATUS & TWI_BUSERR_bm) {
		// Bus Error
	}
	
	if(pxTwi->SSTATUS & TWI_APIF_bm) {
		// Address or Stop Interrupt
		if(pxTwi->SSTATUS & TWI_AP_bm) {
			// Address Matched
			if(pxTwi->SSTATUS & TWI_DIR_bm) {
				// Master Read
				pxTwiState->pfMasterReadCallback();
				if(pxTwiState->ucMasterReadIndex < pxTwiState->ucMasterReadSize && pxTwiState->pucMasterReadBuffer != NULL) {
					pxTwi->SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;
				} else {
					pxTwi->SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc;
				}
			} else {
				// Master Write
				pxTwi->SCTRLB = TWI_ACKACT_ACK_gc;
				dump = pxTwi->SDATA;
			}
		} else {
			// Stop Condition
			if(pxTwiState->ucMasterWriteIndex) {
				pxTwiState->pfMasterWriteCallback();
				pxTwiState->ucMasterWriteIndex = 0;
			}
			pxTwi->SCTRLB = TWI_SCMD_COMPTRANS_gc;
		}
	} else if(pxTwi->SSTATUS & TWI_DIF_bm) {
		// Data Received or Sent
		if(pxTwi->SSTATUS & TWI_DIR_bm) {
			// Master Read
			if(pxTwiState->ucMasterReadIndex < pxTwiState->ucMasterReadSize && pxTwiState->pucMasterReadBuffer != NULL) {
				uint8_t data = (uint8_t)pxTwiState->pucMasterReadBuffer[pxTwiState->ucMasterReadIndex++];
				pxTwi->SDATA = data;
			} else {
				pxTwiState->pucMasterReadBuffer = NULL;
				pxTwiState->ucMasterReadSize = 0;
				pxTwi->SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc;
			}
		} else {
			// Master Write
			if(pxTwiState->ucMasterWriteIndex < TWI_BUFFER_SIZE) {
				pxTwiState->pucMasterWriteBuffer[pxTwiState->ucMasterWriteIndex++] = pxTwi->SDATA;
				pxTwi->SCTRLB = TWI_ACKACT_ACK_gc;
				pxTwiState->pfMasterWriteCallback();
			}
		}
	} else {
		// Unknown
	}
		
	pxTwi->SSTATUS |= TWI_APIF_bm | TWI_DIF_bm;
}