/**
  ******************************************************************************
  * @file           : TR.h
  * @brief          : TR header file
	* @author					: xu_zi_qian_xin
  ******************************************************************************
  */
#ifndef __TR_H__
#define __TR_H__

#ifdef __cplusplus
extern "C" {
#endif 

/* Include ----------------------------------------------------------------------------------------------*/
#include "main.h"
#include "software_usart.h"

/* Macros ------------------------------------------------------------------------------------------------*/
/**
	* @brief The position of the keyword section in the array
	*/
#define PACK_HEAD_H 0
#define PACK_HEAD_L 1
#define SELF_ID_H   2
#define SELF_ID_L   3
#define NET_ID_H		4
#define NET_ID_L		5
#define RF_POWER 		7
#define BAUD_RATE		9
#define CHANNEL			11
#define BYTELANGTH	15
#define CHECKBYTE		17

/**
	* @brief The I/O function can be replaced by the chip
	*/
#define SET_H		HAL_GPIO_WritePin(SET_GPIO_Port, SET_Pin, GPIO_PIN_SET)
#define SET_L 	HAL_GPIO_WritePin(SET_GPIO_Port, SET_Pin, GPIO_PIN_RESET)
#define CS_H  	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define CS_L  	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)

/**
	* @brief The macros that transmit the data can be replaced according to the specific library
	* @param[in] dataPoint Data array address
	* @param[in] size The size of the data array
	*/
#define TRANSMIT(dataPoint, size) \
	do{																							\
			for(uint8_t i = 0; i < size; i++)						\
			{																						\
				software_TX(*(dataPoint + i));						\
			}																						\
	}while(0)

/**
	* @brief The macros that receive the data can be replaced according to the specific library
	* @param[out] dataPoint An array of addresses for receiving data is used for outgoing data
	* @param[in] size	The size of the data array
	* @param[in] timeOut The maximum wait time for receiving data
	*/
#define RECEIVE(dataPoint, size, timeOut) \
	do{																							\
			for(uint8_t i = 0; i < 18; i++)							\
			{																						\
				software_RX((dataPoint + i), timeOut);		\
			}																						\
	}while(0)

/**
	* @brief Delay function macros can be replaced depending on the library used
	*/
#define DELAY(timeOut) \
	do{																							\
		HAL_Delay(timeOut);														\
	}while(0)

/* Enum -------------------------------------------------------------------------------------------------*/
/**
	* @brief Indicates the initialization state
	*/
typedef enum
{
	FAIL = 0,
	SUCES = 1
} ErrorCode;

/* Struct -----------------------------------------------------------------------------------------------*/
/**
	* @brief The register structure of TR2
	*/
typedef struct TR2
{
	uint8_t PackHead_H;
	uint8_t PackHead_L;
	uint8_t SelfID_H;
	uint8_t SelfID_L;
	uint8_t NetID_H;
	uint8_t NetID_L;
	uint8_t RFPower;
	uint8_t BaudRate;
	uint8_t Channel;
	uint8_t ByteLangth;
	uint8_t CheckByte;
} TR2Config_t;

/* Funaction --------------------------------------------------------------------------------------------*/
ErrorCode TR2_Init(uint16_t selfid, uint16_t netid, uint8_t rfpower, uint8_t baudrate, uint8_t channel);
void Data_Receive(uint8_t *dataPoint, uint32_t size, uint16_t timeOut);
void Data_Transmit(uint8_t *dataPoint, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __TR_H__ */
