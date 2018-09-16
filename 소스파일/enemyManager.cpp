#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 100, 1000);
	em_rf = new enemy_rifle;
	em_rf->init(30, WINSIZEX);
	_it = new item;
	_it->init(100);
	bomb_bullet = new enemy_bomb_bullet;
	bomb_bullet->init(100);
	boss_count = 0;
	isBoss = false;
	b = new boss;
	gameClear = false;
	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	boss_count++;
	if (boss_count == 5001)
	{
		isBoss = true;
		//boss *b;
		//b = new boss;
		b->init();
		//_vMinion.push_back(b);
	}
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if (boss_count == 5000)
		{
			(*_viMinion)->get_out();
		}
		(*_viMinion)->update();
	}
	//for (int i = 0; i < _vbomb.size(); i++)
	//{
	//	_vbomb[i]->update();
	//	if (_vbomb[i]->remove_bomb())
	//	{
	//		SAFE_DELETE(_vbomb[i]);
	//		_vbomb.erase(_vbomb.begin() + i);
	//	}
	//}

	collision();
	minionBulletFire();
	em_rf->update();
	_bullet->update();
	_it->update();
	bomb_bullet->update();
	out_enemy();
	if (isBoss && !gameClear)
	{
		if (b->getDEAD())
			gameClear = true;
		b->update();
		BossFire();
	}
}

void enemyManager::render()	
{
	for ( _viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion )
	{
		(*_viMinion)->render();
	}

	_bullet->render();
	em_rf->render();
	_it->render();
	bomb_bullet->render();
	if (isBoss && !gameClear)
		b->render();
}

//미니언 셋팅 함수
void enemyManager::setMinion(void)
{
	int max = RND->getFromIntTo(3, 7);
	for (int j = 0; j < max; j++)
	{
		int num = RND->getInt(3);
		int create_y = RND->getInt(2);
		POINT pt;
		pt.x = RND->getFromIntTo(WINSIZEX / 2, WINSIZEX + 200);
		if (create_y == 0)
			pt.y = -100;
		else
			pt.y = WINSIZEY + 100;
		switch (num)
		{
		case 0:
			normal_enemy* NORMAL_ENEMY;
			NORMAL_ENEMY = new normal_enemy;
			NORMAL_ENEMY->init(pt);
			_vMinion.push_back(NORMAL_ENEMY);
			break;
		case 1:
			rifle_enemy* RIFLE_ENEMY;
			RIFLE_ENEMY = new rifle_enemy;
			RIFLE_ENEMY->init(pt);
			_vMinion.push_back(RIFLE_ENEMY);
			break;
		case 2:
			bomb_enemy* BOMB_ENEMY;
			BOMB_ENEMY = new bomb_enemy;
			BOMB_ENEMY->init(pt);
			_vMinion.push_back(BOMB_ENEMY);
			break;
		}

	}
}


void enemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion )
	{
		if ( (*_viMinion)->bulletCountFire() )
		{
			RECT rc = (*_viMinion)->gethitRect();
			if ((*_viMinion)->getTPYE() == 2)
			{
				em_rf->fire(rc.left - 50,rc.top);
			}
			else if ((*_viMinion)->getTPYE() == 0)
			{
				bomb_bullet->fire(rc.left - 20, rc.top+ 20);
			}
			else
			{
				_bullet->fire(rc.left - 70,
					rc.top + (rc.bottom - rc.top) / 2,
					getAngle(rc.left + (rc.right - rc.left) / 2,
						rc.top + (rc.bottom - rc.top) / 2,
						_ship->getShipImage()->getCenterX(),
						_ship->getShipImage()->getCenterY()),
					7.0f);
			}


		}
	}
}

void enemyManager::collision()
{
	for ( int i = 0; i < _bullet->getVBullet().size(); ++i )
	{
		RECT temp;
		if ( IntersectRect(&temp, &_bullet->getVBullet()[i].rc,&_ship->getRECT() ))
		{
			_ship->hitDamage(10.0f);
			_ship->powerDELETE();
			_bullet->removeBullet(i);
			break;
		}
	}
	for (int i = 0; i < em_rf->getVBullet().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &em_rf->getVBullet()[i].rc, &_ship->getRECT()))
		{
			_ship->hitDamage(1.5);
			_ship->powerDELETE();
			break;
		}
	}
	for (int i = 0; i < bomb_bullet->getVBullet().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &bomb_bullet->getVBullet()[i].rc, &_ship->getRECT()))
		{
			_ship->hitDamage(10);
			bomb_bullet->removeBullet(i);
			_ship->powerDELETE();
			break;
		}
	}

}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::out_enemy()
{
	for (int j = 0; j < _vMinion.size(); ++j)
	{
		if ((_vMinion[j]->gethitRect().bottom < 0 || _vMinion[j]->gethitRect().top > WINSIZEY || _vMinion[j]->gethitRect().left > WINSIZEX) && _vMinion[j]->getMove_count() > 3)
		{
			removeMinion(j);
			break;
		}
		if (_vMinion[j]->getDEAD())
		{
			removeMinion(j);
		
		}
	}
}

bool enemyManager::ALLDEAD()
{
	if (_vMinion.empty())
		return true;
	else
		return false;

}

void enemyManager::Shield_guard()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_ship->getSheild(), &_bullet->getVBullet()[i].rc))
		{
			_bullet->removeBullet(i);
		}
	}
	for (int i = 0; i < bomb_bullet->getVBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_ship->getSheild(), &bomb_bullet->getVBullet()[i].rc))
		{
			bomb_bullet->removeBullet(i);
		}
	}
}

void enemyManager::BossFire(void)
{
		if (b->bulletCountFire())
		{
			RECT rc = b->gethitRect();
			if (b->getACTION() == 2)
			{
				em_rf->fire(rc.left - 50, rc.top);
			}
			else if (b->getACTION() == 0)
			{
				bomb_bullet->fire(rc.left - 20, rc.top + 20);
			}
			else if(b->getACTION() == 1)
			{
				_bullet->fire(rc.left - 70,
					rc.top + (rc.bottom - rc.top) / 2,
					getAngle(rc.left + (rc.right - rc.left) / 2,
						rc.top + (rc.bottom - rc.top) / 2,
						_ship->getShipImage()->getCenterX(),
						_ship->getShipImage()->getCenterY()),
					7.0f);
			}
		}
}