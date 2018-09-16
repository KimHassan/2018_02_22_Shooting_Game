#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "txtData.h"

using namespace OCTA_UTIL;

//=======================================
// ## - �����ι� - ## 18.01.12 ## 
//=======================================

#define WINNAME (LPSTR)(TEXT("Octa API"))
#define WINSTARTX 20
#define WINSTARTY 50
#define WINSIZEX 1000
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingeton()
#define KEYMANAGER keyManager::getSingeton()
#define IMAGEMANAGER imageManager::getSingeton()
#define TXTDATA txtData::getSingeton()

//=======================================
// ## Macro ## 18.01.31 ## 
//=======================================

#define SAFE_DELETE(p) {if(p) { delete(p); (p) = NULL; }} 
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;