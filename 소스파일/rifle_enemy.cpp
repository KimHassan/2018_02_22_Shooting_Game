#include "stdafx.h"
#include "rifle_enemy.h"


rifle_enemy::rifle_enemy()
{
}


rifle_enemy::~rifle_enemy()
{
}

HRESULT rifle_enemy::init(POINT position)
{
	type = 2;
	dead = false;
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;
	boost_frame = 0;
	_rndFireCount = RND->getFromIntTo(300, 600);
	_imageName = IMAGEMANAGER->findImage("rifle_enemy");
	_imageName->setX(position.x);
	_imageName->setY(position.y);
	_rc = RectMake(position.x, position.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	hit_rc = RectMake(_rc.right - 50, _rc.top + 10, 50, _imageName->getFrameHeight() - 10);
	boost_image = new image;
	boost_image->init("boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	//무빙을 위한 재료
	move_count = 0;
	move_pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX - 100);
	move_pt.y = RND->getFromIntTo(20, WINSIZEY - 150);
	moving_pt.x = position.x;
	moving_pt.y = position.y;
	speed = 3;
	moving = 0;
	move_action_count = 0;
	return S_OK;
}
void rifle_enemy::release(void)
{

}
void rifle_enemy::update(void)
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
void rifle_enemy::render(void)
{
	draw();
}
//void rifle_enemy::move(void)
//{
//	moving++;
//	if (move_count <= moving)
//	{
//		move_angle = getAngle(_rc.left, _rc.top, move_pt.x, move_pt.y);
//		moving_pt.x += cosf(move_angle) * speed;
//		moving_pt.y += -sinf(move_angle) * speed;
//		for (int i = 0; i < speed; i++)
//		{
//			for (int j = 0; j < speed; j++)
//			{
//				if (moving_pt.x + i == move_pt.x && moving_pt.y + i == move_pt.y)
//				{
//					move_pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX - 200);
//					move_pt.y = RND->getFromIntTo(20, WINSIZEY - 150);
//					move_count = RND->getFromIntTo(500, 1000);
//					moving = 0;
//					move_count++;
//				}
//			}
//		}
//	}
//}
void rifle_enemy::draw(void)
{
	boost_image->frameRender(getMemDC(), _rc.right - 30, _rc.top + 25, boost_frame, 0);
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	//Rectangle(getMemDC(), hit_rc.left, hit_rc.top, hit_rc.right, hit_rc.bottom);
}