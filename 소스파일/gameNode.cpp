#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if ( _managerInit )
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if ( _managerInit )
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
	}
	
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()	
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND : ������ �ڵ�
	//iMessage : �޽��� ���� ��ȣ
	//wParam : Ű���� �Է� �� ���콺 Ŭ�� ����
	//lParam : ���콺 ��ǥ �Է�

	PAINTSTRUCT ps;
	HDC			hdc;		//Handle Device Context

	switch (iMessage)
	{
		//������ â�� �����ɋ� �� ���� �����
		case WM_CREATE:

		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			this->render();

			EndPaint(hWnd, &ps);
		}
		break;
		case WM_TIMER:

			this->update();

		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;

		//������ â�� ����ɶ� �߻��ϴ� �޽���
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
