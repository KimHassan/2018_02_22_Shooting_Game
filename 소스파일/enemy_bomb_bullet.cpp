#include "stdafx.h"
#include "enemy_bomb_bullet.h"


enemy_bomb_bullet::enemy_bomb_bullet()
{
}


enemy_bomb_bullet::~enemy_bomb_bullet()
{

}

HRESULT enemy_bomb_bullet:: init(int bulletMax)
{
	_bulletMax = bulletMax;
	return S_OK;
}
void enemy_bomb_bullet::release(void)										  
{

}
void enemy_bomb_bullet::update(void)										  
{
	explode();
	move();
}
void enemy_bomb_bullet::render(void)										  
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}
void enemy_bomb_bullet::explode()											  
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (getDistance(_vBullet[i].fireX, _vBullet[i].fireY, _vBullet[i].x, _vBullet[i].y) > _vBullet[i].range && !_vBullet[i].explode)
		{
			int x = _vBullet[i].x;
			int y = _vBullet[i].y;
			int max = RND->getFromIntTo(100, 200);
			for (int j = 0; j < 6; j++)
			{
				tagBullet bullet;
				ZeroMemory(&bullet, sizeof(tagBullet));
				bullet.x = bullet.fireX = x;
				bullet.y = bullet.fireY = y;
				bullet.range= 200;
				bullet.speed = 6;
				bullet.bulletImage = new image;
				bullet.explode = true;
				bullet.count = 0;
				bullet.max_count = max;
				bullet.power = 1;
				bullet.bulletImage->init("bullet.bmp", 21, 21, true, RGB(255, 0, 255));
				bullet.angle = j * (PI2 / 6);
				_vBullet.push_back(bullet);
			}
			removeBullet(i);
		}
	}

}
void enemy_bomb_bullet::fire(float x, float y)	  
{
	if (_bulletMax < _vBullet.size())
		return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.range = RND->getFromIntTo(200, 600);
	bullet.bulletImage = new image;
	bullet.bulletImage->init("bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	bullet.angle = PI;
	bullet.speed = 6.0f;
	bullet.count = 0;
	bullet.power = 1;
	bullet.explode = false;
	_vBullet.push_back(bullet);

}
void enemy_bomb_bullet::move(void)											  
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].count++;
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getWidth(),
			_vBullet[i].bulletImage->getHeight());
		//if (_vBullet[i].x < 0 || _vBullet[i].x > WINSIZEX || _vBullet[i].y < 0 || _vBullet[i].y > WINSIZEY)
		//{
		//	removeBullet(i);
		//}
		if (_vBullet[i].count>_vBullet[i].max_count && _vBullet[i].explode)
		{
			removeBullet(i);
		}
	}
	//for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	_viBullet->x = cosf(_viBullet->angle) * _viBullet->speed;
	//	_viBullet->y = -sinf(_viBullet->angle) * _viBullet->speed;
	//	_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
	//		_viBullet->bulletImage->getWidth(),
	//		_viBullet->bulletImage->getHeight());
	//	if (getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) > _viBullet->range && _viBullet->explode)
	//	{
	//		_viBullet->bulletImage->release();
	//		_viBullet = _vBullet.erase(_viBullet);
	//	}
	//}
}
void enemy_bomb_bullet::removeBullet(int arrNum)							  
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}