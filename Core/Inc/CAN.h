/*
 * CAN.h
 *
 *  Created on: Oct 14, 2023
 *      Author: gk842
 */
#include"stm32f4xx_hal.h"

extern CAN_TxHeaderTypeDef Txheader;
extern CAN_RxHeaderTypeDef Rxheader;



#ifndef INC_CAN_H_
#define INC_CAN_H_
void CAN_TXU(unsigned int CAN_ID, uint8_t a, uint8_t b , uint8_t c);
void CAN_TXU1Sensor(unsigned int CAN_ID, uint8_t a);
void CAN_RX(void);
void uint8_float(uint8_t Rxdata[8]);
void Uart( unsigned int a,float b);



#endif /* INC_CAN_H_ */
