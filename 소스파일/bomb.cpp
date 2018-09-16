#include "stdafx.h"
#include "bomb.h"


bomb::bomb()
{
}


bomb::~bomb()
{
}

HRESULT bomb::init(POINT position)
{
	img = new image;
	img->init("bomb.bmp", 7200, 100, 72, 1, true, RGB(255, 0, 255));
	pt.x = position.x;
	pt.y = position.y;
	currentFrameX = 0;
	return S_OK;
}
void	bomb::update()
{

	img->setFrameX(currentFrameX);
	currentFrameX++;
	//if (img->getMaxFrameX() < currentFrameX)
	//	currentFrameX = img->getMaxFrameX();
}
void	bomb::render()
{
	img->frameRender(getMemDC(), pt.x, pt.y, currentFrameX, 0);
}
bool bomb::remove_bomb()
{
	if (img->getMaxFrameX() < currentFrameX)
		return true;
	else
		return false;
}