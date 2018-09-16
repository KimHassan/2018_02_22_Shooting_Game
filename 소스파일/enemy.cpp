#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{

}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;
	boost_frame = 0;
	_rndFireCount = RND->getFromIntTo(1, 500);
	dead = false;
	_imageName = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	boost_image = new image;
	boost_image->init("boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void enemy::release(void)
{

}

void enemy::update(void) 
{
	_count++;
	boost_frame++;
	if (boost_frame > boost_image->getMaxFrameX())
		boost_frame = 0;
	if (_count == 3)
	{
		_count = 0;
		if (_fireCount + _imageName->getMaxFrameX()*3 > _rndFireCount)
			_currentFrameX++;
		else
			_currentFrameX = 0;
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
	}
	/*if ( _count % 2 == 0 )
	{
		if ( _currentFrameX >= _imageName->getMaxFrameX() ) _currentFrameX = 0;
		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}*/

}

void enemy::render(void) 
{
	draw();
}


void enemy::draw(void)
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}


bool enemy::bulletCountFire()
{
	_fireCount++;

	//발사 시점이 되었으면
	if ( _fireCount % _rndFireCount == 0 )
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 500);

		return true;
	}

	return false;
}

void enemy::move(void)
{
	moving++;
	if (move_count <= moving)
	{
		if (move_action_count == 3)
		{
			int create_y = RND->getInt(2);
			POINT pt;
			pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX + 200);
			if (create_y == 0)
				pt.y = -100;
			else
				pt.y = WINSIZEY + 100;
			move_angle = getAngle(_rc.left, _rc.top, pt.x, pt.y);
			move_action_count++;
		}
		if(move_action_count < 3)
			move_angle = getAngle(_rc.left, _rc.top, move_pt.x, move_pt.y);
		
		moving_pt.x += cosf(move_angle) * speed;
		moving_pt.y += -sinf(move_angle) * speed;
		for (int i = 0; i < speed; i++)
		{
			for (int j = 0; j < speed; j++)
			{
				if (moving_pt.x + i == move_pt.x && moving_pt.y + i == move_pt.y)
				{
					if (move_action_count == 4)
					{
						dead = true;
						return;
					}
					else
					{
						move_pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX - 200);
						move_pt.y = RND->getFromIntTo(20, WINSIZEY - 150);
						move_count = RND->getFromIntTo(500, 1000);
						moving = 0;
						move_action_count++;
					}
				}
			}
		}
	}
}
void enemy::get_out()
{
	move_action_count = 3;
}