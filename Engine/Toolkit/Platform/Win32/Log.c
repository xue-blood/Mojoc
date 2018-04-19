/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-08-29
 * Author: scott.cgi
 */

#include "Engine/Toolkit/Platform/Platform.h"


//----------------------------------------------------------------------------------------------------------------------
#ifdef IS_PLATFORM_WIN32
//----------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <windows.h>	

static char OutMsg[40960] = { 0 };
static char format[40960] = { 0 };

#include "Engine/Toolkit/Platform/Log.h"

void debugPrintf(char* lpOutputString, ...){
	va_list argptr;

	va_start(argptr, lpOutputString);

	memset(OutMsg, 0, sizeof(OutMsg));
	memset(format, 0, sizeof(format));


	for (int i = 0, j = 0; lpOutputString[i] != '\0'; i++)
	{
		OutMsg[j] = lpOutputString[i];
		format[j++] = lpOutputString[i];
		// If escape character
		if (lpOutputString[i] == '\\')
		{
			i++;
			continue;
		}
		// if not a substitutal character
		if (lpOutputString[i] != '%')
			continue;

		format[j++] = lpOutputString[++i];
		format[j] = '\0';
		switch (lpOutputString[i])
		{
			// string
		case 's':
		{
			char* s = va_arg(argptr, char *);
			sprintf(OutMsg, format, s);
			strcpy(format, OutMsg);
			j = strlen(format);
			strcat(format, " ");
			break;
		}
		// character
		case 'c':
		{
			char c = (char)va_arg(argptr, int);
			sprintf(OutMsg, format, c);
			strcpy(format, OutMsg);
			j = strlen(format);
			strcat(format, " ");
			break;
		}
		// integer
		case 'd':
		{
			int d = va_arg(argptr, int);
			sprintf(OutMsg, format, d);
			strcpy(format, OutMsg);
			j = strlen(format);
			strcat(format, " ");
			break;
		}
		// float
		case 'f':
		{
			float f = va_arg(argptr, float);
			sprintf(OutMsg, format, f);
			strcpy(format, OutMsg);
			j = strlen(format);
			strcat(format, " ");
			break;
		}

		}
	}
	OutputDebugStringA(OutMsg);
	va_end(argptr);
}

//----------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------
