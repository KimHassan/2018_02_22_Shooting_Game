#include "stdafx.h"
#include "bullets.h"

bullet::bullet(){}
bullet::~bullet()
{

}

HRESULT bullet::init(const char* imageName, int bulletMax, float range)
{

	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release(void)
{

}

void bullet::update(void) 
{
	move();
}

void bullet::render(void) 
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet )
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}


void bullet::fire(float x, float y, float angle, float speed)
{
	if ( _bulletMax < _vBullet.size() ) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	_vBullet.push_back(bullet);

}


void bullet::move(void)
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if ( _range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY) )
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}


missile::missile(){}
missile::~missile(){}

HRESULT missile::init(int bulletMax, float range)
{
	_range = range;

	for ( int i = 0; i < bulletMax; i++ )
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile1.bmp", 26, 124, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.isFire = false;

		//벡터에 값을 담을땐 푸쉬백
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release(void)
{

}

void missile::update(void) 
{
	move();
}

void missile::render(void) 
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet )
	{
		if ( !_viBullet->isFire ) continue;

		_viBullet->bulletImage->render(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top,
			0, 0,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}
}


void missile::fire(float x, float y)
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet )
	{
		if ( _viBullet->isFire ) continue;

		_viBullet->isFire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		break;
	}
}


void missile::move(void)
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet )
	{
		if ( !_viBullet->isFire ) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//사거리 밖으로 나가면 없애라
		if ( _range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) )
		{
			_viBullet->isFire = false;
		}
	}
}



yankeeGoHome::yankeeGoHome(){}
yankeeGoHome::~yankeeGoHome(){}

HRESULT yankeeGoHome::init(int missileMax, float range)
{
	_bulletMax = missileMax;
	_range = range;

	return S_OK;
}

void yankeeGoHome::release(void)
{
	
}

void yankeeGoHome::update(void)
{
	move();
}

void yankeeGoHome::render(void)
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet )
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if ( _viBullet->count % 5 == 0 )
		{
			_viBullet->bulletImage->setFrameY(_viBullet->bulletImage->getFrameY() + 1);

			if ( _viBullet->bulletImage->getFrameY() >= _viBullet->bulletImage->getMaxFrameY() )
			{
				_viBullet->bulletImage->setFrameY(0);
			}

			_viBullet->count = 0;
		}
	}
}


void yankeeGoHome::fire(float x, float y)
{
	//총알 최대갯수보다 더 만들려고 한다면
	if ( _bulletMax < _vBullet.size() ) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 0, 0, 64, 416, 1, 13, true, RGB(255, 0, 255));
	bullet.speed		= 6.0f;
	bullet.x			= bullet.fireX = x;
	bullet.y			= bullet.fireY = y;
	bullet.rc			 = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);
}


void yankeeGoHome::move()
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if ( _range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY) )
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
		
	}
}

void yankeeGoHome::removeYankee(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}
