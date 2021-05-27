#include "sendCommand.h"

void sendCommand (char *str){


	  if (strstr(str,"help")) {
		  cleanBuffer(str);
		  USART2_SendString("\r\n");

		  USART2_SendInfo  ("aacb  : clean buffer");
		  USART2_SendInfo  ("aass0 : SMS=SMS_waiting;");
		  USART2_SendInfo  ("aass1 : SMS=SMS_recieved;");
		  USART2_SendInfo  ("aass2 : SMS=SMS_read;");
		  USART2_SendInfo  ("aass3 : SMS=SMS_waiting;");
		  USART2_SendInfo  ("aacm  :  check SMS");
		  USART2_SendInfo  ("aakey : turn on/off sim808 module with GPIO");
		  USART2_SendInfo  ("aarr  : restart mcu");
		  USART2_SendInfo  ("aact  : communication test");
		  USART2_SendInfo  ("aaoff : turn off SIM808 mobudle");
		  USART2_SendInfo  ("aaoff : turn off SIM808 mobudle");
		  USART2_SendInfo  ("aags : location status");
		  USART2_SendInfo  ("aap? : power status");
		  USART2_SendInfo  ("aagp1 : power on");
		  USART2_SendInfo  ("aagp0 : power off");
		  USART2_SendInfo  ("aagr0 : cold restart");
		  USART2_SendInfo  ("aagr1 : warm restart");
		  USART2_SendInfo  ("aagi : gps formated info");
		  USART2_SendInfo  ("aabs : battery status");
		  USART2_SendInfo  ("ath : reject call");
		//  USART2_SendInfo  ("aamd : delete message (add number)");
		//  USART2_SendInfo  ("aamr : read message");
		// USART2_SendInfo  ("aamlr : list of messages");
		  USART2_SendInfo  ("aamlu : list of unread messages");
		  USART2_SendInfo  ("aaclip : enable call info");
		  USART2_SendInfo  ("aatext : enable text mode");
		  USART2_SendInfo  ("aasleep : enter sleep mode");
		  USART2_SendInfo  ("aastop : enter stop mode");
		  USART2_SendInfo  ("aaloc : print location");
		  USART2_SendInfo  ("aanum : print phone number");
		  USART2_SendInfo  ("aastm : send test message");

	  }


	  //clean buffer
	  if (strstr(str,"aacb"))  { cleanBuffer(str);USART2_SendInfo(str);LPUART1_SendString(str);}

	  //sms commands
	  if (strstr(str,"aass0")) { cleanBuffer(str); SMS=SMS_waiting;}
	  if (strstr(str,"aass1")) { cleanBuffer(str); SMS=SMS_recieved;}
	  if (strstr(str,"aass2")) { cleanBuffer(str); SMS=SMS_read;}
	  if (strstr(str,"aass3")) { cleanBuffer(str); SMS=SMS_processed;}

	  //checkmessage
	  if (strstr(str,"aacm"))  { cleanBuffer(str);checkSMS();}

	 	  //turn on/off sim808 module with GPIO
	  if (strstr(str,"aakey")) { cleanBuffer(str); PowerOnKey();}

	  //restart mcu
	  if (strstr(str,"aarr")) { USART2_Debug("Restarting MCU!");  __NVIC_SystemReset();}

	  //perform communication test
	  if (strstr(str,"aact")) {  communicationTest();}

	  if (strstr(str,"aaoff")) {strcpy(str,"\r\nAT+CPOWD=1\r\n");LPUART1_SendString(str);}
	  // location status
	  if (strstr(str,"aags")) {strcpy(str,"\r\nAT+CGPSSTATUS?\r\n");LPUART1_SendString(str);}

	  // power status (on / off)
	  if (strstr(str,"aap?")) {strcpy(str,"\r\nAT+CGPSPWR?\r\n"); LPUART1_SendString(str);}

	  // power on
	  if (strstr(str,"aagp1")) {strcpy(str,"\r\nAT+CGPSPWR=1\r\n"); LPUART1_SendString(str);}

	  // power off
	  if (strstr(str,"aagp0")) {strcpy(str,"\r\nAT+CGPSPWR=0\r\n"); LPUART1_SendString(str);}

	  // gps cold restart
	  if (strstr(str,"aagr0")) {strcpy(str,"\r\nAT+CGPSRST=0\r\n"); LPUART1_SendString(str);}

	  // gps warm restart
	  if (strstr(str,"aagr1")) {strcpy(str,"\r\nAT+CGPSRST=1\r\n"); LPUART1_SendString(str);}

	  // gps formated information
	  if (strstr(str,"aagi")) {strcpy(str,"\r\nAT+CGPSINF=2\r\n"); LPUART1_SendString(str);}

	  // battery status
	  if (strstr(str,"aabs")) {strcpy(str,"\r\nAT+CBC\r\n"); LPUART1_SendString(str);}

	  // reject call
	  if (strstr(str,"ath")) {strcpy(str,"\r\nATH\r\n"); LPUART1_SendString(str);}

	  // delete message
	  if (strstr(str,"aamd")) {strcpy(str,"\r\nAT+CMGD="); LPUART1_SendString(str);}

	  // read message
	  if (strstr(str,"aamr")) {strcpy(str,"\r\nAT+CMGR=\r\n"); LPUART1_SendString(str);}

	  // list of read messages
	  if (strstr(str,"aamlr")) {strcpy(str,"\r\nAT+CMGL=\"REC READ\"\r\n"); LPUART1_SendString(str);}

	  // list of unread messages
	  if (strstr(str,"aamlu")) {strcpy(str,"\r\nAT+CMGL=\"REC UNREAD\"\r\n"); LPUART1_SendString(str);}

	  // enable call info
	  if (strstr(str,"aaclip")) {strcpy(str,"\r\nAT+CLIP=1\r\n"); LPUART1_SendString(str);}

	  // enable text mode
	  if (strstr(str,"aatext")) {strcpy(str,"\r\nAT+CMGF=1\r\n"); LPUART1_SendString(str);}


	  //enter SLEEP mode
	  if (strstr(str,"aasleep")) {
		  USART2_Debug("Entering SLEEP mode.");
		  HAL_SuspendTick();

		  memset(str,0,strlen(str));
		  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	  	  }

	  //enter STOP mode
	  if (strstr(str,"aastop")) {
		  USART2_Debug("Entering STOP mode.");
		  HAL_SuspendTick();

		  memset(str,0,strlen(str));
		  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	  }

	  //print location
	  if (strstr(str,"aaloc")) {

		  cleanBuffer(str);
		  sprintf(locationBuffer,"\r\n%2d.%4d %c, %2d.%4d %c\r\n",
				  locationStruct.latitude1,locationStruct.latitude2,locationStruct.lat,
				  locationStruct.longitude1,locationStruct.longitude2,locationStruct.lon);
		  USART2_SendString(locationBuffer);
	  }

	  //print phone number
	  if (strstr(str,"aanum")) {

		  cleanBuffer(str);

		  USART2_SendString("\r\nCaller ID: ");
		  sprintf(callBuffer,"\r\n %s\r\n",
				  callStruct.phone);
		  USART2_SendString(callBuffer);

		  USART2_SendString("\r\nMessenger ID : ");
		  sprintf(messageBuffer,"\r\n %s\r\n",
				  messageStruct.phone);
		  USART2_SendString(messageBuffer);

		  USART2_SendString("\r\nMessage: ");
		  sprintf(messageBuffer,"\r\n %s\r\n",
				  messageStruct.text);
		  USART2_SendString(messageBuffer);


	  }

	  // send test message
	  if (strstr(str,"aastn")) {

		  cleanBuffer(str);

	  }


	  if (strstr(str,"aabb1")) {

		  cleanBuffer(str);
		  USART2_SendString(buffer1);

	  }

	  if (strstr(str,"aabb2")) {

		  cleanBuffer(str);
		  USART2_SendString(buffer2);

	  }

	  //everything else, performed when pressed ENTER
	  if (strchr(str,'\r')) {LPUART1_SendString(str);}

}

