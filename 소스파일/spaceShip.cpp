#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"

spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{

}

HRESULT spaceShip::init()
{
	boost = IMAGEMANAGER->addFrameImage("player_boost", "player_boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	_ship = IMAGEMANAGER->addFrameImage("player", "player.bmp", 228, 75, 3, 1, true, RGB(255, 0, 255));
	_ship->setX(-100);
	_ship->setY(WINSIZEY / 2);
	_ship->setFrameX(0);
	rc = RectMakeCenter(_ship->getCenterX(), _ship->getCenterY(), 30, 30);
	_sw = new sword_bullet;
	_sw->init(50, 300);
	_nb = new normal_bullet;
	_nb->init(50, 500);
	_rb = new rifle_bullet;
	_rb->init(50, WINSIZEX);
	//현재체력과 최대체력은 100으로
	_currentHP = _maxHP = 100;
	bool frame_Moving;
	//프로그레스 바 할당 후 위치 셋팅
	_hpBar = new progressBar;
	_hpBar->init(_ship->getX(), _ship->getY() - 20, 52, 10);
	_hpBar->setGauge(_currentHP, _maxHP);
	count = 0;
	action = NORMAL;
	shot_delay = 0;
	rifle_charge = 0;
	sword_power = 1;
	normal_power = 1;
	dead = false;
	gameClear = false;
	start = false;
	return S_OK;
}

void spaceShip::release()
{
	SAFE_DELETE(_missile);
	SAFE_DELETE(_ygh);
	SAFE_DELETE(_nb);
	SAFE_DELETE(_sw);
	SAFE_DELETE(_rb);
}

void spaceShip::update() 
{
	rc = RectMakeCenter(_ship->getCenterX(), _ship->getCenterY(), 30, 30);
	count++;
	shot_delay++;
	if (count % 3 == 0)
	{
		boost_frame++;
		if (boost_frame > boost->getMaxFrameX())
			boost_frame = 0;
	}
	if (!start)
	{
		_ship->setX(_ship->getX() + 6);
		if (_ship->getX() > 100)
			start = true;
	}
	else
	{
		switch (action)
		{
		case MOVE:
			_ship->setFrameX(0);
			_hpBar->setX(_ship->getX() + 20);
			_hpBar->setY(_ship->getY() - 20);
			boost_x = _ship->getX() - boost->getFrameWidth() + 30;
			boost_y = _ship->getY() + 20;
			break;
		case NORMAL:
			_ship->setFrameX(0);
			_hpBar->setX(_ship->getX() + 20);
			_hpBar->setY(_ship->getY() - 20);
			boost_x = _ship->getX() - boost->getFrameWidth() + 30;
			boost_y = _ship->getY() + 20;
			break;
		case SWORD:
			_em->Shield_guard();
			shield = RectMake(0, 0, 0, 0);
			_ship->setFrameX(19);
			_hpBar->setX(_ship->getX() + 50);
			_hpBar->setY(_ship->getY() - 15);
			boost_x = _ship->getX() + 20;
			boost_y = _ship->getY() + 25;
			break;
		case RIFLE:
			_ship->setFrameX(9);
			_hpBar->setX(_ship->getX() + 20);
			_hpBar->setY(_ship->getY() + 20);
			boost_x = _ship->getX() - boost->getFrameWidth() + 38;
			boost_y = _ship->getY() + 65;
			break;
		}
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			int x = _ship->getX();
			int y = _ship->getY();
			_ship = IMAGEMANAGER->findImage("player_normal");
			_ship->setX(x);
			_ship->setY(y);
			action = NORMAL;
		}
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			int x = _ship->getX();
			int y = _ship->getY();
			_ship = IMAGEMANAGER->findImage("player_sword");
			_ship->setX(x);
			_ship->setY(y);
			action = SWORD;
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			int x = _ship->getX();
			int y = _ship->getY();
			_ship = IMAGEMANAGER->findImage("player_x");
			_ship->setX(x);
			_ship->setY(y);
			action = RIFLE;
		}
		if (!dead)
		{
			if (KEYMANAGER->isStayKeyDown('C') && action != RIFLE)
			{

				if (action == NORMAL)
				{
					if (shot_delay > 15)
					{
						shot_delay = 0;
						_nb->fire(_ship->getX() + _ship->getFrameWidth() + 5, _ship->getCenterY(), normal_power);
					}
					if (count > 5)
						count = 2;
				}
				else if (action == SWORD)
				{
					if (shot_delay > 15)
					{
						shot_delay = 0;
						_sw->fire(_ship->getX() + _ship->getFrameWidth() + 5, _ship->getCenterY(), sword_power);
					}
					if (count > 20)
						count = 0;
				}
				shield = RectMake(_ship->getX() + _ship->getFrameWidth(), _ship->getY(), 20, _ship->getFrameHeight());
				_ship->setFrameX(count++);
				//	_ygh->fire(_ship->getX() + _ship->getFrameWidth() + 5, _ship->getCenterY());
			}
			if (KEYMANAGER->isStayKeyDown('C') && action == RIFLE)
			{
				if (count > 28)
					count = 28;
				_ship->setFrameX(count++);
				if (_rb->getVBullet().empty())
				{
					rifle_charge++;
					if (rifle_charge > 80 && count > 28)
						_ship->setFrameX(29);
					else if (rifle_charge > 40 && count > 28)
						_ship->setFrameX(30);
				}

			}
			if (KEYMANAGER->isOnceKeyUp('C') && action == RIFLE)
			{
				int height = 20;
				if (_rb->getVBullet().empty())
				{
					if (rifle_charge > 80)
						height = 40;
					else if (rifle_charge > 40)
						height = 30;
					_rb->fire(_ship->getX() + _ship->getFrameWidth(), _ship->getY() + 40, height);
					rifle_charge = 0;
					count = 0;
				}
			}
			if (!_rb->getVBullet().empty())
			{
				_ship->setFrameX(30);
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && rc.left > 0)
			{
				if (action == MOVE)
					_ship->setFrameX(1);
				_ship->setX(_ship->getX() - 5);
			}

			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && rc.right < WINSIZEX)
			{
				if (action == MOVE)
					_ship->setFrameX(0);
				_ship->setX(_ship->getX() + 5);
			}
			if (KEYMANAGER->isStayKeyDown(VK_UP) && rc.top > 0)
			{
				if (action == MOVE)
					_ship->setFrameX(1);
				_ship->setY(_ship->getY() - 5);
			}

			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && rc.bottom < WINSIZEY)
			{
				if (action == MOVE)
					_ship->setFrameX(2);
				_ship->setY(_ship->getY() + 5);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) _missile->fire(_ship->getX() + _ship->getFrameWidth() + 5, _ship->getCenterY());

			if (KEYMANAGER->isOnceKeyDown(VK_F11))
			{
				char temp[128];
				vector<string> vStr;

				vStr.push_back(itoa(_currentHP, temp, 10));
				vStr.push_back(itoa(_maxHP, temp, 10));
				vStr.push_back(itoa(_ship->getX(), temp, 10));
				vStr.push_back(itoa(_ship->getY(), temp, 10));

				TXTDATA->txtSave("세이부.txt", vStr);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_F12))
			{
				vector<string> vStr;

				vStr = TXTDATA->txtLoad("세이부.txt");

				_currentHP = (atoi(vStr[0].c_str()));
				_maxHP = (atoi(vStr[1].c_str()));
				_ship->setX(atof(vStr[2].c_str()));
				_ship->setY(atof(vStr[3].c_str()));

			}
			_hpBar->setGauge(_currentHP, _maxHP);
			_hpBar->update();
		}

		collision();
		_sw->update();
		_nb->update();
		_rb->update(_ship->getX() + _ship->getFrameWidth(), _ship->getY() + 40);
		if (_em->getBoss() && !gameClear)
			boss_collision();
		//for (_vibomb = _vbomb.begin(); _vibomb != _vbomb.end(); _vibomb++)
		//{
		//	(*_vibomb)->update();
		//}
		for (int i = 0; i < _vbomb.size(); i++)
		{
			_vbomb[i]->update();
			if (_vbomb[i]->remove_bomb())
			{
				SAFE_DELETE(_vbomb[i]);
				_vbomb.erase(_vbomb.begin() + i);
			}
		}
	}
}

void spaceShip::render() 
{
	if (!dead)
	{
		boost->frameRender(getMemDC(), boost_x, boost_y, boost_frame, 0);
		_ship->frameRender(getMemDC(), _ship->getX(), _ship->getY());
		_hpBar->render();
	}
	for (_vibomb = _vbomb.begin(); _vibomb != _vbomb.end(); _vibomb++)
	{
		(*_vibomb)->render();
	}
	_sw->render();
	_nb->render();
	_rb->render();
	//Rectangle(getMemDC(),shield.left, shield.top, shield.right, shield.bottom);
}

void spaceShip::collision(void)
{
	for (int i = 0; i < _em->getITEM()->getVitem().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_em->getITEM()->getVitem()[i].rc, &rc))
		{
			if (_em->getITEM()->getVitem()[i].type ==0)
			{
				if (action == NORMAL)
				{
					normal_power++;
					if (normal_power > 3)
						normal_power = 3;
				}
				else
				{
					int x = _ship->getX();
					int y = _ship->getY();
					_ship = IMAGEMANAGER->findImage("player_normal");
					_ship->setX(x);
					_ship->setY(y);
					action = NORMAL;
				}
			}
			else if (_em->getITEM()->getVitem()[i].type == 1)
			{
				if (action == SWORD)
				{
					sword_power++;
					if (sword_power > 3)
						sword_power = 3;
				}
				else
				{
					int x = _ship->getX();
					int y = _ship->getY();
					_ship = IMAGEMANAGER->findImage("player_sword");
					_ship->setX(x);
					_ship->setY(y);
					action = SWORD;
				}
			}
			else if (_em->getITEM()->getVitem()[i].type == 2)
			{
				int x = _ship->getX();
				int y = _ship->getY();
				_ship = IMAGEMANAGER->findImage("player_x");
				_ship->setX(x);
				_ship->setY(y);
				action = RIFLE;
			}
			_em->getITEM()->remove(i);
		}
	

	}
	for (int j = 0; j < _em->getVMinion().size(); ++j)
	{
		for(int i = 0; i < _nb->getVBullet().size(); ++i) // 발칸
		{

			RECT temp;
		
				if (IntersectRect(&temp, &_nb->getVBullet()[i].rc, &_em->getVMinion()[j]->gethitRect()))
				{
					bomb *new_bomb = new bomb;
					//new_bomb->init(PointMake(450, 450));
					new_bomb->init(PointMake(_em->getVMinion()[j]->gethitRect().left, _em->getVMinion()[j]->gethitRect().top));
					_vbomb.push_back(new_bomb);
					int num = RND->getInt(4);
					if (num == 0)
						_em->getITEM()->create(_em->getVMinion()[j]->gethitRect().left, _em->getVMinion()[j]->gethitRect().top);
					_nb->remove_NormalBullet(i);
					_em->removeMinion(j);
					break;
				}
			
			
		}
		for (int i = 0; i < _sw->getVBullet().size(); ++i) // 소드
		{

			RECT temp;
				if (IntersectRect(&temp, &_sw->getVBullet()[i].rc, &_em->getVMinion()[j]->gethitRect()))
				{
					bomb *new_bomb = new bomb;
					new_bomb->init(PointMake(_em->getVMinion()[j]->gethitRect().left, _em->getVMinion()[j]->gethitRect().top));
					_vbomb.push_back(new_bomb);
					int num = RND->getInt(4);
					if (num == 0)
						_em->getITEM()->create(_em->getVMinion()[j]->gethitRect().left, _em->getVMinion()[j]->gethitRect().top);
					_sw->removeSW(i);
					_em->removeMinion(j);
					break;
				}
			
		}
		for (int i = 0; i < _rb->getVBullet().size(); ++i) //라이플
		{
		
			RECT temp;
			if (IntersectRect(&temp, &_rb->getVBullet()[i].rc, &_em->getVMinion()[j]->gethitRect()))
			{
				bomb *new_bomb = new bomb;
				new_bomb->init(PointMake(_em->getVMinion()[j]->gethitRect().left, _em->getVMinion()[j]->gethitRect().top));
				_vbomb.push_back(new_bomb);
				int num = RND->getInt(4);
				if (num == 0)
					_em->getITEM()->create(_em->getVMinion()[j]->gethitRect().left, _em->getVMinion()[j]->gethitRect().top);
				_em->removeMinion(j);
			}
			
		}
	}

}

void spaceShip::hitDamage(float damage)
{
	_currentHP -= damage;
	if (_currentHP < 0 && !dead)
	{
		
		dead = true;
		bomb *new_bomb = new bomb;
		new_bomb->init(PointMake(rc.left, rc.top));
		_vbomb.push_back(new_bomb);
	}
}

void spaceShip::powerDELETE()
{
	sword_power --;
	normal_power --;
	if (sword_power < 1)
		sword_power = 1;
	if (normal_power < 1)
		normal_power = 1;
}

void spaceShip::boss_collision()
{
	if (_em->getBossDEAD() && !gameClear)
	{
		bomb *new_bomb = new bomb;
		new_bomb->init(PointMake(_em->getBossRECT().left,_em->getBossRECT().top));
		_vbomb.push_back(new_bomb);
		gameClear = true;
	}
		for (int i = 0; i < _nb->getVBullet().size(); ++i) // 발칸
		{

			RECT temp;
			if (_em->getBoss())
			{

				if (IntersectRect(&temp, &_em->getBossRECT(), &_nb->getVBullet()[i].rc))
				{
					_nb->remove_NormalBullet(i);
					_em->getBossHIT();
					break;
				}
			}

		}
		for (int i = 0; i < _sw->getVBullet().size(); ++i) // 소드
		{

			RECT temp;
			if (_em->getBoss())
			{
				if (IntersectRect(&temp, &_em->getBossRECT(), &_sw->getVBullet()[i].rc))
				{

					_sw->removeSW(i);
					_em->getBossHIT();
					break;
				}
			}

		}
		for (int i = 0; i < _rb->getVBullet().size(); ++i) //라이플
		{
			RECT temp;
			if (_em->getBoss())
			{
				if (IntersectRect(&temp, &_em->getBossRECT(), &_rb->getVBullet()[i].rc))
				{
					_em->getBossHIT();
				}
			}
		}
}