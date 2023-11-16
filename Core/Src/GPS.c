/*
 * GPS.c
 *
 *  Created on: Jul 26, 2023
 *      Author: Tarun Singh
 *
 */
#include "GPS.h"
#include "main.h"
#include"string.h"
#include "stdio.h"
#include "math.h"
uint8_t RxdataGPS[750];
char TxdataGPS[750];
char GPS_Payyload[100];
char GPS_Payyload1[100];
uint8_t buf[2];
float lat[3];
uint8_t Flag = 0;
static int Msgindex;
static int Msgindex1;
char *ptr;
char *ptr1;
char Data[150], Data1[150];
float time ,speed_knots, speed;
float Latitude, Longitude,altitude;
int Hours, Min, Sec,date;
// Initialization start for Target Vector
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void get_location(void){


	HAL_UART_Receive_DMA(&huart1, RxdataGPS, sizeof(RxdataGPS));
		Msgindex =0;
		strcpy((TxdataGPS),(char*)(RxdataGPS));
		ptr=strstr(TxdataGPS,"GPGGA");
		if (*ptr == 'G')
		{
			for (Msgindex = 0;Msgindex < 74 ; Msgindex++) {
			    GPS_Payyload[Msgindex] = *ptr;

			    if (*ptr == '\n') {
			        GPS_Payyload[Msgindex] = '\0';
			        break;
			    }

			    ptr++;

			}
			sscanf(GPS_Payyload, "GPGGA,%f,%f,%*c,%f,%*c,%*d,%*d,%*f,%f,M,%*f,M,,", &time, &Latitude, &Longitude, &altitude);
			get_velocity();
			Format_data(time, Latitude, Longitude);
			HAL_Delay(1);
		}
};

void get_velocity(void){

	Msgindex1 =0;
			strcpy((TxdataGPS),(char*)(RxdataGPS));
			ptr1=strstr(TxdataGPS,"GPRMC");
			if (*ptr1 == 'G')
			{
				for (Msgindex1 = 0;Msgindex1 < 74 ; Msgindex1++) {
							    GPS_Payyload1[Msgindex1] = *ptr1;

							    if (*ptr1 == '\n') {
							        GPS_Payyload1[Msgindex1] = '\0';
							        break;
							    }

							    ptr1++;

							}
				sscanf(GPS_Payyload1, "GPRMC,%*f,%*c,%*f,%*c,%*f,%*c,%f,%*f,%d,%*f,%*c", &speed, &date);
				HAL_Delay(1);

			}
}

void Format_data(float Time, float Lat, float Long){


	Hours = (int)Time/10000;
	Min=(int)(Time - (Hours*10000))/100;
	Sec=(int )(Time-((Hours*10000)+(Min*100)));
	Hours += 5;
	Min +=30;
	Hours += Min /60;
	Min %= 60;
	Hours %= 24;

//	sprintf(Data, "\r\n Time=%d:%d:%d  Lat=%f, Long = %f", Hours+3, Min,Sec, Latitude,Longitude);
	sprintf(Data, "\r\n Time=%d:%d:%d Lat=%f, Long = %f, Altitude = %lf,Speed = %f,date = %d",  Hours, Min,Sec, Latitude/100,Longitude/100, altitude,speed* 0.514444,date);
	HAL_UART_Transmit(&huart2, (uint8_t*)Data, strlen(Data), 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n",3, 100);


}

