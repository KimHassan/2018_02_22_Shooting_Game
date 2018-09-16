#pragma once
#include "gameNode.h"
#include "bullets.h"
#include <vector>
#include "minion.h"
#include "normal_enemy.h"
#include "rifle_enemy.h"
#include "bomb_enemy.h"
#include "enemy_rifle.h"
#include "enemy_bomb_bullet.h"
#include "bomb.h"
#include "item.h"
#include "boss.h"

class spaceShip;
enum ENEMY_TYPE
{
	ENEMY_NORMAL = 0,
	ENEMY_BOMB = 1,
	ENEMY_RIFLE = 2
};
class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;
	typedef vector<bomb*> vBomb;
	typedef vector<bomb*>::iterator viBomb;

private:
	vEnemy	_vMinion;
	viEnemy _viMinion;
	vBomb _vbomb;
	viBomb _vibomb;
	bullet* _bullet;
	enemy_rifle *em_rf;
	enemy_bomb_bullet *bomb_bullet;
	item *_it;
	spaceShip* _ship;
	boss *b;
	int boss_count;
	bool isBoss;
	bool boss_dead;
	bool gameClear;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion(void);

	void minionBulletFire(void);
	void BossFire();
	void collision();
	void hitBoss();
	//적 지우는 함수
	void removeMinion(int arrNum);

	void setSpaceShipMemoryAddressLink(spaceShip* ship) { _ship = ship; }
	void out_enemy();
	void Shield_guard();
	bool ALLDEAD();
	//적 벡터에 대한 접근자
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }
	vBomb* getVBomb() { return &_vbomb;}
	bullet* getBullet() { return _bullet; }
	item* getITEM() { return _it; }
	bool getBoss() { return isBoss; }
	RECT getBossRECT() { return b->gethitRect(); }
	void getBossHIT() { return b->hit(); }
	bool getBossDEAD() { return b->getDEAD(); }
};

