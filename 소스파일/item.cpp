#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{

}

HRESULT item::init(int max)
{
	item_max = max;
	return S_OK;
}
void item:: update()	   
{
	move();
}
void item::render()	   
{
	for (_viitem = _vitem.begin(); _viitem != _vitem.end(); _viitem++)
	{
		_viitem->img->render(getMemDC(), _viitem->x, _viitem->y);
	}
}
void item::create(float x,float y)	   
{
	if (item_max < _vitem.size()) return;
	ITEM it;
	ZeroMemory(&it, sizeof(ITEM));
	it.x = x;
	it.y = y;
	it.speed = 4;
	it.count = 0;
	it.angle = RND->getFromIntTo(90, 270);
	it.img = new image;
	int ran_num;
	ran_num = RND->getInt(3);
	switch (ran_num)
	{
	case 0:
		it.img->init("normal.bmp", 44, 40, true, RGB(255, 0, 255));
		it.type = 0;
		break;
	case 1:
		it.img->init("sword_item.bmp", 43, 39, true, RGB(255, 0, 255));
		it.type = 1;
		break;
	case 2:
		it.img->init("rifle.bmp", 43, 39, true, RGB(255, 0, 255));
		it.type = 2;
		break;
	}
	it.rc = RectMakeCenter(it.x, it.y, it.img->getWidth(), it.img->getHeight());
	_vitem.push_back(it);
}

void item::move()
{
	for (int i = 0; i < _vitem.size(); i++)
	{
		_vitem[i].count++;
		_vitem[i].x += cosf(_vitem[i].angle) * _vitem[i].speed;
		_vitem[i].y += -sinf(_vitem[i].angle) * _vitem[i].speed;
		_vitem[i].rc = RectMakeCenter(_vitem[i].x, _vitem[i].y, _vitem[i].img->getWidth(), _vitem[i].img->getHeight());
		if (_vitem[i].x < 0)
		{
			_vitem[i].angle = PI - _vitem[i].angle;
		}
		else if (_vitem[i].x+ _vitem[i].img->getWidth() > WINSIZEX)
		{
			_vitem[i].angle = PI*2 - _vitem[i].angle;
		}
		else if (_vitem[i].y < 0)
		{
			_vitem[i].angle = PI - _vitem[i].angle;
		}
		else if (_vitem[i].y + _vitem[i].img->getHeight() > WINSIZEY)
		{
			_vitem[i].angle = PI*2 - _vitem[i].angle;
		}
		if (_vitem[i].count > 1000)
			remove(i);
		
	}
}

void item::remove(int num)
{
	_vitem[num].img->release();
	_vitem.erase(_vitem.begin() + num);
}