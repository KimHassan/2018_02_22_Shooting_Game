#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addImage("긴배경", "background.bmp", 19200, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Tallgeese", "tallgeese.bmp", 520, 78, 5, 1, true, RGB(255, 0, 255));
	//player
	IMAGEMANAGER->addFrameImage("player", "player.bmp", 228, 75, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_sword", "player_sword2.bmp", 3220, 89, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_normal", "player_normal.bmp", 516, 69, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_x", "player_x.bmp", 5440, 133, 32, 1, true, RGB(255, 0, 255));
	// new enemy
	IMAGEMANAGER->addFrameImage("rifle_enemy", "Vorlent.bmp", 2156, 99, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bomb_enemy", "Grimekaiser.bmp", 1027, 72, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("normal_enemy", "EVA.bmp", 3484, 92, 26, 1, true, RGB(255, 0, 255));
	//boost
	IMAGEMANAGER->addFrameImage("player_boost", "player_boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boost", "boost.bmp", 256, 42, 4, 1, true, RGB(255, 0, 255));
	//boss
	IMAGEMANAGER->addFrameImage("boss_normal", "boss_normal.bmp", 540, 66, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_sword_ready", "boss_normal_ready.bmp", 1611, 85, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_sword", "boss_sword.bmp", 834, 111, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_rifle", "boss_rifle.bmp", 1476, 72, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_transform", "boss_transform.bmp", 2430, 175, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_blast", "boss_blast.bmp", 1554, 102, 14, 1, true, RGB(255, 0, 255));
	//UI
	IMAGEMANAGER->addImage("GAMEOVER", "gameover.bmp", 600, 254, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GAMECLEAR", "game_clear3.bmp", 844, 164, true, RGB(255, 0, 255));
	// 스타트 화면
	start_bg = new image;
	start_bg->init("start_animation.bmp", 28000, 600, 28, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start", "start.bmp", 1000, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("logo", "logo5.bmp", 495, 262, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ment", "ment2.bmp", 320, 40, true, RGB(255, 0, 255));

	bg = new image;
	bg->init("background.bmp", 19200, 600, true, RGB(255, 0, 255));
	camera = 0;
	gameStart = 0;
	game_anime = 0;
	fade_out = 1;
	fade = 0;
	fade2 = 0;
	fade3 = 0;
	count = 0;
	out = false;
	//_ship = new spaceShip;
	//_em = new enemyManager;
	//_ship->init();
	//_em->init();
	//_em->setMinion();
	//_ship->setEmMemoryAddressLink(_em);
	//_em->setSpaceShipMemoryAddressLink(_ship);
	//count=1;
	//index = 0;
	//respawn = 0;
	//dead_count = 0;
	//fade = 0;
	//_slt = new saveLoadTest;

	return S_OK;
}

void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_ship);

}

void playGround::update()
{
	gameNode::update();
	if (gameStart == 0)
	{
		if (out == false)
		{
			fade_out += 3;
			if (fade_out > 255)
			{
				fade_out = 255;
				out = true;
			}
		}
		if (out)
			game_anime++;
		count++;
		if (count == 3)
		{
			game_anime++;
			count = 0;
		}
		if (game_anime > start_bg->getMaxFrameX())
		{
			game_anime = start_bg->getMaxFrameX();
			if (out)
			{
				fade += 3;
				fade_out -= 5;
			}
			if (fade_out < 0)
			{
				fade_out = 0;
			}
			//if (fade_out < 50)
			//{
			//	fade += 5;
			//}
			if (fade > 255)
			{
				fade = 255;
				fade2 += 5;
			}
			if (fade2 > 255)
			{
				fade2 = 255;
				fade3 += 5;
			}
			if (fade3 > 255)
			{
				fade3 = 255;
		
			}
		}
		if(KEYMANAGER->isOnceKeyDown(VK_RETURN))
			gameStart = 1;
	}
	else if(gameStart == 1)
	{
		_ship = new spaceShip;
		_em = new enemyManager;
		_ship->init();
		_em->init();
		_em->setMinion();
		_ship->setEmMemoryAddressLink(_em);
		_em->setSpaceShipMemoryAddressLink(_ship);
		count = 1;
		index = 0;
		respawn = 0;
		dead_count = 0;
		fade = 0;
		gameStart = 0;
		_slt = new saveLoadTest;
		gameStart = 2;
	}
	else if (gameStart == 2)
	{
		count++;
		camera -= 1;
		_ship->update();
		_em->update();
		if (_em->ALLDEAD() && !_em->getBoss())
		{
			respawn++;
			if (respawn > 100)
			{
				_em->setMinion();
				respawn = 0;
			}
		}
		_slt->update();
		if (_ship->isDead())
		{
			dead_count++;
		}
		//collision();
	}
}
void playGround::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//======================================================================
	if (gameStart == 0)
	{
		start_bg->alphaFrameRender(getMemDC(), 0, 0, game_anime, 0,fade_out);
		IMAGEMANAGER->findImage("start")->alphaRender(getMemDC(),0,0, fade);
		IMAGEMANAGER->findImage("logo")->alphaRender(getMemDC(), 0, 120, fade2);
		IMAGEMANAGER->findImage("ment")->alphaRender(getMemDC(), 150, WINSIZEY/2 + 5, fade3);
	}
	if (gameStart == 2)
	{
		IMAGEMANAGER->findImage("긴배경")->render(getMemDC(), camera, 0);
		if (dead_count > 20)
		{
			fade++;
			if (fade > 255) fade = 255;
			IMAGEMANAGER->findImage("GAMEOVER")->alphaRender(getMemDC(), 200, 200, fade);
		}
		if (_ship->getClear())
		{
			fade++;
			if (fade > 255) fade = 255;
			IMAGEMANAGER->findImage("GAMECLEAR")->alphaRender(getMemDC(), 100, 200, fade);
			//IMAGEMANAGER->findImage("GAMECLEAR")->render(getMemDC(), 200, 100);
		}
		//GG->frameRender(getMemDC(), GG->getX(), GG->getY());
		_ship->render();
		_em->render();
	}

	//==================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
