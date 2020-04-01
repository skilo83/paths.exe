/*
 *  Created on: Mar 31, 2020
 *      Author: github.com/skilo83
 *      Version: 1.2
 */


#include <windows.h>
#include <userenv.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXPATH 900
#define DEFAULT_FONT_COLOR 7

int main(void){

	WIN32_FIND_DATA lpFindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char pathBuf[MAXPATH];
	int fResult = 0;
	HANDLE hConsole = INVALID_HANDLE_VALUE;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ZeroMemory(pathBuf, sizeof(pathBuf));

	hFind = FindFirstFileA("*", &lpFindFileData);
	do{
		SetConsoleTextAttribute(hConsole, 11);
		fResult = FindNextFileA(hFind, &lpFindFileData);
		GetFullPathNameA(lpFindFileData.cFileName, sizeof(pathBuf), pathBuf, NULL);
		
		if ((lpFindFileData.dwFileAttributes) & (FILE_ATTRIBUTE_DIRECTORY == 16)){
			SetConsoleTextAttribute(hConsole, 12);
		}

		if (lpFindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
			SetConsoleTextAttribute(hConsole, 12);
		}

		if (fResult != 0){
			printf("%s\n", pathBuf);
		}

		ZeroMemory(pathBuf, sizeof(pathBuf));

	} while (fResult != 0);

	SetConsoleTextAttribute(hConsole, DEFAULT_FONT_COLOR);
	CloseHandle(hConsole);
	FindClose(hFind);
	return 0;
}
