#include "sms.h"




void checkSMS(void){

//	todo: connect SMS variable to SMS info / interrupt
	char buffer[BUFSIZE]={'\0'};
	char str[BUFSIZE]={'\0'};


	if (SMS==SMS_recieved){

		USART2_Debug("SMS recieved!");
		LPUART1_SendString("AT+CMGL=\"REC UNREAD\"\r\n");

		HAL_Delay(500);
		LPUART_handler(str);

		SMS=SMS_read;


	}


	if(strstr(buffer,"GPS")) sendLocation(phoneNumber);



}

void sendLocation(char *number){

	int i;

}


void setMessageFlag(int *messageFlag){

	*messageFlag=1;
}


void checkMessage(int *messageFlag, char *str){

	char * token;
	char * string;
	int cnt=0;

	strcpy(auxBuffer,str);

	if (*messageFlag){

		token = strtok (auxBuffer," ,.-");
		  while (token != NULL)
		  {
		    string=token;
			cnt++;
			messageStruct=parseMessage(cnt,string,messageStruct);

		    token = strtok (NULL, " ,.-");
		  }

		*messageFlag=0;

		  sprintf(messageBuffer,"\r\n%s %s\r\n",
				  messageStruct.phone,messageStruct.text);
		  USART2_SendString(messageBuffer);
	}

}



message parseMessage (int cnt,char *string,message message){


	switch (cnt) {

	case 5:
		  USART2_Debug("message5");
		break;
	case 6:
		  USART2_Debug("message6");
		break;
	case 7:
		  USART2_Debug("message7");
		break;
	case 8:
		  USART2_Debug("message8");
		break;
	case 9:
		  USART2_Debug("message9");
		break;
	case 10:
		  USART2_Debug("message10");
		break;
	default:
		break;

	}
	USART2_SendString(string);

	return message;
}
