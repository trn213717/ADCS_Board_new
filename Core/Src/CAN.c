/*
 * CAN.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Tarun Singh
 *
 */

#include"CAN.h"
#include "main.h"
#include"string.h"
#include "stdio.h"
#include "math.h"

uint8_t Txdata1[8];
uint8_t Rxdata1[8];
char message[30];
uint32_t Txmailbox;

extern CAN_HandleTypeDef hcan1;
extern UART_HandleTypeDef huart2;


void CAN_TXU(unsigned int CAN_ID, uint8_t a, uint8_t b , uint8_t c)
{               // unsigned int CAN_ID = 0x1A;
	  Txheader.DLC =4;//DATA LENGTH
	  Txheader.IDE= CAN_ID_STD;
	  Txheader.RTR=CAN_RTR_DATA;
	  Txheader.StdId=CAN_ID; //id
      Txdata1[0] = a;
   	  Txdata1[1] = b;
      Txdata1[2] = c;
	  HAL_CAN_AddTxMessage(&hcan1, &Txheader, Txdata1, &Txmailbox);
	  HAL_Delay(10);
}
void CAN_TXU1Sensor(unsigned int CAN_ID, uint8_t a)
{      // unsigned int CAN_ID = 0x1A;
	  Txheader.DLC =4;//DATA LENGTH
	  Txheader.IDE= CAN_ID_STD;
	  Txheader.RTR=CAN_RTR_DATA;
	  Txheader.StdId=CAN_ID; //id
      Txdata1[0] = a;
	  HAL_CAN_AddTxMessage(&hcan1, &Txheader, Txdata1, &Txmailbox);
	  HAL_Delay(1);
}
void uint8_float(uint8_t Rxdata1[8])
{
		 uint32_t intVal;
	     float receivedFloat;

	     // Convert the received bytes back to a 32-bit integer
	     intVal = 0;
	     for (int i = 0; i < 8; i++) {
	         intVal |= (Rxdata1[i] << (i * 8));
	     }

	     // Convert the integer back to a float
	     receivedFloat = *((float*)&intVal);
	     printf("%f",receivedFloat);
}
float convertBytesToFloat(uint8_t Rxdata1[4]) {
    uint32_t intVal = 0;

    // Convert the received bytes back to a 32-bit integer
    for (int i = 0; i < 4; i++) {
        intVal |= (Rxdata1[i] << (i * 8));
    }

    // Convert the integer back to a float
    float receivedFloat = *((float*)&intVal);

    return receivedFloat;
}
void CAN_RX(void){
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &Rxheader, Rxdata1);
		if(Rxheader.DLC==2)
		{

			  float result = convertBytesToFloat(Rxdata1);
			     printf("%f",result);
			     Uart( Rxheader.StdId ,result);

		}

		if (Rxheader.StdId == 0x61) {

			  float result = convertBytesToFloat(Rxdata1);
			     printf("%f",result);
			     Uart( Rxheader.StdId ,result);

		}
		 if(Rxheader.StdId == 0x63)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x64)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x65)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x66)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x67)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x68)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x69)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x70)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x71)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x72)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
		 if(Rxheader.StdId == 0x73)
				{

					  float result = convertBytesToFloat(Rxdata1);
					     printf("%f",result);
					     Uart( Rxheader.StdId ,result);

				}
};

void Uart( unsigned int a,float b){


	sprintf(message," Sensor Id %x  , %0.4f ",a,b);
	strcat(message, "\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)message, sizeof(message), 100);
}






