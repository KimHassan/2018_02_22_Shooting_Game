#include "stdafx.h"
#include "enemy_rifle.h"


enemy_rifle::enemy_rifle()
{
}


enemy_rifle::~enemy_rifle()
{

}

HRESULT enemy_rifle::init(int missileMax, float range)		
{
	_range = range;
	_bulletMax = missileMax;
	count = 0;
	return S_OK;
}
void enemy_rifle::release(void)								
{

}
void enemy_rifle::update()					
{
	move();
}
void enemy_rifle::render(void)							
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->x, _viBullet->y + 12, 0, 0, _viBullet->rc.right - _viBullet->rc.left, _viBullet->rc.bottom - _viBullet->rc.top);
		//_viBullet->bulletImage->render(
		//Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
	}
}
void enemy_rifle::fire(float x, float y)		
{
	if (_vBullet.size() > _bulletMax)
		return;
	BLASTER bullet;
	ZeroMemory(&bullet, sizeof(BLASTER));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("blast2.bmp", 1000, 40, true, RGB(255, 0, 255));
	bullet.speed = 20;
	bullet.x= x;
	bullet.y= y;
	bullet.rc = RectMake(bullet.x - 50, bullet.y + 12, 50,40);
	_vBullet.push_back(bullet);
	bullet.count = 0;
}
void enemy_rifle::move()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x -= _vBullet[i].speed;
		_vBullet[i].rc.left = _vBullet[i].x;
		_vBullet[i].rc.top = _vBullet[i].y + 12;
		_vBullet[i].rc.left -= _vBullet[i].speed;
		if (_vBullet[i].rc.left < 20)
		{
			_vBullet[i].count++;
			_vBullet[i].rc.top += +5 * _vBullet[i].count;
			_vBullet[i].rc.bottom -= 5 * _vBullet[i].count;
			if (_vBullet[i].rc.top > _vBullet[i].rc.bottom)
				remove_rifle(i);
		}
	}
}
void enemy_rifle::remove_rifle(int arrNum)					
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}