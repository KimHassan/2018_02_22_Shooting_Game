#include "stdafx.h"
#include "boss.h"


boss::boss()
{
}


boss::~boss()
{

}

HRESULT boss::init()
{
	tpye = action;
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;
	boost_frame = 0;
	_rndFireCount = RND->getFromIntTo(1, 200);
	dead = false;
	_imageName = IMAGEMANAGER->findImage("boss_normal");
	boost_image = new image;
	hp_bar = new image;
	red_bar = new image;
	hp_bar->init("hp_bar.bmp", 380, 58, true, RGB(255, 0, 255));
	red_bar->init("red_bar.bmp", 334, 6, true, RGB(255, 0, 255));
	hp_bar->setX(WINSIZEX - 400);
	hp_bar->setY(10);
	red_bar->setX(WINSIZEX - 365);
	red_bar->setY(37);
	hp_rc = RectMake(red_bar->getX(), red_bar->getY(), red_bar->getWidth(), red_bar->getHeight());
	boost_image->init("boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	move_pt.x =WINSIZEX - 500;
	move_pt.y =WINSIZEY /2;
	moving_pt.x = WINSIZEX;
	moving_pt.y = WINSIZEY/2;
	_imageName->setX(moving_pt.x);
	_imageName->setY(moving_pt.y);
	_rc = RectMakeCenter(moving_pt.x, moving_pt.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	hit_rc = RectMake(_rc.right - 50, _rc.top + 10, 50, _imageName->getFrameHeight() - 10);
	move_count = 0;
	speed = 3;
	moving = 0;
	action = BOSS_NORMAL;
	change = RND->getFromIntTo(500, 1000);
	change_count = 0;
	animation = false;
	_hpBar = new progressBar;
	_currentHP = _maxHP = 100;
	hit_hp = 0;
	_hpBar->init(moving_pt.x, moving_pt.y - 20, 52, 10);
	_hpBar->setGauge(_currentHP, _maxHP);
	dead = false;
	return S_OK;
}
void boss::release(void)	   
{

}
void boss::update(void)		   
{
	_count++;
	boost_frame++;
	change_count++;
	_rc = RectMake(moving_pt.x, moving_pt.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	hit_rc = RectMake(_rc.right - 60, _rc.top + 10, 50, _imageName->getFrameHeight() - 10);
	_imageName->setX(moving_pt.x);
	_imageName->setY(moving_pt.y);
	if (_count == 3)
	{
		_count = 0;
		if (_fireCount + _imageName->getMaxFrameX() * 3 > _rndFireCount)
			_currentFrameX++;
		else
			_currentFrameX = 0;
		if (_currentFrameX >= _imageName->getMaxFrameX())
			if(_fireCount < 30)
				_currentFrameX = _imageName->getMaxFrameX();
			else
				_currentFrameX = 0;
	}
	if (change_count > change)
	{
		action = RND->getInt(3);
				if (action == BOSS_NORMAL)
				{
					int x = _imageName->getX();
					int y = _imageName->getY();
					_imageName = IMAGEMANAGER->findImage("boss_normal");
					_imageName->setX(x);
					_imageName->setY(y);
					change_count = 0;
					change = RND->getFromIntTo(500, 1000);
				}
				else if (action == BOSS_RIFLE)
				{
					
						int x = _imageName->getX();
						int y = _imageName->getY();
						_imageName = IMAGEMANAGER->findImage("boss_rifle");
						_imageName->setX(x);
						_imageName->setY(y);
						change_count = 0;
						change = RND->getFromIntTo(500, 1000);
				
					
				}
				else if (action == BOSS_BLAST)
				{
					int x = _imageName->getX();
					int y = _imageName->getY();
					_imageName = IMAGEMANAGER->findImage("boss_blast");
					_imageName->setX(x);
					_imageName->setY(y);
					change_count = 0;
					change = RND->getFromIntTo(500, 1000);
				}
	}	
	if (boost_frame > boost_image->getMaxFrameX())
		boost_frame = 0;
	switch (action)
	{
	case BOSS_NORMAL:
		_hpBar->setX(_imageName->getX() + 20);
		_hpBar->setY(_imageName->getY() - 20);
		boost_image->setX(_imageName->getX() + boost_image->getFrameWidth() -5);
		boost_image->setY( _imageName->getY() + 20);
		break;
	case BOSS_RIFLE:
		_hpBar->setX(_imageName->getX() + 20);
		_hpBar->setY(_imageName->getY() - 20);
		boost_image->setX(_imageName->getX() + boost_image->getFrameWidth() + 23);
		boost_image->setY(_imageName->getY() + 23);
		break;
	case BOSS_BLAST:
		_hpBar->setX(_imageName->getX() + 20);
		_hpBar->setY(_imageName->getY() - 20);
		boost_image->setX(_imageName->getX() + boost_image->getFrameWidth());
		boost_image->setY(_imageName->getY() + 25);
		break;
	case BOSS_X:
		_hpBar->setX(_imageName->getX() + 20);
		_hpBar->setY(_imageName->getY() - 20);
		boost_image->setX(_imageName->getX() - boost_image->getFrameWidth() -5);
		boost_image->setY(_imageName->getY() + 20);
		break;
	}
	move();
}
void boss::render(void)		   
{
	draw();
}
void boss::move(void)		   
{
	moving++;
	if (move_count <= moving)
	{
		move_angle = getAngle(_rc.left, _rc.top, move_pt.x, move_pt.y);
		moving_pt.x += cosf(move_angle) * speed;
		moving_pt.y += -sinf(move_angle) * speed;
		for (int i = 0; i < speed; i++)
		{
			for (int j = 0; j < speed; j++)
			{
				if (moving_pt.x + i == move_pt.x && moving_pt.y + i == move_pt.y)
				{
			
						move_pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX - 200);
						move_pt.y = RND->getFromIntTo(20, WINSIZEY - 150);
						move_count = RND->getFromIntTo(100, 300);
						moving = 0;
				}
			}
		}
	}
}
void boss::draw(void)		   
{
	boost_image->frameRender(getMemDC(), boost_image->getX(), boost_image->getY(), boost_frame, 0);
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	_hpBar->render();
	hp_bar->render(getMemDC());
	red_bar->render(getMemDC(), red_bar->getX() + hit_hp, red_bar->getY(), 0, 0,red_bar->getWidth() - hit_hp, red_bar->getHeight());
	//Rectangle(getMemDC(), hit_rc.left, hit_rc.top, hit_rc.right, hit_rc.bottom);

}
bool boss::bulletCountFire()   
{
	_fireCount++;

	//발사 시점이 되었으면
	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		if(action == BOSS_NORMAL)
			_rndFireCount = RND->getFromIntTo(1, 50);
		else if(action == BOSS_BLAST)
			_rndFireCount = RND->getFromIntTo(100, 300);
		else if (action == BOSS_RIFLE)
			_rndFireCount = RND->getFromIntTo(50, 150);

		return true;
	}

	return false;
}
void boss::get_out()
{
	
}
void boss::hit()
{
	hit_hp += 3;
	if (hit_hp > red_bar->getWidth())
		dead = true;
}