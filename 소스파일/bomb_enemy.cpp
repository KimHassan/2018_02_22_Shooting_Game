#include "stdafx.h"
#include "bomb_enemy.h"


bomb_enemy::bomb_enemy()
{
}


bomb_enemy::~bomb_enemy()
{
}

HRESULT bomb_enemy::init(POINT position)
{
	tpye = 3;
	dead = false;
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;
	boost_frame = 0;
	_rndFireCount = RND->getFromIntTo(1, 500);
	_imageName = IMAGEMANAGER->findImage("bomb_enemy");
	_imageName->setX(position.x);
	_imageName->setY(position.y);
	_rc = RectMake(position.x, position.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	hit_rc = RectMake(_rc.right - 50, _rc.top + 10, 50, _imageName->getFrameHeight() - 10);
	boost_image = new image;
	boost_image->init("boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	move_count =0;
	move_pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX - 100);
	move_pt.y = RND->getFromIntTo(20, WINSIZEY - 150);
	moving_pt.x = position.x;
	moving_pt.y = position.y;
	speed = 3;
	moving = 0;
	move_action_count = 0;
	return S_OK;
}
void bomb_enemy::release(void)
{

}
void bomb_enemy::update(void)
{
	_count++;
	boost_frame++;
	_rc = RectMake(moving_pt.x, moving_pt.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	hit_rc = RectMake(_rc.right - 50, _rc.top + 10, 50, _imageName->getFrameHeight() - 10);
	if (boost_frame > boost_image->getMaxFrameX())
		boost_frame = 0;
	if (_count == 3)
	{
		_count = 0;
		if (_fireCount + _imageName->getMaxFrameX() * 3 > _rndFireCount)
			_currentFrameX++;
		else
			_currentFrameX = 0;
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
	}
	move();
}
void bomb_enemy::render(void)
{
	draw();
}

void bomb_enemy::draw(void)	 
{
	boost_image->frameRender(getMemDC(), _rc.right - 30, _rc.top + 25, boost_frame, 0);
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	//Rectangle(getMemDC(), hit_rc.left, hit_rc.top, hit_rc.right, hit_rc.bottom);
}
bool bomb_enemy::bulletCountFire()
{
	return true;
}
//bool bomb_enemy::bulletCountFire()
//{
//	_fireCount++;
//
//	//발사 시점이 되었으면
//	if (_fireCount > _rndFireCount)
//	{
//		_fireCount = 0;
//		_rndFireCount = RND->getFromIntTo(1, 500);
//
//		return true;
//	}
//
//	return false;
//}