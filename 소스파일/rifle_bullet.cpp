#include "stdafx.h"
#include "rifle_bullet.h"


rifle_bullet::rifle_bullet()
{
}


rifle_bullet::~rifle_bullet()
{

}

HRESULT rifle_bullet::init(int missileMax, float range)	 
{
	_range = range;
	_bulletMax = missileMax;
	frame = 0;
	count = 0;
	return S_OK;
}
void rifle_bullet::release(void)						 
{

}
void rifle_bullet::update(float x,float y)							 
{
	move(x, y);
}
void rifle_bullet::render(void)							 
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->x, _viBullet->y + 12 +  20 -_viBullet->height / 2, 0, 0, _viBullet->rc.right - _viBullet->rc.left, _viBullet->rc.bottom - _viBullet->rc.top);
		//_viBullet->bulletImage->render(
		_viBullet->blast->frameRender(getMemDC(),
			_viBullet->x - 10,
			_viBullet->y - 10,
			frame, 0);
			_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			frame++;
			if (frame > _viBullet->blast->getMaxFrameX())
				frame = 0;
			_viBullet->count = 0;
		}
		//Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
	}
}
void rifle_bullet::fire(float x, float y, float height)				 
{
	if (_vBullet.size() > _bulletMax)
		return;
	BLAST bullet;
	ZeroMemory(&bullet, sizeof(BLAST));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("blast2.bmp", 1000, 40, true, RGB(255, 0, 255));
	bullet.blast = new image;
	bullet.blast->init("blast_flame.bmp", 297, 85, 3, 1, true, RGB(255, 0, 255));
	bullet.speed = 10;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.height = height;
	bullet.rc = RectMake(bullet.x, bullet.y +12,50,height);
	_vBullet.push_back(bullet);

}
void rifle_bullet::move(float x, float y)								 
{

	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x = x;
		_vBullet[i].y = y;
		_vBullet[i].rc.left = x;
		_vBullet[i].rc.top = _vBullet[i].y + 12 + 20 - _vBullet[i].height / 2;
		_vBullet[i].rc.right += _vBullet[i].speed;
		//count++;
		if (_vBullet[i].rc.right > WINSIZEX - 20)
		{
			count++;
			_vBullet[i].rc.top += + 5*count;
			_vBullet[i].rc.bottom -= 5 * count;
			if (_vBullet[i].rc.top > _vBullet[i].rc.bottom)
				remove_rifle(i);
			break;
		}

		else
		{
			count = 0;
			_vBullet[i].rc.bottom = _vBullet[i].rc.top + _vBullet[i].height;
		}
	}
}
void rifle_bullet::remove_rifle(int arrNum)				 
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet[arrNum].blast->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}
