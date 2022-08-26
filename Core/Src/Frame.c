#include "Frame.h"


void Frame_SendResponseFrame(defResponseType response){
	defResponsePacket res_fr = {
			.Sof = SOF_SIGNAL,
			.Type = RESPONSE_TYPE,
			.DataLength = {0x00, 0x01,},
			.Command = response,
			.Eof = EOF_SIGNAL,
	};

	res_fr.Crc.DataUint32 = crc32(&response, 1);

	HAL_UART_Transmit(&MY_UART, (uint8_t*)&res_fr.Sof, 1, 1000);
	HAL_UART_Transmit(&MY_UART, (uint8_t*)&res_fr.Type, 1, 1000);
	HAL_UART_Transmit(&MY_UART, (uint8_t*)res_fr.DataLength, 2, 1000);
	HAL_UART_Transmit(&MY_UART, (uint8_t*)&res_fr.Command, 1, 1000);
	HAL_UART_Transmit(&MY_UART, (uint8_t*)res_fr.Crc.DataArray, 4, 1000);
	HAL_UART_Transmit(&MY_UART, (uint8_t*)&res_fr.Eof, 1, 1000);
}


defReturnType Frame_ReadStartFrame(){
	uint8_t buf[COMMAND_FRAME_LENGHT] = {0,};

	HAL_UART_Receive(&MY_UART, buf, COMMAND_FRAME_LENGHT, 3000);

	if(!((buf[0] == SOF_SIGNAL)&&(buf[COMMAND_FRAME_LENGHT - 1]  == EOF_SIGNAL)))
		return HANDLE_FAILED;

	if(buf[1] != COMMAND_TYPE) return HANDLE_FAILED;

	if(buf[4] != START_COMMAND) return HANDLE_FAILED;

	return HANDLE_OK;
}


defReturnType Frame_ReadStopFrame(){
	uint8_t buf[COMMAND_FRAME_LENGHT] = {0,};

	HAL_UART_Receive(&MY_UART, buf, COMMAND_FRAME_LENGHT, 3000);

	if(!((buf[0] = SOF_SIGNAL)&&(buf[COMMAND_FRAME_LENGHT - 1]  = EOF_SIGNAL)))
		return HANDLE_FAILED;

	if(buf[1] != COMMAND_TYPE) return HANDLE_FAILED;

	if(buf[4] != STOP_COMMAND) return HANDLE_FAILED;

	return HANDLE_OK;
}


defReturnType Frame_ReadHeaderFrame(){
	uint8_t buf[HEADER_FRAME_LENGHT] = {0,};
	uint32To4Bytes crc_merge;
	HAL_UART_Receive(&MY_UART, (uint8_t *) buf, HEADER_FRAME_LENGHT, 3000);

	if(!((buf[0] == SOF_SIGNAL)&&(buf[HEADER_FRAME_LENGHT - 1]  == EOF_SIGNAL)))
		return HANDLE_FAILED;

	crc_merge.DataArray[0] = buf[11];
	crc_merge.DataArray[1] = buf[10];
	crc_merge.DataArray[2] = buf[9];
	crc_merge.DataArray[3] = buf[8];

	if(buf[1] != HEADER_TYPE) return HANDLE_FAILED;

	uint32_t crc_header = crc32((uint8_t*)(&buf[0] + 4), 4);

	if(crc_header != crc_merge.DataUint32) return HANDLE_FAILED;
	Frame_NumberOfKbyteData = buf[6]*256 + buf[7];

	return HANDLE_OK;
}


defReturnType Frame_ReadDataFrame(uint8_t* data){
	uint32To4Bytes crc_merge;
	uint8_t buf[4];

	HAL_UART_Receive(&MY_UART, buf, 4, 1000);
	Frame_DataLenghtPerFrame = buf[2]*256 + buf[3];

	HAL_UART_Receive(&MY_UART, data, Frame_DataLenghtPerFrame + 5, 3000);

	if(!((buf[0] == SOF_SIGNAL)&&(data[Frame_DataLenghtPerFrame + 5 - 1] == EOF_SIGNAL))) return HANDLE_FAILED;

	if(buf[1] != DATA_TYPE) return HANDLE_FAILED;

	crc_merge.DataArray[0] = data[Frame_DataLenghtPerFrame + 5 - 2];
	crc_merge.DataArray[1] = data[Frame_DataLenghtPerFrame + 5 - 3];
	crc_merge.DataArray[2] = data[Frame_DataLenghtPerFrame + 5 - 4];
	crc_merge.DataArray[3] = data[Frame_DataLenghtPerFrame + 5 - 5];

	uint32_t crc_data = crc32((uint8_t*)(&data[0]), Frame_DataLenghtPerFrame);

	if(crc_data != crc_merge.DataUint32) return HANDLE_FAILED;

	return HANDLE_OK;
}

extern uint8_t bufff[19];
defReturnType Frame_STM32OTA(){
	if(Frame_InitFlash(FLASH_SLOT_0) != HANDLE_OK) return HANDLE_FAILED;

	Frame_SendResponseFrame(RESPONSE_ACK);

	if(Frame_ReadStartFrame() == HANDLE_OK){
		Frame_SendResponseFrame(RESPONSE_ACK);
	}
	else{
		Frame_SendResponseFrame(RESPONSE_NACK);
		Frame_ReadStopFrame();
		return HANDLE_FAILED;
	}

	if(Frame_ReadHeaderFrame() == HANDLE_OK){
		Frame_SendResponseFrame(RESPONSE_ACK);
	}
	else{
		Frame_SendResponseFrame(RESPONSE_NACK);
		Frame_ReadStopFrame();
		return HANDLE_FAILED;
	}

	for(uint16_t NoFrame = 0; NoFrame < Frame_NumberOfKbyteData; NoFrame ++){
		uint8_t buf[DATA_FRAME_LENGHT];
		if(Frame_ReadDataFrame(buf) == HANDLE_OK){
//			Frame_WriteFlashToSlot(FLASH_SLOT_0,(uint8_t*) (&buf[0]+4), DATA_FRAME_LENGHTs);
			Frame_SendResponseFrame(RESPONSE_ACK);
		}
		else{
			Frame_SendResponseFrame(RESPONSE_NACK);
			Frame_ReadStopFrame();
			return HANDLE_FAILED;
		}
	}


	HAL_FLASH_Lock();
	return HANDLE_OK;
}


defReturnType Frame_InitFlash(uint8_t slot){
	defReturnType ret;

	ret = HAL_FLASH_Unlock();
	if(ret != (uint8_t)HAL_OK){
		return HANDLE_FAILED;
	}

	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SectorError;

	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;

	if(slot == 0x00){
		EraseInitStruct.Sector        = FLASH_SECTOR_5;
	}
	else if(slot == 0x01){
		EraseInitStruct.Sector        = FLASH_SECTOR_6;
	}
	else if(slot == 0x02){
		EraseInitStruct.Sector        = FLASH_SECTOR_7;
	}
	EraseInitStruct.NbSectors     = 1;           //erase 2 sectors
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;

	ret = HAL_FLASHEx_Erase( &EraseInitStruct, &SectorError );
	if( ret != (uint8_t)HAL_OK )
	{
		return HANDLE_FAILED;
	}

	return HANDLE_OK;
}


defReturnType Frame_WriteFlashToSlot(uint8_t slot, uint8_t* data, uint16_t lenght){
	uint32_t BaseAddress = 0;
	if(slot == FLASH_SLOT_0) BaseAddress = FLASH_SLOT_0_ADD;
	else if(slot == FLASH_SLOT_1) BaseAddress = FLASH_SLOT_1_ADD;
	else if(slot == FLASH_SLOT_2) BaseAddress = FLASH_SLOT_2_ADD;
	else{}

	for(uint16_t index = 0; index < lenght; index++){
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, BaseAddress + index, data[index]) != HAL_OK)
			return HANDLE_FAILED;
	}
	return HANDLE_OK;
}

