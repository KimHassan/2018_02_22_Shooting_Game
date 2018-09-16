#pragma once
#include "gameNode.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "saveLoadTest.h"

class playGround : public gameNode
{
private:
	//우주선 클래스
	spaceShip* _ship;
	enemyManager* _em;
	image *GG;
	image *bg;
	saveLoadTest* _slt;
	image *start_bg;
	int count;
	int index;
	float camera;
	int respawn;
	int dead_count;
	int fade;
	int gameStart;
	int game_anime;
	int fade_out;
	int fade2;
	int fade3;
	bool out;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(void);

	//충돌
	void collision();


	playGround();
	~playGround();
};

