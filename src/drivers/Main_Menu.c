#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"

#define MAXLEN 100
#define MAX_RECV_BUFF_SIZE  1024
#define MAX_SEND_BUFF_SIZE  512
#define MAX_HOSTNAME_SIZE   40
#define MAX_PASSKEY_SIZE    32
#define MAX_SSID_SIZE       32

uint32_t choice;
char input[MAXLEN], input2[MAXLEN];
extern char SendBuff[MAX_SEND_BUFF_SIZE];
//string REQUEST;

extern char UART_InChar(void);
extern void UART_OutString(char *pt);
extern void UART_InString(char *bufPt, uint16_t max);
extern uint32_t UART_InUDec(void);
void BuildCityNameRequest(char *request, char *city);
void BuildCoordRequest(char *request, char *lat, char *lon);
void Main_Menu(void);

void BuildCityNameRequest(char *request, char *city){
	sprintf(request,"GET /data/2.5/weather?q=%s&APPID=e04d17d588df2af70a56e4f331d0ffd5&units=imperial HTTP/1.1\r\n"
    "User-Agent: Keil\r\n"
    "Host:api.openweathermap.org\r\n"
    "Accept: */*\r\n\r\n",
    city);
}

void BuildCityIDRequest(char *request, char *cityID) {
	sprintf(request,  "GET /data/2.5/weather?id=%s&APPID=e04d17d588df2af70a56e4f331d0ffd5&units=imperial HTTP/1.1\r\n"
    "User-Agent: Keil\r\n"
    "Host:api.openweathermap.org\r\n"
    "Accept: */*\r\n\r\n",
    cityID);
}

void BuildCoordRequest(char *request, char *lat, char *lon){
	  sprintf(request,
    "GET /data/2.5/weather?lat=%s&lon=%s&APPID=e04d17d588df2af70a56e4f331d0ffd5&units=imperial HTTP/1.1\r\n"
    "User-Agent: Keil\r\n"
    "Host:api.openweathermap.org\r\n"
    "Accept: */*\r\n\r\n",
    lat, lon);
}

void BuildZipRequest(char *request, char *zip){
  sprintf(request,
    "GET /data/2.5/weather?zip=%s&APPID=e04d17d588df2af70a56e4f331d0ffd5&units=imperial HTTP/1.1\r\n"
    "User-Agent: Keil\r\n"
    "Host:api.openweathermap.org\r\n"
    "Accept: */*\r\n\r\n",
    zip);
}

void ReplaceSpace(const char *source, char target, const char *replacement, char *destination) {
    while (*source) {
        if (*source == target) {
            // Replace with 3 characters (e.g., replacement = "ABC")
            *destination++ = replacement[0];
            *destination++ = replacement[1];
            *destination++ = replacement[2];
        } else {
            *destination++ = *source;
        }
        source++;
    }
    *destination = '\0'; // Null-terminate the new string
}

void Main_Menu(void){
  UART_OutString("Welcome to my Embedded Weather Quester!\n\r");
  UART_OutString("Please choose your query criteria: \n\r");
  UART_OutString("1. City Name\n\r");
  UART_OutString("2. City ID\n\r");
  UART_OutString("3. Geographic Coordinates\n\r");
  UART_OutString("4. Zip Code\n\r");

	choice = UART_InUDec();
	
	UART_OutString("\n\r");

	switch(choice){
		case (1):
			UART_OutString("Enter city name :\r\n");
			UART_OutString("Example: Long Beach\r\n");
			UART_OutString("City Name: ");
			UART_InString(input, MAXLEN-1);
			UART_OutString("\r\n");
			ReplaceSpace(input, ' ', "%20", input2);
			BuildCityNameRequest(SendBuff, input2);
			break;
		case (2):
			UART_OutString("Enter city ID.\r\n");
			UART_OutString("Example: 5367929\r\n");
			UART_OutString("City ID: ");
			UART_InString(input, MAXLEN-1);
			UART_OutString("\r\n");
			BuildCityIDRequest(SendBuff, input);
			break;
		case (3):
			UART_OutString("Enter latitude.\r\n");
			UART_OutString("Example: 33.77\r\n");
			UART_OutString("Latitude: ");
			UART_InString(input, MAXLEN-1);
			UART_OutString("\r\n");

			UART_OutString("Enter longitude.\r\n");
			UART_OutString("Example: -118.19\r\n");
			UART_OutString("Longitude: ");
			UART_InString(input2, MAXLEN-1);
			UART_OutString("\r\n");
			BuildCoordRequest(SendBuff, input, input2);			
			break;
		case (4):
			UART_OutString("Enter zip code.\r\n");
			UART_OutString("Example: 90802,US\r\n");
			UART_OutString("Zip Code: ");
			UART_InString(input, MAXLEN-1);
			UART_OutString("\r\n");

			BuildZipRequest(SendBuff, input);
			break;
		default:
			UART_OutString("Invalid input, please try again. \n\r.");
			break;
	}
}