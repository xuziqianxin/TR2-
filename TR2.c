/**
  ******************************************************************************
  * @file           : TR.c
  * @brief          : TR C file
	* @author					: xu_zi_qian_xin
  ******************************************************************************
  */
#include "TR2.h"

TR2Config_t config ={ 0 };

/**
	* @brief TR2 module initialization
	*	@param[in] selfid moudle id 
	* @param[in] rfpower rf work power (dbm) data range 0 ~ 14
	* @param[in] baudrate moudle baudrate data range 0 ~ 6
	* @param[in] channel correspondence channel data range 0 ~ 127
	*/
ErrorCode TR2_Init(uint16_t selfid, uint16_t netid, uint8_t rfpower, uint8_t baudrate, uint8_t channel)
{
	HAL_Delay(500);
	uint8_t TxBuffer[18] = { 0 };
	uint8_t RxBuffer[18] = { 0 };
	uint8_t CheckSum = 0;
	uint8_t RxCheck = 0;
	
	TxBuffer[PACK_HEAD_H] = 0xAA;
	TxBuffer[PACK_HEAD_L] = 0x5A;
	TxBuffer[SELF_ID_H] = selfid;
	TxBuffer[SELF_ID_L] = selfid >> 8;
	TxBuffer[NET_ID_H] = netid;
	TxBuffer[NET_ID_L] = netid >> 8;
	TxBuffer[RF_POWER] = rfpower;
	TxBuffer[BAUD_RATE] = baudrate;
	TxBuffer[CHANNEL] = channel;
	TxBuffer[BYTELANGTH] = 0x12;
	for(uint8_t i = 0; i < sizeof(TxBuffer); i++)
	{
		CheckSum += TxBuffer[i];
	}
	TxBuffer[CHECKBYTE] = CheckSum;
	CS_L;
	SET_L;
	
	TRANSMIT(TxBuffer, sizeof(TxBuffer));
	
	CS_L; 
	SET_H;
	
	RECEIVE(RxBuffer, sizeof(RxBuffer), 0xFFFF);
	
	for(uint8_t i = 0; i < (sizeof(RxBuffer)-1); i++)
	{
		RxCheck += RxBuffer[i];
	}
	
	if(RxCheck == RxBuffer[CHECKBYTE])
	{
		CS_H;
		return SUCES;
	}
	else
	{
		CS_H;
		return FAIL;
	}
}

/**
	* @brief Transfer data functions
	* @param[in] dataPoint Data array address
	* @param[in] size The size of the data array
	*/
void Data_Transmit(uint8_t *dataPoint, uint32_t size)
{
	CS_L;
	SET_H;
	TRANSMIT(dataPoint, size);
	CS_H;
}

/**
	* @brief Receive data functions
	* @param[out] dataPoint An array of addresses for receiving data is used for outgoing data
	* @param[in] size	The size of the data array
	* @param[in] timeOut The maximum wait time for receiving data
	*/
void Data_Receive(uint8_t *dataPoint, uint32_t size, uint16_t timeOut)
{
	CS_L;
	SET_H;
	DELAY(3);
	RECEIVE(dataPoint, size, timeOut);
	CS_H;
}

