#include "stdafx.h"
#include "image.h"

//컴파일러 지시기
#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

//이미지 초기화
HRESULT image::init(int width, int height)
{
	//이미지 정보가 이미 있다면 해제
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = FALSE;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드 적용시킬 이미지
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 이미 있다면 해제
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, (LPWSTR)fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드 적용시킬 이미지
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 이미 있다면 해제
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, (LPCWSTR)fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드 적용시킬 이미지
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 이미 있다면 해제
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, (LPCWSTR)fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드 적용시킬 이미지
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 이미 있다면 해제
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, (LPCWSTR)fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드 적용시킬 이미지
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//이미지 해제
void image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = RGB(0, 0, 0);

	}
}

//제거해줄 Color 값 셋팅
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//이미지 렌더링 함수(뿌릴DC영역, left, top)
void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//복사될 DC영역
			_imageInfo->x,					//(이미지 뿌려질)복사될 X좌표(left)
			_imageInfo->y,					//(이미지 뿌려질)복사될 Y좌표(top)
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,		//복사해올 DC영역
			0, 0,					//복사해올 좌표 X, Y
			_imageInfo->width,
			_imageInfo->height,
			_transColor				//제거해줄 색상
		);
	}
	else
	{
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

//이미지 렌더링 함수(뿌릴DC영역, left, top)
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//복사될 DC영역
			destX,					//(이미지 뿌려질)복사될 X좌표(left)
			destY,					//(이미지 뿌려질)복사될 Y좌표(top)
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,		//복사해올 DC영역
			0, 0,					//복사해올 좌표 X, Y
			_imageInfo->width,
			_imageInfo->height,
			_transColor				//제거해줄 색상
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//복사될 DC영역
			destX,					//(이미지 뿌려질)복사될 X좌표(left)
			destY,					//(이미지 뿌려질)복사될 Y좌표(top)
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,		//복사해올 DC영역
			sourX, sourY,					//복사해올 좌표 X, Y
			sourWidth,
			sourHeight,
			_transColor				//제거해줄 색상
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY, SRCCOPY);
	}


}

void image::scaleRender(HDC hdc, int destX, int destY, int scaleX, int scaleY)
{

	SetStretchBltMode(getMemDC(), COLORONCOLOR);
	if (_trans)
	{
		TransparentBlt(hdc,		//복사될 DC영역
			destX,					//(이미지 뿌려질)복사될 X좌표(left)
			destY,					//(이미지 뿌려질)복사될 Y좌표(top)
			scaleX,
			scaleY,
			_imageInfo->hMemDC,		//복사해올 DC영역
			0, 0,					//복사해올 좌표 X, Y
			_imageInfo->width,
			_imageInfo->height,
			_transColor				//제거해줄 색상
		);


	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}

}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	// 예외처리
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;		//잘라올 가로크기
	int sourHeight;		//잘라올 세로크기

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//Y축부터
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//복사해와야할 세로크기
		sourHeight = rcSour.bottom - rcSour.top;

		//OffsetY 범위가 생겼다!
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//실제로 화면에 렌더 할 곳에 보정이 된 연산을 해준다
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;


		//X축 
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,	//뿌려줄 곳 X, Y
				rcSour.left, rcSour.top,			//뿌려올 곳 X, Y
				rcSour.right - rcSour.left,			//뿌려올 가로, 세로 크기
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

//프레임 번호 수로 돌릴때
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//== 실제 이미지에 알파블렌드를 접목시켜주는 함수
	///== 0~255수치로 투명도를 가지며 0에 가까울수록 투명해진다.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt							//== 뿌리는 스타일(기본)
		(
			_blendImage->hMemDC,		//== 이미지 뿌려질곳
			0,							//== 뿌려질곳 X 좌표
			0,							//== 뿌려질곳 Y 좌표
			_imageInfo->width,			//== 뿌려질 이미지 가로 사이즈
			_imageInfo->height,			//== 뿌려질 이미지 세로 사이즈
			hdc,						//== 이미지 가져올곳
			_imageInfo->x,				//== 가져올곳 X 좌표
			_imageInfo->y,				//== 가져올곳 Y 좌표
			SRCCOPY						//== 복사할거에염
		);

		GdiTransparentBlt				//== 뿌리는 스타일(특정 색상제거)
		(
			_blendImage->hMemDC,		//== 이미지 뿌려질곳
			0,							//== 뿌려질곳 X 좌표
			0,							//== 뿌려질곳 Y 좌표
			_imageInfo->width,			//== 뿌려질 이미지 가로 사이즈
			_imageInfo->height,			//== 뿌려질 이미지 세로 사이즈
			_blendImage->hMemDC,		//== 이미지 가져올곳
			0,							//== 가져올곳 X 좌표
			0,							//== 가져올곳 Y 좌표
			_imageInfo->width,			//== 가져올 이미지 가로 사이즈
			_imageInfo->height,			//== 가져올 이미지 세로 사이즈
			_transColor					//== Trans가 true일때 제거할 색상 -> RGB(0,0,0)
		);

		AlphaBlend						//== 뿌리는 스타일(특정 색상제거)
		(
			hdc,						//== 이미지 뿌려질곳
			_imageInfo->x,				//== 뿌려질곳 X 좌표
			_imageInfo->y,				//== 뿌려질곳 Y 좌표
			_imageInfo->width,			//== 뿌려질 이미지 가로 사이즈
			_imageInfo->height,			//== 뿌려질 이미지 세로 사이즈
			_blendImage->hMemDC,		//== 이미지 가져올곳
			0,							//== 가져올곳 X 좌표
			0,							//== 가져올곳 Y 좌표
			_imageInfo->width,			//== 가져올 이미지 가로 사이즈
			_imageInfo->height,			//== 가져올 이미지 세로 사이즈
			_blendFunc					//== 색상을 섞는다 -> 현재 검정색으로 셋팅되어있어서 점점 어두워지는 효과로 볼수있음
		);
	}
	else
	{
		AlphaBlend
		(
			hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend
		(
			hdc,
			destX,
			destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend
		(
			hdc,
			destX,
			destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//== 실제 이미지에 알파블렌드를 접목시켜주는 함수
	///== 0~255수치로 투명도를 가지며 0에 가까울수록 투명해진다.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt							//== 뿌리는 스타일(기본)
		(
			_blendImage->hMemDC,		//== 이미지 뿌려질곳
			0,							//== 뿌려질곳 X 좌표
			0,							//== 뿌려질곳 Y 좌표
			_imageInfo->width,			//== 뿌려질 이미지 가로 사이즈
			_imageInfo->height,			//== 뿌려질 이미지 세로 사이즈
			hdc,						//== 이미지 가져올곳
			_imageInfo->x,				//== 가져올곳 X 좌표
			_imageInfo->y,				//== 가져올곳 Y 좌표
			SRCCOPY						//== 복사할거에염
		);

		GdiTransparentBlt				//== 뿌리는 스타일(특정 색상제거)
		(
			_blendImage->hMemDC,		//== 이미지 뿌려질곳
			destX,						//== 뿌려질곳 X 좌표
			destY,						//== 뿌려질곳 Y 좌표
			sourWidth,					//== 뿌려질 이미지 가로 사이즈
			sourHeight,					//== 뿌려질 이미지 세로 사이즈
			_imageInfo->hMemDC,			//== 이미지 가져올곳
			sourX,						//== 가져올곳 X 좌표
			sourY,						//== 가져올곳 Y 좌표
			sourWidth,					//== 가져올 이미지 가로 사이즈
			sourHeight,					//== 가져올 이미지 세로 사이즈
			_transColor					//== Trans가 true일때 제거할 색상 -> RGB(0,0,0)
		);

		AlphaBlend						//== 뿌리는 스타일(특정 색상제거)
		(
			hdc,						//== 이미지 뿌려질곳
			destX,						//== 뿌려질곳 X 좌표
			destY,						//== 뿌려질곳 Y 좌표
			_imageInfo->width,			//== 뿌려질 이미지 가로 사이즈
			_imageInfo->height,			//== 뿌려질 이미지 세로 사이즈
			_blendImage->hMemDC,		//== 이미지 가져올곳
			sourX,						//== 가져올곳 X 좌표
			sourY,						//== 가져올곳 Y 좌표
			sourWidth,					//== 가져올 이미지 가로 사이즈
			sourHeight,					//== 가져올 이미지 세로 사이즈
			_blendFunc					//== 색상을 섞는다 -> 현재 검정색으로 셋팅되어있어서 점점 어두워지는 효과로 볼수있음
		);
	}
	else
	{
		BitBlt
		(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			SRCCOPY
		);
	}
}
//프레임 번호 수로 돌릴때
void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			_blendImage->hMemDC,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			hdc,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);


	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}