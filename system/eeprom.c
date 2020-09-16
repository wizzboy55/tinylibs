/*
 * eeprom.c
 *
 * Created: 2020-09-16 9:14:43 AM
 *  Author: charl
 */ 

#include "eeprom.h"

#include <avr/io.h>
#include "ccp.h"

void vEEPROMInit(void) {
	
	// Wait for Ready bit
	while(NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm) {};
}

void vEEPROMWriteBlock(uint16_t usEepromAddress, uint8_t *data, size_t size) {
	uint8_t *write = (uint8_t *)(EEPROM_START + usEepromAddress);

	/* Wait for completion of previous write */
	while (NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm)
	;

	/* Clear page buffer */
	vTinyCCPUnlockSPMRegisters();
	NVMCTRL.CTRLA = NVMCTRL_CMD_PAGEBUFCLR_gc;

	do {
		/* Write byte to page buffer */
		*write++ = *data++;
		size--;
		// If we have filled an entire page or written last byte to a partially filled page
		if ((((uintptr_t)write % EEPROM_PAGE_SIZE) == 0) || (size == 0)) {
			/* Erase written part of page and program with desired value(s) */
			vTinyCCPUnlockSPMRegisters();
			NVMCTRL.CTRLA = NVMCTRL_CMD_PAGEERASEWRITE_gc;
		}
	} while (size != 0);
}

inline void vEEPROMReadBlock(uint16_t usEepromAddress, uint8_t *data, size_t size) {
	memcpy(data, (uint8_t *)(EEPROM_START + usEepromAddress), size);
}