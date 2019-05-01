#include "MFRC522.h"

Uid uid;								// Used by PICC_ReadCardSerial().

void PCD_WriteRegister(uint8_t reg, uint8_t value)
{
	uint8_t rxBuffer[2] = {reg, value};
	MFRC522_CS_LOW
	HAL_SPI_Transmit(MFRC522_SPI_HANDLE, rxBuffer, 2, MFRC522_SPI_TIMEOUT);
	MFRC522_CS_HIGH
}
void PCD_WriteRegister_ext(uint8_t reg, uint8_t count, uint8_t *values)
{
	MFRC522_CS_LOW
	HAL_SPI_Transmit(MFRC522_SPI_HANDLE, &reg, 1, MFRC522_SPI_TIMEOUT);
	HAL_SPI_Transmit(MFRC522_SPI_HANDLE, values, count, MFRC522_SPI_TIMEOUT);
	MFRC522_CS_HIGH
}
uint8_t PCD_ReadRegister(uint8_t reg)
{
	uint8_t txBuffer[2] = {0x80 | reg, 0};
	uint8_t rxBuffer[2] = {0};

	MFRC522_CS_LOW
	HAL_SPI_TransmitReceive(MFRC522_SPI_HANDLE, txBuffer, rxBuffer, 2, MFRC522_SPI_TIMEOUT);
	MFRC522_CS_HIGH
	return rxBuffer[1];
}
void PCD_ReadRegister_ext(uint8_t reg, uint8_t count, uint8_t *values, uint8_t rxAlign)
{
	if (count == 0)
		return;

	uint8_t address = 0x80 | reg;
	uint8_t index = 0;
	uint8_t dummy = 0;

	MFRC522_CS_LOW
	count--;
	HAL_SPI_Transmit(MFRC522_SPI_HANDLE, &address, 1, MFRC522_SPI_TIMEOUT);
	if(rxAlign)
	{
		uint8_t mask = (0xFF << rxAlign) & 0xFF;
		uint8_t value;
		HAL_SPI_TransmitReceive(MFRC522_SPI_HANDLE, &address, &value, 1, MFRC522_SPI_TIMEOUT);
		values[0] = (values[0] & ~mask) | (value & mask);
		index++;
	}
	while(index < count)
	{
		HAL_SPI_TransmitReceive(MFRC522_SPI_HANDLE, &address, &values[index], 1, MFRC522_SPI_TIMEOUT);
		index++;
	}
	HAL_SPI_TransmitReceive(MFRC522_SPI_HANDLE, &dummy, &values[index], 1, MFRC522_SPI_TIMEOUT);
	MFRC522_CS_HIGH

}
void PCD_SetRegisterBitMask(uint8_t reg, uint8_t mask)
{
	uint8_t tmp;
	tmp = PCD_ReadRegister(reg);
	PCD_WriteRegister(reg, tmp | mask);
}
void PCD_ClearRegisterBitMask(uint8_t reg, uint8_t mask)
{
	uint8_t tmp;
	tmp = PCD_ReadRegister(reg);
	PCD_WriteRegister(reg, tmp & (~mask));
}
uint8_t PCD_CalculateCRC(uint8_t *data, uint8_t length, uint8_t *result)
{
	PCD_WriteRegister(COMMAND_REG, PCD_IDLE_CMD);		// Stop any active command.
	PCD_WriteRegister(DIV_IRQ_REG, 0x04);				// Clear the CRCIRq interrupt request bit
	PCD_WriteRegister(FIFO_LEVEL_REG, 0x80);			// FlushBuffer = 1, FIFO initialization
	PCD_WriteRegister_ext(FIFO_DATA_REG, length, data);		// Write data to the FIFO
	PCD_WriteRegister(COMMAND_REG, PCD_CALC_CRC_CMD);	// Start the calculation


	// Wait for the CRC calculation to complete. Each iteration of the while-loop takes 17.73us.
	for (uint16_t i = 5000; i > 0; i--) {
		// DivIrqReg[7..0] bits are: Set2 reserved reserved MfinActIRq reserved CRCIRq reserved reserved
		uint8_t n = PCD_ReadRegister(DIV_IRQ_REG);
		if (n & 0x04) {									// CRCIRq bit set - calculation done
			PCD_WriteRegister(COMMAND_REG, PCD_IDLE_CMD);	// Stop calculating CRC for new content in the FIFO.
			// Transfer the result from the registers to the result buffer
			result[0] = PCD_ReadRegister(CRC_RESULT_REG_L);
			result[1] = PCD_ReadRegister(CRC_RESULT_REG_H);
			return STATUS_OK;
		}
	}
	// 89ms passed and nothing happend. Communication with the MFRC522 might be down.
	return STATUS_TIMEOUT;
}









void PCD_Init()
{
	uint8_t hardReset = 0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	MFRC522_CS_HIGH

	HAL_GPIO_DeInit(MFRC522_RST_GPIO_PORT, MFRC522_RST_PIN);
	GPIO_InitStruct.Pin = MFRC522_RST_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(MFRC522_RST_GPIO_PORT, &GPIO_InitStruct);

	delay_CYC(US_TO_CYC(50));

	if(HAL_GPIO_ReadPin(MFRC522_RST_GPIO_PORT, MFRC522_RST_PIN) == 0)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(MFRC522_RST_GPIO_PORT, &GPIO_InitStruct);

		HAL_GPIO_WritePin(MFRC522_RST_GPIO_PORT, MFRC522_RST_PIN, GPIO_PIN_RESET);
		delay_CYC(US_TO_CYC(2));
		HAL_GPIO_WritePin(MFRC522_RST_GPIO_PORT, MFRC522_RST_PIN, GPIO_PIN_SET);

		delay_CYC(US_TO_CYC(50));
		hardReset = 1;
	}
	if (!hardReset) { // Perform a soft reset if we haven't triggered a hard reset above.
		PCD_Reset();
	}

	// Reset baud rates
	PCD_WriteRegister(TX_MODE_REG, 0x00);
	PCD_WriteRegister(RX_MODE_REG, 0x00);
	// Reset ModWidthReg
	PCD_WriteRegister(MOD_WIDTH_REG, 0x26);

	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	PCD_WriteRegister(T_MODE_REG, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	PCD_WriteRegister(T_PRESCALER_REG, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25μs.
	PCD_WriteRegister(T_RELOAD_REG_H, 0x03);		// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
	PCD_WriteRegister(T_RELOAD_REG_L, 0xE8);

	PCD_WriteRegister(TX_ASK_REG, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
	PCD_WriteRegister(MODE_REG, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363 (ISO 14443-3 part 6.2.4)
	PCD_AntennaOn();						// Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset)
}

void PCD_Reset()
{
	PCD_WriteRegister(COMMAND_REG, PCD_SOFT_RESET_CMD);	// Issue the SoftReset command.
	// The datasheet does not mention how long the SoftRest command takes to complete.
	// But the MFRC522 might have been in soft power-down mode (triggered by bit 4 of CommandReg)
	// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74μs. Let us be generous: 50ms.
	uint8_t count = 0;
	do {
		// Wait for the PowerDown bit in CommandReg to be cleared (max 3x50ms)
		delay_CYC(US_TO_CYC(50));
	} while ((PCD_ReadRegister(COMMAND_REG) & (1 << 4)) && (++count) < 3);
	if(count==3)
		__asm__ __volatile__ ("bkpt #0");
}

void PCD_AntennaOn()
{
	uint8_t value = PCD_ReadRegister(TX_CONTROL_REG);
	if ((value & 0x03) != 0x03) {
		PCD_WriteRegister(TX_CONTROL_REG, value | 0x03);
	}
}

void PCD_AntennaOff()
{
	PCD_ClearRegisterBitMask(TX_CONTROL_REG, 0x03);
}

uint8_t PCD_GetAntennaGain()
{
	return PCD_ReadRegister(RF_CFG_REG) & (0x07<<4);
}

void PCD_SetAntennaGain(uint8_t mask) {
	if (PCD_GetAntennaGain() != mask) {						// only bother if there is a change
		PCD_ClearRegisterBitMask(RF_CFG_REG, (0x07<<4));		// clear needed to allow 000 pattern
		PCD_SetRegisterBitMask(RF_CFG_REG, mask & (0x07<<4));	// only set RxGain[2:0] bits
	}
} // End PCD_SetAntennaGain()

void PCD_SoftPowerDown()
{//Note : Only soft power down mode is available throught software
	uint8_t val = PCD_ReadRegister(COMMAND_REG); // Read state of the command register
	val |= (1<<4);// set PowerDown bit ( bit 4 ) to 1
	PCD_WriteRegister(COMMAND_REG, val);//write new value to the command register
}

void PCD_SoftPowerUp()
{
	uint8_t val = PCD_ReadRegister(COMMAND_REG); // Read state of the command register
	val &= ~(1<<4);// set PowerDown bit ( bit 4 ) to 0
	PCD_WriteRegister(COMMAND_REG, val);//write new value to the command register
	// wait until PowerDown bit is cleared (this indicates end of wake up procedure)
	uint32_t ref;
	mark_CYC_Timer(&ref);// create timer for timeout (just in case)

	while(CYC_TO_US(elapsed_CYC_Timer(ref))<=500000){ // set timeout to 500 ms
		val = PCD_ReadRegister(COMMAND_REG);// Read state of the command register
		if(!(val & (1<<4))){ // if powerdown bit is 0
			break;// wake up procedure is finished
		}
	}
}

uint8_t PCD_TransceiveData(uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen, uint8_t *validBits, uint8_t rxAlign, uint8_t checkCRC)
{
	uint8_t waitIRq = 0x30;		// RxIRq and IdleIRq
	return PCD_CommunicateWithPICC(PCD_TRANSCEIVE_CMD, waitIRq, sendData, sendLen, backData, backLen, validBits, rxAlign, checkCRC);
}

uint8_t PCD_CommunicateWithPICC(uint8_t command, uint8_t waitIRq, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen, uint8_t *validBits, uint8_t rxAlign, uint8_t checkCRC)
{
	// Prepare values for BitFramingReg
	uint8_t txLastBits = validBits ? *validBits : 0;
	uint8_t bitFraming = (rxAlign << 4) + txLastBits;		// RxAlign = BitFramingReg[6..4]. TxLastBits = BitFramingReg[2..0]
	uint32_t ref;


	PCD_WriteRegister(COMMAND_REG, PCD_IDLE_CMD);			// Stop any active command.
	PCD_WriteRegister(COM_IRQ_REG, 0x7F);					// Clear all seven interrupt request bits
	PCD_WriteRegister(FIFO_LEVEL_REG, 0x80);				// FlushBuffer = 1, FIFO initialization
	PCD_WriteRegister_ext(FIFO_DATA_REG, sendLen, sendData);	// Write sendData to the FIFO
	PCD_WriteRegister(BIT_FRAMING_REG, bitFraming);		// Bit adjustments
	PCD_WriteRegister(COMMAND_REG, command);				// Execute the command
	if (command == PCD_TRANSCEIVE_CMD) {
		PCD_SetRegisterBitMask(BIT_FRAMING_REG, 0x80);	// StartSend=1, transmission of data starts
	}

	// Wait for the command to complete.
	// In PCD_Init() we set the TAuto flag in TModeReg. This means the timer automatically starts when the PCD stops transmitting.
	uint8_t pcdComSuccess=0;
	mark_CYC_Timer(&ref);
	while(CYC_TO_US(elapsed_CYC_Timer(ref))<40000) { //40 ms timeout
		uint8_t n = PCD_ReadRegister(COM_IRQ_REG);	// ComIrqReg[7..0] bits are: Set1 TxIRq RxIRq IdleIRq HiAlertIRq LoAlertIRq ErrIRq TimerIRq
		if (n & waitIRq) {					// One of the interrupts that signal success has been set.
			pcdComSuccess=1;
			break;
		}
		if (n & 0x01) {						// Timer interrupt - nothing received in 25ms
			pcdComSuccess=1;
			return STATUS_TIMEOUT;
		}
	}
	// 40ms and nothing happend. Communication with the MFRC522 might be down.
	if (!pcdComSuccess) {
		//__asm__ __volatile__ ("bkpt #0");
		return STATUS_TIMEOUT;
	}

	// Stop now if any errors except collisions were detected.
	uint8_t errorRegValue = PCD_ReadRegister(ERROR_REG); // ErrorReg[7..0] bits are: WrErr TempErr reserved BufferOvfl CollErr CRCErr ParityErr ProtocolErr
	if (errorRegValue & 0x13) {	 // BufferOvfl ParityErr ProtocolErr
		return STATUS_ERROR;
	}

	uint8_t _validBits = 0;

	// If the caller wants data back, get it from the MFRC522.
	if (backData && backLen) {
		uint8_t n = PCD_ReadRegister(FIFO_LEVEL_REG);	// Number of bytes in the FIFO
		if (n > *backLen) {
			return STATUS_NO_ROOM;
		}
		*backLen = n;											// Number of bytes returned
		PCD_ReadRegister_ext(FIFO_DATA_REG, n, backData, rxAlign);	// Get received data from FIFO
		_validBits = PCD_ReadRegister(CONTROL_REG) & 0x07;		// RxLastBits[2:0] indicates the number of valid bits in the last received byte. If this value is 000b, the whole byte is valid.
		if (validBits) {
			*validBits = _validBits;
		}
	}

	// Tell about collisions
	if (errorRegValue & 0x08) {		// CollErr
		return STATUS_COLLISION;
	}

	// Perform CRC_A validation if requested.
	if (backData && backLen && checkCRC) {
		// In this case a MIFARE Classic NAK is not OK.
		if (*backLen == 1 && _validBits == 4) {
			return STATUS_MIFARE_NACK;
		}
		// We need at least the CRC_A value and all 8 bits of the last byte must be received.
		if (*backLen < 2 || _validBits != 0) {
			return STATUS_CRC_WRONG;
		}
		// Verify CRC_A - do our own calculation and store the control in controlBuffer.
		uint8_t controlBuffer[2];
		uint8_t status = PCD_CalculateCRC(&backData[0], *backLen - 2, &controlBuffer[0]);
		if (status != STATUS_OK) {
			return status;
		}
		if ((backData[*backLen - 2] != controlBuffer[0]) || (backData[*backLen - 1] != controlBuffer[1])) {
			return STATUS_CRC_WRONG;
		}
	}

	return STATUS_OK;
}

uint8_t PICC_RequestA(uint8_t *bufferATQA, uint8_t *bufferSize)
{
	return PICC_REQA_or_WUPA(PICC_REQA_CMD, bufferATQA, bufferSize);
}

uint8_t PICC_WakeupA(uint8_t *bufferATQA, uint8_t *bufferSize)
{
	return PICC_REQA_or_WUPA(PICC_WUPA_CMD, bufferATQA, bufferSize);
}

uint8_t PICC_REQA_or_WUPA(uint8_t command, uint8_t *bufferATQA, uint8_t *bufferSize)
{
	uint8_t validBits;
	uint8_t status;

	if (bufferATQA == NULL || *bufferSize < 2) {	// The ATQA response is 2 bytes long.
		return STATUS_NO_ROOM;
	}
	PCD_ClearRegisterBitMask(COLL_REG, 0x80);		// ValuesAfterColl=1 => Bits received after collision are cleared.
	validBits = 7;									// For REQA and WUPA we need the short frame format - transmit only 7 bits of the last (and only) byte. TxLastBits = BitFramingReg[2..0]
	status = PCD_TransceiveData(&command, 1, bufferATQA, bufferSize, &validBits, 0, 0);
	if (status != STATUS_OK) {
		return status;
	}
	if (*bufferSize != 2 || validBits != 0) {		// ATQA must be exactly 16 bits.
		return STATUS_ERROR;
	}
	return STATUS_OK;
}

uint8_t PICC_Select(Uid *uid, uint8_t validBits)
{
	uint8_t uidComplete;
	uint8_t selectDone;
	uint8_t useCascadeTag;
	uint8_t cascadeLevel = 1;
	uint8_t result;
	uint8_t count;
	uint8_t checkBit;
	uint8_t index;
	uint8_t uidIndex;					// The first index in uid->uidByte[] that is used in the current Cascade Level.
	int8_t currentLevelKnownBits;		// The number of known UID bits in the current Cascade Level.
	uint8_t buffer[9];					// The SELECT/ANTICOLLISION commands uses a 7 byte standard frame + 2 bytes CRC_A
	uint8_t bufferUsed;				// The number of bytes used in the buffer, ie the number of bytes to transfer to the FIFO.
	uint8_t rxAlign;					// Used in BitFramingReg. Defines the bit position for the first bit received.
	uint8_t txLastBits;				// Used in BitFramingReg. The number of valid bits in the last transmitted byte.
	uint8_t *responseBuffer;
	uint8_t responseLength;

	// Description of buffer structure:
	//		Byte 0: SEL 				Indicates the Cascade Level: PICC_CMD_SEL_CL1, PICC_CMD_SEL_CL2 or PICC_CMD_SEL_CL3
	//		Byte 1: NVB					Number of Valid Bits (in complete command, not just the UID): High nibble: complete bytes, Low nibble: Extra bits.
	//		Byte 2: UID-data or CT		See explanation below. CT means Cascade Tag.
	//		Byte 3: UID-data
	//		Byte 4: UID-data
	//		Byte 5: UID-data
	//		Byte 6: BCC					Block Check Character - XOR of bytes 2-5
	//		Byte 7: CRC_A
	//		Byte 8: CRC_A
	// The BCC and CRC_A are only transmitted if we know all the UID bits of the current Cascade Level.
	//
	// Description of bytes 2-5: (Section 6.5.4 of the ISO/IEC 14443-3 draft: UID contents and cascade levels)
	//		UID size	Cascade level	Byte2	Byte3	Byte4	Byte5
	//		========	=============	=====	=====	=====	=====
	//		 4 bytes		1			uid0	uid1	uid2	uid3
	//		 7 bytes		1			CT		uid0	uid1	uid2
	//						2			uid3	uid4	uid5	uid6
	//		10 bytes		1			CT		uid0	uid1	uid2
	//						2			CT		uid3	uid4	uid5
	//						3			uid6	uid7	uid8	uid9

	// Sanity checks
	if (validBits > 80) {
		return STATUS_INVALID;
	}

	// Prepare MFRC522
	PCD_ClearRegisterBitMask(COLL_REG, 0x80);		// ValuesAfterColl=1 => Bits received after collision are cleared.

	// Repeat Cascade Level loop until we have a complete UID.
	uidComplete = 0;
	while (!uidComplete) {
		// Set the Cascade Level in the SEL byte, find out if we need to use the Cascade Tag in byte 2.
		switch (cascadeLevel) {
		case 1:
			buffer[0] = PICC_SEL_CL1_CMD;
			uidIndex = 0;
			useCascadeTag = validBits && uid->size > 4;	// When we know that the UID has more than 4 bytes
			break;

		case 2:
			buffer[0] = PICC_SEL_CL2_CMD;
			uidIndex = 3;
			useCascadeTag = validBits && uid->size > 7;	// When we know that the UID has more than 7 bytes
			break;

		case 3:
			buffer[0] = PICC_SEL_CL3_CMD;
			uidIndex = 6;
			useCascadeTag = 0;						// Never used in CL3.
			break;

		default:
			return STATUS_INTERNAL_ERROR;
			break;
		}

		// How many UID bits are known in this Cascade Level?
		currentLevelKnownBits = validBits - (8 * uidIndex);
		if (currentLevelKnownBits < 0) {
			currentLevelKnownBits = 0;
		}
		// Copy the known bits from uid->uidByte[] to buffer[]
		index = 2; // destination index in buffer[]
		if (useCascadeTag) {
			buffer[index++] = PICC_CT_CMD;
		}
		uint8_t bytesToCopy = currentLevelKnownBits / 8 + (currentLevelKnownBits % 8 ? 1 : 0); // The number of bytes needed to represent the known bits for this level.
		if (bytesToCopy) {
			uint8_t maxBytes = useCascadeTag ? 3 : 4; // Max 4 bytes in each Cascade Level. Only 3 left if we use the Cascade Tag
			if (bytesToCopy > maxBytes) {
				bytesToCopy = maxBytes;
			}
			for (count = 0; count < bytesToCopy; count++) {
				buffer[index++] = uid->uidByte[uidIndex + count];
			}
		}
		// Now that the data has been copied we need to include the 8 bits in CT in currentLevelKnownBits
		if (useCascadeTag) {
			currentLevelKnownBits += 8;
		}

		// Repeat anti collision loop until we can transmit all UID bits + BCC and receive a SAK - max 32 iterations.
		selectDone = 0;
		while (!selectDone) {
			// Find out how many bits and bytes to send and receive.
			if (currentLevelKnownBits >= 32) { // All UID bits in this Cascade Level are known. This is a SELECT.
				//Serial.print(F("SELECT: currentLevelKnownBits=")); Serial.println(currentLevelKnownBits, DEC);
				buffer[1] = 0x70; // NVB - Number of Valid Bits: Seven whole bytes
				// Calculate BCC - Block Check Character
				buffer[6] = buffer[2] ^ buffer[3] ^ buffer[4] ^ buffer[5];
				// Calculate CRC_A
				result = PCD_CalculateCRC(buffer, 7, &buffer[7]);
				if (result != STATUS_OK) {
					return result;
				}
				txLastBits		= 0; // 0 => All 8 bits are valid.
				bufferUsed		= 9;
				// Store response in the last 3 bytes of buffer (BCC and CRC_A - not needed after tx)
				responseBuffer	= &buffer[6];
				responseLength	= 3;
			}
			else { // This is an ANTICOLLISION.
				//Serial.print(F("ANTICOLLISION: currentLevelKnownBits=")); Serial.println(currentLevelKnownBits, DEC);
				txLastBits		= currentLevelKnownBits % 8;
				count			= currentLevelKnownBits / 8;	// Number of whole bytes in the UID part.
				index			= 2 + count;					// Number of whole bytes: SEL + NVB + UIDs
				buffer[1]		= (index << 4) + txLastBits;	// NVB - Number of Valid Bits
				bufferUsed		= index + (txLastBits ? 1 : 0);
				// Store response in the unused part of buffer
				responseBuffer	= &buffer[index];
				responseLength	= sizeof(buffer) - index;
			}

			// Set bit adjustments
			rxAlign = txLastBits;											// Having a separate variable is overkill. But it makes the next line easier to read.
			PCD_WriteRegister(BIT_FRAMING_REG, (rxAlign << 4) + txLastBits);	// RxAlign = BitFramingReg[6..4]. TxLastBits = BitFramingReg[2..0]

			// Transmit the buffer and receive the response.
			result = PCD_TransceiveData(buffer, bufferUsed, responseBuffer, &responseLength, &txLastBits, rxAlign, 0);
			if (result == STATUS_COLLISION) { // More than one PICC in the field => collision.
				uint8_t valueOfCollReg = PCD_ReadRegister(COLL_REG); // CollReg[7..0] bits are: ValuesAfterColl reserved CollPosNotValid CollPos[4:0]
				if (valueOfCollReg & 0x20) { // CollPosNotValid
					return STATUS_COLLISION; // Without a valid collision position we cannot continue
				}
				uint8_t collisionPos = valueOfCollReg & 0x1F; // Values 0-31, 0 means bit 32.
				if (collisionPos == 0) {
					collisionPos = 32;
				}
				if (collisionPos <= currentLevelKnownBits) { // No progress - should not happen
					return STATUS_INTERNAL_ERROR;
				}
				// Choose the PICC with the bit set.
				currentLevelKnownBits	= collisionPos;
				count			= currentLevelKnownBits % 8; // The bit to modify
				checkBit		= (currentLevelKnownBits - 1) % 8;
				index			= 1 + (currentLevelKnownBits / 8) + (count ? 1 : 0); // First byte is index 0.
				buffer[index]	|= (1 << checkBit);
			}
			else if (result != STATUS_OK) {
				return result;
			}
			else { // STATUS_OK
				if (currentLevelKnownBits >= 32) { // This was a SELECT.
					selectDone = 1; // No more anticollision
					// We continue below outside the while.
				}
				else { // This was an ANTICOLLISION.
					// We now have all 32 bits of the UID in this Cascade Level
					currentLevelKnownBits = 32;
					// Run loop again to do the SELECT.
				}
			}
		} // End of while (!selectDone)

		// We do not check the CBB - it was constructed by us above.

		// Copy the found UID bytes from buffer[] to uid->uidByte[]
		index			= (buffer[2] == PICC_CT_CMD) ? 3 : 2; // source index in buffer[]
		bytesToCopy		= (buffer[2] == PICC_CT_CMD) ? 3 : 4;
		for (count = 0; count < bytesToCopy; count++) {
			uid->uidByte[uidIndex + count] = buffer[index++];
		}

		// Check response SAK (Select Acknowledge)
		if (responseLength != 3 || txLastBits != 0) { // SAK must be exactly 24 bits (1 byte + CRC_A).
			return STATUS_ERROR;
		}
		// Verify CRC_A - do our own calculation and store the control in buffer[2..3] - those bytes are not needed anymore.
		result = PCD_CalculateCRC(responseBuffer, 1, &buffer[2]);
		if (result != STATUS_OK) {
			return result;
		}
		if ((buffer[2] != responseBuffer[1]) || (buffer[3] != responseBuffer[2])) {
			return STATUS_CRC_WRONG;
		}
		if (responseBuffer[0] & 0x04) { // Cascade bit set - UID not complete yes
			cascadeLevel++;
		}
		else {
			uidComplete = 1;
			uid->sak = responseBuffer[0];
		}
	} // End of while (!uidComplete)

	// Set correct uid->size
	uid->size = 3 * cascadeLevel + 1;

	return STATUS_OK;
}

uint8_t PICC_HaltA()
{
	uint8_t result;
	uint8_t buffer[4];

	// Build command buffer
	buffer[0] = PICC_HLTA_CMD;
	buffer[1] = 0;
	// Calculate CRC_A
	result = PCD_CalculateCRC(buffer, 2, &buffer[2]);
	if (result != STATUS_OK) {
		return result;
	}

	// Send the command.
	// The standard says:
	//		If the PICC responds with any modulation during a period of 1 ms after the end of the frame containing the
	//		HLTA command, this response shall be interpreted as 'not acknowledge'.
	// We interpret that this way: Only STATUS_TIMEOUT is a success.
	result = PCD_TransceiveData(buffer, sizeof(buffer), NULL, 0, NULL, 0, 0);
	if (result == STATUS_TIMEOUT) {
		return STATUS_OK;
	}
	if (result == STATUS_OK) { // That is ironically NOT ok in this case ;-)
		return STATUS_ERROR;
	}
	return result;
}

uint8_t PICC_GetType(uint8_t sak)
{
	// http://www.nxp.com/documents/application_note/AN10833.pdf
	// 3.2 Coding of Select Acknowledge (SAK)
	// ignore 8-bit (iso14443 starts with LSBit = bit 1)
	// fixes wrong type for manufacturer Infineon (http://nfc-tools.org/index.php?title=ISO14443A)
	sak &= 0x7F;
	switch (sak) {
	case 0x04:	return PICC_NOT_COMPLETE_TYPE;	// UID not complete
	case 0x09:	return PICC_MIFARE_MINI_TYPE;
	case 0x08:	return PICC_MIFARE_1K_TYPE;
	case 0x18:	return PICC_MIFARE_4K_TYPE;
	case 0x00:	return PICC_MIFARE_UL_TYPE;
	case 0x10:
	case 0x11:	return PICC_MIFARE_PLUS_TYPE;
	case 0x01:	return PICC_TNP3XXX_TYPE;
	case 0x20:	return PICC_ISO_14443_4_TYPE;
	case 0x40:	return PICC_ISO_18092_TYPE;
	default:	return PICC_UNKNOWN_TYPE;
	}
}

uint8_t PICC_IsNewCardPresent()
{
	uint8_t bufferATQA[2];
	uint8_t bufferSize = sizeof(bufferATQA);

	// Reset baud rates
	PCD_WriteRegister(TX_MODE_REG, 0x00);
	PCD_WriteRegister(RX_MODE_REG, 0x00);
	// Reset ModWidthReg
	PCD_WriteRegister(MOD_WIDTH_REG, 0x26);

	uint8_t result = PICC_RequestA(bufferATQA, &bufferSize);
	return (result == STATUS_OK || result == STATUS_COLLISION);
}
uint8_t PICC_ReadCardSerial()
{
	uint8_t result = PICC_Select(&uid, 0);
	return (result == STATUS_OK);
}
