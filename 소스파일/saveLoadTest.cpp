#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update()
{
	if ( KEYMANAGER->isOnceKeyDown(VK_F1) ) save();
	if ( KEYMANAGER->isOnceKeyDown(VK_F2) ) load();
}

void saveLoadTest::save()
{
	//파일 입출력
	//C - FILE*
	//C++ - ifStream, ofStream
	//WIN32 - CreateFile()

	HANDLE file;
	DWORD write;

	char str[128] = "반장 일본 잘다녀와 기념품 사와";

	file = CreateFile("객체지향바이바이.txt", GENERIC_WRITE, FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile("객체지향바이바이.txt", GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "일본이라니!", MB_OK);
}