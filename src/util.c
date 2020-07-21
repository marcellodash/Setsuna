/*******************************************************************************
*	<util.c> - github.com/raphasanori/Setsuna
*	Author: @RaphaSanOri
*	Content: Util Function Definitions
*
*	This file is part of the Setsuna app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/raphasanori/Setsuna/blob/master/LICENSE.TXT
*/

#include <util.h>
#include <string.h>
#include <windows.h>

void normalize_string(char* string) {
	while (string[0] != '\0') {
		if (string[0] == '?') {
			string[0] = ';';
		}
		string++;
	}
}

void denormalize_string(char* string) {
	while (string[0] != '\0') {
		if (string[0] == ';') {
			string[0] = '?';
		}
		string++;
	}
}

char* sjis2utf8(char* sjis) {
	LPCCH pSJIS = (LPCCH)sjis;
	LPTSTR pUTF8;
	int utf16size = MultiByteToWideChar(932, MB_ERR_INVALID_CHARS, pSJIS, -1, 0, 0);
	if (utf16size != 0) {
		LPWSTR pUTF16 = malloc(utf16size * sizeof(WCHAR));
		if (MultiByteToWideChar(932, 0, (LPCCH)pSJIS, -1, pUTF16, utf16size) != 0) {
			int utf8size = WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, 0, 0, 0, 0);
			if (utf8size != 0) {
				pUTF8 = malloc(sizeof(TCHAR) * (utf8size + 16));
				ZeroMemory(pUTF8, utf8size + 16);
				if (WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, pUTF8, utf8size, 0, 0) != 0) {
					//OK
				}
			}
		}
		free(pUTF16);
	}
	return pUTF8;
}


char* utf82sjis(char* utf8, int* size) {
	int sizew = strlen(utf8);
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, utf8, sizew + 1, NULL, 0);
	wchar_t* bufUnicode = malloc(lenghtUnicode * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, utf8, sizew + 1, bufUnicode, lenghtUnicode);
	int lengthSJis = WideCharToMultiByte(932, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
	char* bufShiftJis = malloc(sizeof(char) * lengthSJis);
	WideCharToMultiByte(932, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);
	*size = lengthSJis;
	free(bufUnicode);
	return bufShiftJis;
}
