#include "stdafx.h"
#include "sword_bullet.h"


sword_bullet::sword_bullet()
{
}


sword_bullet::~sword_bullet()
{
}

HRESULT sword_bullet::init(int missileMax, float range)
{
	_bulletMax = missileMax;
	_range = range;

	return S_OK;
}
void sword_bullet::fire(float x,float y,int power)
{
	if (_bulletMax < _vBullet.size())
	return;
	for (int i = 0; i < power; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("sword_bullet.bmp", 126, 78, 3, 1, true, RGB(255, 0, 255));
		bullet.speed = 6.0f;
		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		if (i == 0)
			bullet.angle = 0;
		if (i == 1)
			bullet.angle = PI / 18;
		if (i == 2)
			bullet.angle = -PI / 18;

		bullet.rc = RectMake(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());
		_vBullet.push_back(bullet);
	}
}
void sword_bullet::render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}
void sword_bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) *_viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) *_viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void sword_bullet::update(void)
{
	move();
}

void sword_bullet::removeSW(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}