#ifndef FRAME_H_
#define FRAME_H_

#include "main.h"
#include "string.h"
#include "Compiler.h"
#include "Std_Types.h"
#include "CRC32.h"
#include "FileHandle.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;


#define MY_UART huart6

#define COMMAND_FRAME_LENGHT 10
#define HEADER_FRAME_LENGHT 13
#define DATA_LENGHT 1024
#define DATA_FRAME_LENGHT 9 + DATA_LENGHT


#define FLASH_SLOT_0_ADD	0x08020000
#define FLASH_SLOT_1_ADD	0x08040000
#define FLASH_SLOT_2_ADD	0x08060000

/* Number of frame data, for example: Length of file is 9.5Kbyte then Number = 10 */
static uint8_t Frame_NumberOfKbyteData = 0;
static uint16_t Frame_DataLenghtPerFrame = 0;

typedef enum{
	FLASH_SLOT_0 = 0x00,
	FLASH_SLOT_1,
	FLASH_SLOT_2
}defFlashSlot;

typedef enum{
    SOF_SIGNAL = 0x00,
    EOF_SIGNAL
}defTerminateFrame;

typedef enum{
    START_COMMAND = 0x00,
    STOP_COMMAND,
    HEADER_COMMAND,
}defCommandType;

typedef enum{
    COMMAND_TYPE = 0x00,
    HEADER_TYPE,
    DATA_TYPE,
    RESPONSE_TYPE
}defPacketType;


typedef enum{
    RESPONSE_ACK = 0x00,
    RESPONSE_NACK,
    RESPONSE_ABORT
}defResponseType;

typedef enum{
    HANDLE_OK = 0x00,
    HANDLE_FAILED
}defReturnType;

/* Convert from 4 bytes to uin32 type */
typedef union{
	uint8_t DataArray[4];
    uint32 DataUint32;
}uint32To4Bytes;

typedef struct{
	uint8_t DataSize[4];
    uint8_t Reserved1[4];
    uint8_t Reserved2[4];
    uint8_t Reserved3[4];
}defMetaInfo;

typedef struct{
	uint8_t Sof;
	uint8_t Type;
	uint8_t DataLength[2];
    uint8_t Command;
    uint32To4Bytes Crc;
    uint8_t Eof;
}defCommandPacket;

typedef struct{
	uint8_t Sof;
	uint8_t Type;
	uint8_t DataLength[2];
	uint8_t Datainfo[4];
    uint32To4Bytes Crc;
    uint8_t Eof;
}defHeaderPacket;

typedef struct{
	uint8_t Sof;
	uint8_t Type;
	uint8_t DataLenght[2];
	uint8_t* Data;
    uint32To4Bytes Crc;
    uint8_t Eof;
}defDataPacket;

typedef struct{
	uint8_t Sof;
	uint8_t Type;
	uint8_t DataLength[2];
    uint8_t Command;
    uint32To4Bytes Crc;
    uint8_t Eof;
}defResponsePacket;

typedef enum{
	RESET_NORMAL = 0x00,
	RESET_OTA
}defResetCause;

typedef struct{
	uint8_t FlashOnGoing;
	uint8_t FlashIdle;
	uint16_t NoSizeInSlot1;
	uint16_t NoSizeInSlot2;
	uint16_t NoSizeInSlot3;
	defResetCause ResetCause;
}defFlashCfg;

static defFlashCfg	Flash_Cfg;

void Frame_SendResponseFrame(defResponseType response);
defReturnType Frame_ReadStartFrame();
defReturnType Frame_ReadStopFrame();
defReturnType Frame_ReadHeaderFrame();
defReturnType Frame_ReadDataFrame(uint8_t* data);
defResponseType Frame_CheckSum(uint8_t* res_frame);
defReturnType Frame_WriteToFlash(uint8_t slot, uint8_t* data);
defReturnType Frame_STM32OTA();
defReturnType Frame_InitFlash(uint8_t slot); //call only one time.
defReturnType Frame_WriteFlashToSlot(uint8_t slot, uint8_t* data, uint16_t lenght);
#endif 
