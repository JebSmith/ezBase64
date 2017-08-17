#include "ezBase64.h"

#define EZ_STR_INIT ""
#define EZ_STR_MAKE_INIT(str) str=EZ_STR_INIT

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


char ezBase64set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklnmopqrstuvwxyz0123456789+/";

char*ezAppendData(char*str1,char*str2) 
{
	char* ezReturn = (char*)malloc(strlen(str1)+strlen(str2)+1);
	sprintf(ezReturn,"%s%s",str1,str2);
	return ezReturn;
}

void ezBase64ZeroMem(char*ezInput,int size)
{
	for (int i = 0;i<size;i++)
	{
		ezInput[i] = '\0';
	}
}

unsigned char ezBase642Char(char c) {
	if(c >='A' && c <='Z') 
		return c - 'A';
	if(c >='a' && c <='z') 
		return c - 71;
	if(c >='0' && c <='9') 
		return c + 4;
	if(c == '+') 
		return 62;
	if(c == '/') 
		return 63;
	return -1;
}

void ezBase2Bin(char*ezInput,char*ezBin)
{
	int tot = 0;
	for (int i = 0; i < 4; i++)
	{
		if (ezInput[i] != '=')
			tot++;
		else
			break;
	}
	switch(tot)
	{
		case 2:
			ezBin[0] = (ezBase642Char(ezInput[0]) << 2) | ((ezBase642Char(ezInput[1]) & 0xf0) >> 4);
			ezBin[1] = '\0';
			break;
		case 3:
			ezBin[0] = (ezBase642Char(ezInput[0]) << 2) | ((ezBase642Char(ezInput[1]) & 0xf0) >> 4);
			ezBin[1] = ((ezBase642Char(ezInput[1]) & 0xf) << 4) | ((ezBase642Char(ezInput[2]) & 0x3c)  >> 2);
			ezBin[2] = '\0';
			break;
		case 4:
			ezBin[0] = (ezBase642Char(ezInput[0]) << 2) | ((ezBase642Char(ezInput[1]) & 0xf0) >> 4);
			ezBin[1] = ((ezBase642Char(ezInput[1]) & 0xf) << 4) | ((ezBase642Char(ezInput[2]) & 0x3c)  >> 2);
			ezBin[2] = ((ezBase642Char(ezInput[2])&0x3) << 6) | (ezBase642Char(ezInput[3]));
			break;
		default:
			break;
	}
}

void ezBin2base(char*ezInput,char*ezBase) 
{
	int tot = 0;
	for (int i = 0; i < 4; i++)
	{
		if (ezInput[i] != '\0')
			tot++;
	}
	switch(tot)
	{
		case 1:
			ezBase[0] = ezBase64set[(ezInput[0] >> 2)];
			ezBase[1] = ezBase64set[(((ezInput[0] & 0x03) << 4) | ((ezInput[1] & 0xf0) >> 4))]; 
			ezBase[2] = '=';
			ezBase[3] = '=';
			break;
		case 2:
			ezBase[0] = ezBase64set[(ezInput[0] >> 2)];
			ezBase[1] = ezBase64set[(((ezInput[0] & 0x03) << 4) | ((ezInput[1] & 0xf0) >> 4))]; 
			ezBase[2] = ezBase64set[(((ezInput[1] & 0x0f) << 2) | ((ezInput[2] & 0xc0) >> 6))];
			ezBase[3] = '=';
			break;
		case 3:
			ezBase[0] = ezBase64set[(ezInput[0] >> 2)];
			ezBase[1] = ezBase64set[(((ezInput[0] & 0x03) << 4) | ((ezInput[1] & 0xf0) >> 4))]; 
			ezBase[2] = ezBase64set[(((ezInput[1] & 0x0f) << 2) | ((ezInput[2] & 0xc0) >> 6))];
			ezBase[3] = ezBase64set[(ezInput[2] & 0x3f)];
			break;
		default:
			break;
	}
}

char* ezBase64Encode(char*ezInput,int size)
{
	char*ezReturn = EZ_STR_INIT;
	int ezTempCounter = 0;
	char ezTempBuffer[4];
	char finas[5];
	ezBase64ZeroMem(ezTempBuffer,4);
	ezBase64ZeroMem(finas,5);
	int i = 0;
	while (i < size)
	{
		
		if (ezTempCounter < 3)
		{
			ezTempBuffer[ezTempCounter] = ezInput[i];
			ezTempCounter++;
			i++;
		}
		else 
		{
			ezBin2base(ezTempBuffer,finas);
			ezReturn = ezAppendData(ezReturn,finas);
			ezBase64ZeroMem(ezTempBuffer,4);
			ezBase64ZeroMem(finas,5);
			ezTempCounter = 0;
		}
	}
	ezBin2base(ezTempBuffer,finas);
	ezReturn = ezAppendData(ezReturn,finas);
	ezBase64ZeroMem(ezTempBuffer,4);
	ezBase64ZeroMem(finas,5);
	ezTempCounter = 0;
	return ezReturn;
}

char* ezBase64Decode(char*ezInput,int size)
{
	char*ezReturn = EZ_STR_INIT;
	int ezTempCounter = 0;
	char ezTempBuffer[5];
	char finas[5];
	ezBase64ZeroMem(ezTempBuffer,5);
	ezBase64ZeroMem(finas,5);
	int i = 0;
	while (i < size)
	{
		
		if (ezTempCounter < 4)
		{
			ezTempBuffer[ezTempCounter] = ezInput[i];
			ezTempCounter++;
			i++;
		}
		else 
		{
			ezBase2Bin(ezTempBuffer,finas);
			ezReturn = ezAppendData(ezReturn,finas);
			ezBase64ZeroMem(ezTempBuffer,5);
			ezBase64ZeroMem(finas,5);
			ezTempCounter = 0;
		}
	}
	ezBase2Bin(ezTempBuffer,finas);
	ezReturn = ezAppendData(ezReturn,finas);
	ezBase64ZeroMem(ezTempBuffer,5);
	ezBase64ZeroMem(finas,5);
	ezTempCounter = 0;
	return ezReturn;
}


