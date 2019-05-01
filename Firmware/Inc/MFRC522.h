#ifndef MFRC522_H_
#define MFRC522_H_

#include "stm32f2xx_hal.h"
#include "spi.h"
#include "timer.h"
#include <stdlib.h>

#define MFRC522_SPI_HANDLE				&hspi1
#define MFRC522_SPI_TIMEOUT				1000 //1 second

#define MFRC522_CS_PORT					MFRC522_CS_GPIO_Port
#define MFRC522_CS_PIN					MFRC522_CS_Pin


#define MFRC522_RST_GPIO_PORT MFRC522_RST_GPIO_Port
#define MFRC522_RST_PIN MFRC522_RST_Pin

#define MFRC522_CS_HIGH					MFRC522_CS_PORT->BSRR =	(uint32_t)MFRC522_CS_PIN;
#define MFRC522_CS_LOW					MFRC522_CS_PORT->BSRR =	(uint32_t)MFRC522_CS_PIN << 16;

#define MFRC522_RST_HIGH				MFRC522_RST_PORT->BSRR =	(uint32_t)MFRC522_RST_PIN;
#define MFRC522_RST_LOW					MFRC522_RST_PORT->BSRR =	(uint32_t)MFRC522_RST_PIN << 16;

// Size of the MFRC522 FIFO
#define FIFO_SIZE 64		// The FIFO is 64 bytes.

// MFRC522 (=PCD) registers. Described in chapter 9 of the datasheet.
// When using SPI all addresses are shifted one bit left in the "SPI address byte" (section 8.1.2.3)

// ###################################
// # PCD Register address definition #
// ###################################

// Page 0: Command and status
//										0x00					// reserved for future use
#define		COMMAND_REG					((uint8_t)(0x01 << 1))	// starts and stops command execution
#define		COM_I_EN_REG				((uint8_t)(0x02 << 1))	// enable and disable interrupt request control bits
#define		DIV_I_EN_REG				((uint8_t)(0x03 << 1))	// enable and disable interrupt request control bits
#define		COM_IRQ_REG					((uint8_t)(0x04 << 1))	// interrupt request bits
#define		DIV_IRQ_REG					((uint8_t)(0x05 << 1))	// interrupt request bits
#define		ERROR_REG					((uint8_t)(0x06 << 1))	// error bits showing the error status of the last command executed
#define		STATUS_1_REG				((uint8_t)(0x07 << 1))	// communication status bits
#define		STATUS_2_REG				((uint8_t)(0x08 << 1))	// receiver and transmitter status bits
#define		FIFO_DATA_REG				((uint8_t)(0x09 << 1))	// input and output of 64 byte FIFO buffer
#define		FIFO_LEVEL_REG				((uint8_t)(0x0A << 1))	// number of bytes stored in the FIFO buffer
#define		WATER_LEVEL_REG				((uint8_t)(0x0B << 1))	// level for FIFO underflow and overflow warning
#define		CONTROL_REG					((uint8_t)(0x0C << 1))	// miscellaneous control registers
#define		BIT_FRAMING_REG				((uint8_t)(0x0D << 1))	// adjustments for bit-oriented frames
#define		COLL_REG					((uint8_t)(0x0E << 1))	// bit position of the first bit-collision detected on the RF interface
//										0x0F					// reserved for future use

// Page 1: Command
//										0x10					// reserved for future use
#define		MODE_REG					((uint8_t)(0x11 << 1))	// defines general modes for transmitting and receiving
#define		TX_MODE_REG					((uint8_t)(0x12 << 1))	// defines transmission data rate and framing
#define		RX_MODE_REG					((uint8_t)(0x13 << 1))	// defines reception data rate and framing
#define		TX_CONTROL_REG				((uint8_t)(0x14 << 1))	// controls the logical behavior of the antenna driver pins TX1 and TX2
#define		TX_ASK_REG					((uint8_t)(0x15 << 1))	// controls the setting of the transmission modulation
#define		TX_SEL_REG					((uint8_t)(0x16 << 1))	// selects the internal sources for the antenna driver
#define		RX_SEL_REG					((uint8_t)(0x17 << 1))	// selects internal receiver settings
#define		RX_THRESHOLD_REG			((uint8_t)(0x18 << 1))	// selects thresholds for the bit decoder
#define		DEMOD_REG					((uint8_t)(0x19 << 1))	// defines demodulator settings
// 						  				0x1A					// reserved for future use
// 						  				0x1B					// reserved for future use
#define		MF_TX_REG					((uint8_t)(0x1C << 1))	// controls some MIFARE communication transmit parameters
#define		MF_RX_REG					((uint8_t)(0x1D << 1))	// controls some MIFARE communication receive parameters
// 										0x1E					// reserved for future use
#define		SERIAL_SPEED_REG			((uint8_t)(0x1F << 1))	// selects the speed of the serial UART interface

// Page 2: Configuration
// 						  				0x20					// reserved for future use
#define		CRC_RESULT_REG_H			((uint8_t)(0x21 << 1))	// shows the MSB and LSB values of the CRC calculation
#define		CRC_RESULT_REG_L			((uint8_t)(0x22 << 1))
// 						  				0x23					// reserved for future use
#define		MOD_WIDTH_REG				((uint8_t)(0x24 << 1))	// controls the ModWidth setting?
// 						  				0x25					// reserved for future use
#define		RF_CFG_REG					((uint8_t)(0x26 << 1))	// configures the receiver gain
#define		GS_N_REG					((uint8_t)(0x27 << 1))	// selects the conductance of the antenna driver pins TX1 and TX2 for modulation
#define		CW_GS_P_REG					((uint8_t)(0x28 << 1))	// defines the conductance of the p-driver output during periods of no modulation
#define		MOD_GS_P_REG				((uint8_t)(0x29 << 1))	// defines the conductance of the p-driver output during periods of modulation
#define		T_MODE_REG					((uint8_t)(0x2A << 1))	// defines settings for the internal timer
#define		T_PRESCALER_REG				((uint8_t)(0x2B << 1))	// the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
#define		T_RELOAD_REG_H				((uint8_t)(0x2C << 1))	// defines the 16-bit timer reload value
#define		T_RELOAD_REG_L				((uint8_t)(0x2D << 1))
#define		T_COUNTER_VALUE_REG_H		((uint8_t)(0x2E << 1))	// shows the 16-bit timer value
#define		T_COUNTER_VALUE_REG_L		((uint8_t)(0x2F << 1))

// Page 3: Test Registers
// 						  				0x30					// reserved for future use
#define		TEST_SEL_1_REG				((uint8_t)(0x31 << 1))	// general test signal configuration
#define		TEST_SEL_2_REG				((uint8_t)(0x32 << 1))	// general test signal configuration
#define		TEST_PIN_EN_REG				((uint8_t)(0x33 << 1))	// enables pin output driver on pins D1 to D7
#define		TEST_PIN_VALUE_REG			((uint8_t)(0x34 << 1))	// defines the values for D1 to D7 when it is used as an I/O bus
#define		TEST_BUS_REG				((uint8_t)(0x35 << 1))	// shows the status of the internal test bus
#define		AUTO_TEST_REG				((uint8_t)(0x36 << 1))	// controls the digital self-test
#define		VERSION_REG					((uint8_t)(0x37 << 1))	// shows the software version
#define		ANALOG_TEST_REG				((uint8_t)(0x38 << 1))	// controls the pins AUX1 and AUX2
#define		TEST_DAC1_REG				((uint8_t)(0x39 << 1))	// defines the test value for TestDAC1
#define		TEST_DAC2_REG				((uint8_t)(0x3A << 1))	// defines the test value for TestDAC2
#define		TEST_ADC_REG				((uint8_t)(0x3B << 1))	// shows the value of ADC I and Q channels
// 						  				0x3C					// reserved for production tests
// 						  				0x3D					// reserved for production tests
// 						  				0x3E					// reserved for production tests
// 						  				0x3F					// reserved for production tests




// MFRC522 commands. Described in chapter 10 of the datasheet.

#define		PCD_IDLE_CMD				((uint8_t)(0x00))		// no action, cancels current command execution
#define		PCD_MEM_CMD					((uint8_t)(0x01))		// stores 25 bytes into the internal buffer
#define		PCD_GENERATE_RANDOM_ID_CMD	((uint8_t)(0x02))		// generates a 10-byte random ID number
#define		PCD_CALC_CRC_CMD			((uint8_t)(0x03))		// activates the CRC coprocessor or performs a self-test
#define		PCD_TRANSMIT_CMD			((uint8_t)(0x04))		// transmits data from the FIFO buffer
#define		PCD_NO_CMD_CHANGE_CMD		((uint8_t)(0x07))		// no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
#define		PCD_RECEIVE_CMD				((uint8_t)(0x08))		// activates the receiver circuits
#define		PCD_TRANSCEIVE_CMD 			((uint8_t)(0x0C))		// transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
#define		PCD_MF_AUTHENT_CMD 			((uint8_t)(0x0E))		// performs the MIFARE standard authentication as a reader
#define		PCD_SOFT_RESET_CMD			((uint8_t)(0x0F))		// resets the MFRC522





// MFRC522 RxGain[2:0] masks, defines the receiver's signal voltage gain factor (on the PCD).
// Described in 9.3.3.6 / table 98 of the datasheet at http://www.nxp.com/documents/data_sheet/MFRC522.pdf

#define		RX_GAIN_18DB				((uint8_t)(0x00 << 4))	// 000b - 18 dB, minimum
#define		RX_GAIN_23DB				((uint8_t)(0x01 << 4))	// 001b - 23 dB
#define		RX_GAIN_18DB_2				((uint8_t)(0x02 << 4))	// 010b - 18 dB, it seems 010b is a duplicate for 000b
#define		RX_GAIN_23DB_2				((uint8_t)(0x03 << 4))	// 011b - 23 dB, it seems 011b is a duplicate for 001b
#define		RX_GAIN_33DB				((uint8_t)(0x04 << 4))	// 100b - 33 dB, average, and typical default
#define		RX_GAIN_38DB				((uint8_t)(0x05 << 4))	// 101b - 38 dB
#define		RX_GAIN_43DB				((uint8_t)(0x06 << 4))	// 110b - 43 dB
#define		RX_GAIN_48DB				((uint8_t)(0x07 << 4))	// 111b - 48 dB, maximum
//For convenience
#define		RX_GAIN_MIN					RX_GAIN_18DB			// 000b - 18 dB, minimum, convenience for RxGain_18dB
#define		RX_GAIN_AVR					RX_GAIN_33DB			// 100b - 33 dB, average, convenience for RxGain_33dB
#define		RX_GAIN_MAX					RX_GAIN_48DB			// 111b - 48 dB, maximum, convenience for RxGain_48dB




// Commands sent to the PICC.
// The commands used by the PCD to manage communication with several PICCs (ISO 14443-3, Type A, section 6.4)
#define		PICC_REQA_CMD				((uint8_t)(0x26))		// REQuest command, Type A. Invites PICCs in state IDLE to go to READY and prepare for anticollision or selection. 7 bit frame.
#define		PICC_WUPA_CMD				((uint8_t)(0x52))		// Wake-UP command, Type A. Invites PICCs in state IDLE and HALT to go to READY(*) and prepare for anticollision or selection. 7 bit frame.
#define		PICC_CT_CMD					((uint8_t)(0x88))		// Cascade Tag. Not really a command, but used during anti collision.
#define		PICC_SEL_CL1_CMD			((uint8_t)(0x93))		// Anti collision/Select, Cascade Level 1
#define		PICC_SEL_CL2_CMD			((uint8_t)(0x95))		// Anti collision/Select, Cascade Level 2
#define		PICC_SEL_CL3_CMD			((uint8_t)(0x97))		// Anti collision/Select, Cascade Level 3
#define		PICC_HLTA_CMD				((uint8_t)(0x50))		// HaLT command, Type A. Instructs an ACTIVE PICC to go to state HALT.
#define		PICC_RATS_CMD           	((uint8_t)(0xE0))     	// Request command for Answer To Reset.

// The commands used for MIFARE Classic (from http://www.mouser.com/ds/2/302/MF1S503x-89574.pdf, Section 9)
// Use PCD_MFAuthent to authenticate access to a sector, then use these commands to read/write/modify the blocks on the sector.
// The read/write commands can also be used for MIFARE Ultralight.
#define		PICC_MF_AUTH_KEY_A_CMD		((uint8_t)(0x60))		// Perform authentication with Key A
#define		PICC_MF_AUTH_KEY_B_CMD		((uint8_t)(0x61))		// Perform authentication with Key B
#define		PICC_MF_READ_CMD			((uint8_t)(0x30))		// Reads one 16 byte block from the authenticated sector of the PICC. Also used for MIFARE Ultralight.
#define		PICC_MF_WRITE_CMD			((uint8_t)(0xA0))		// Writes one 16 byte block to the authenticated sector of the PICC. Called "COMPATIBILITY WRITE" for MIFARE Ultralight.
#define		PICC_MF_DECREMENT_CMD		((uint8_t)(0xC0))		// Decrements the contents of a block and stores the result in the internal data register.
#define		PICC_MF_INCREMENT_CMD		((uint8_t)(0xC1))		// Increments the contents of a block and stores the result in the internal data register.
#define		PICC_MF_RESTORE_CMD			((uint8_t)(0xC2))		// Reads the contents of a block into the internal data register.
#define		PICC_MF_TRANSFER_CMD		((uint8_t)(0xB0))		// Writes the contents of the internal data register to a block.

// The commands used for MIFARE Ultralight (from http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf, Section 8.6)
// The PICC_CMD_MF_READ and PICC_CMD_MF_WRITE can also be used for MIFARE Ultralight.
#define		PICC_UL_WRITE_CMD			((uint8_t)(0xA2))		// Writes one 4 byte page to the PICC.





// MIFARE constants that does not fit anywhere else
#define		MF_ACK						((uint8_t)(0x0A))		// The MIFARE Classic uses a 4 bit ACK/NAK. Any other value than 0xA is NAK.
#define		MF_KEY_SIZE					((uint8_t)(0x06))		// A Mifare Crypto1 key is 6 bytes.




// PICC types we can detect. Remember to update PICC_GetTypeName() if you add more.

#define		PICC_UNKNOWN_TYPE			((uint8_t)(0x00))
#define		PICC_ISO_14443_4_TYPE		((uint8_t)(0x01))		// PICC compliant with ISO/IEC 14443-4
#define		PICC_ISO_18092_TYPE			((uint8_t)(0x02))		// PICC compliant with ISO/IEC 18092 (NFC)
#define		PICC_MIFARE_MINI_TYPE		((uint8_t)(0x03))		// MIFARE Classic protocol, 320 bytes
#define		PICC_MIFARE_1K_TYPE			((uint8_t)(0x04))		// MIFARE Classic protocol, 1KB
#define		PICC_MIFARE_4K_TYPE			((uint8_t)(0x05))		// MIFARE Classic protocol, 4KB
#define		PICC_MIFARE_UL_TYPE			((uint8_t)(0x06))		// MIFARE Ultralight or Ultralight C
#define		PICC_MIFARE_PLUS_TYPE		((uint8_t)(0x07))		// MIFARE Plus
#define		PICC_MIFARE_DESFIRE_TYPE	((uint8_t)(0x08))		// MIFARE DESFire
#define		PICC_TNP3XXX_TYPE			((uint8_t)(0x09))		// Only mentioned in NXP AN 10833 MIFARE Type Identification Procedure
#define		PICC_NOT_COMPLETE_TYPE		((uint8_t)(0xFF))		// SAK indicates UID is not complete.

#define ISO_14443_4_UID_SIZE 7

// Return codes from the functions. Remember to update GetStatusCodeName() if you add more.
#define		STATUS_OK					((uint8_t)(0x00))		// Success
#define		STATUS_ERROR				((uint8_t)(0x01))		// Error in communication
#define		STATUS_COLLISION			((uint8_t)(0x02))		// Collission detected
#define		STATUS_TIMEOUT				((uint8_t)(0x03))		// Timeout in communication.
#define		STATUS_NO_ROOM				((uint8_t)(0x04))		// A buffer is not big enough.
#define		STATUS_INTERNAL_ERROR		((uint8_t)(0x05))		// Internal error in the code. Should not happen ;-)
#define		STATUS_INVALID				((uint8_t)(0x06))		// Invalid argument.
#define		STATUS_CRC_WRONG			((uint8_t)(0x07))		// The CRC_A does not match
#define		STATUS_MIFARE_NACK			((uint8_t)(0x08))		// A MIFARE PICC responded with NAK.


// A struct used for passing the UID of a PICC.
typedef struct {
	uint8_t		size;			// Number of bytes in the UID. 4, 7 or 10.
	uint8_t		uidByte[10];
	uint8_t		sak;			// The SAK (Select acknowledge) byte returned from the PICC after successful selection.
} Uid;

// A struct used for passing a MIFARE Crypto1 key
typedef struct {
	uint8_t		keyByte[MF_KEY_SIZE];
} MIFARE_Key;


extern Uid uid;								// Used by PICC_ReadCardSerial().


/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
void PCD_WriteRegister(uint8_t reg, uint8_t value);
void PCD_WriteRegister_ext(uint8_t reg, uint8_t count, uint8_t *values);
uint8_t PCD_ReadRegister(uint8_t reg);
void PCD_ReadRegister_ext(uint8_t reg, uint8_t count, uint8_t *values, uint8_t rxAlign);
void PCD_SetRegisterBitMask(uint8_t reg, uint8_t mask);
void PCD_ClearRegisterBitMask(uint8_t reg, uint8_t mask);
uint8_t PCD_CalculateCRC(uint8_t *data, uint8_t length, uint8_t *result);

/////////////////////////////////////////////////////////////////////////////////////
// Functions for manipulating the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
void PCD_Init();
void PCD_Reset();
void PCD_AntennaOn();
void PCD_AntennaOff();
uint8_t PCD_GetAntennaGain();
void PCD_SetAntennaGain(uint8_t mask);
//uint8_t PCD_PerformSelfTest();

/////////////////////////////////////////////////////////////////////////////////////
// Power control functions
/////////////////////////////////////////////////////////////////////////////////////
void PCD_SoftPowerDown();
void PCD_SoftPowerUp();

/////////////////////////////////////////////////////////////////////////////////////
// Functions for communicating with PICCs
/////////////////////////////////////////////////////////////////////////////////////
uint8_t PCD_TransceiveData(uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen, uint8_t *validBits /*= NULL*/, uint8_t rxAlign /*= 0*/, uint8_t checkCRC /*= 0*/);
uint8_t PCD_CommunicateWithPICC(uint8_t command, uint8_t waitIRq, uint8_t *sendData, uint8_t sendLen, uint8_t *backData /*= NULL*/, uint8_t *backLen /*= NULL*/, uint8_t *validBits /*= NULL*/, uint8_t rxAlign /*= 0*/, uint8_t checkCRC /*= 0*/);
uint8_t PICC_RequestA(uint8_t *bufferATQA, uint8_t *bufferSize);
uint8_t PICC_WakeupA(uint8_t *bufferATQA, uint8_t *bufferSize);
uint8_t PICC_REQA_or_WUPA(uint8_t command, uint8_t *bufferATQA, uint8_t *bufferSize);
uint8_t PICC_Select(Uid *uid, uint8_t validBits /*= 0*/);
uint8_t PICC_HaltA();
uint8_t PICC_GetType(uint8_t sak);

/*
/////////////////////////////////////////////////////////////////////////////////////
// Support functions
/////////////////////////////////////////////////////////////////////////////////////
uint8_t PCD_MIFARE_Transceive(uint8_t *sendData, uint8_t sendLen, uint8_t acceptTimeout = false);
// old function used too much memory, now name moved to flash; if you need char, copy from flash to memory
//const char *GetStatusCodeName(byte code);
static const __FlashStringHelper *GetStatusCodeName(StatusCode code);
static PICC_Type PICC_GetType(byte sak);
// old function used too much memory, now name moved to flash; if you need char, copy from flash to memory
//const char *PICC_GetTypeName(byte type);
static const __FlashStringHelper *PICC_GetTypeName(PICC_Type type);

// Support functions for debuging
void PCD_DumpVersionToSerial();
void PICC_DumpToSerial(Uid *uid);
void PICC_DumpDetailsToSerial(Uid *uid);
void PICC_DumpMifareClassicToSerial(Uid *uid, PICC_Type piccType, MIFARE_Key *key);
void PICC_DumpMifareClassicSectorToSerial(Uid *uid, MIFARE_Key *key, byte sector);
void PICC_DumpMifareUltralightToSerial();

// Advanced functions for MIFARE
DEPRECATED_MSG("name will change in next version")
void MIFARE_SetAccessBits(byte *accessBitBuffer, byte g0, byte g1, byte g2, byte g3);
DEPRECATED_MSG("will move to extra class in next version")
bool MIFARE_OpenUidBackdoor(bool logErrors);
DEPRECATED_MSG("will move to extra class in next version")
bool MIFARE_SetUid(byte *newUid, byte uidSize, bool logErrors);
DEPRECATED_MSG("will move to extra class in next version")
bool MIFARE_UnbrickUidSector(bool logErrors);
*/
/////////////////////////////////////////////////////////////////////////////////////
// Convenience functions - does not add extra functionality
/////////////////////////////////////////////////////////////////////////////////////
uint8_t PICC_IsNewCardPresent();
uint8_t PICC_ReadCardSerial();
#endif
