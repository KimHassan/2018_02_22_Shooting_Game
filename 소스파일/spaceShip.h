#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"
#include "sword_bullet.h"
#include "normal_bullet.h"
#include "bomb.h"
#include "rifle_bullet.h"

//헤더파일 무한루프 방지를 위한 전방선언
class enemyManager;
enum  ACTION
{
	MOVE,
	NORMAL,
	SWORD,
	RIFLE
};
class spaceShip : public gameNode
{
private:
	image* _ship;
	missile* _missile;
	yankeeGoHome* _ygh;
	sword_bullet* _sw;
	normal_bullet* _nb;
	rifle_bullet* _rb;
	vector<bomb*> _vbomb;
	vector<bomb*>::iterator _vibomb;
	RECT rc;
	RECT shield;
	enemyManager* _em;
	ACTION action;
	//프로그레스 바
	progressBar* _hpBar;
	float _currentHP, _maxHP;
	int frame;
	int count;
	int rifle_charge;
	bool frame_Moving;
	//boost
	image* boost;
	int boost_frame = 0;
	float boost_x;
	float boost_y;
	int shot_delay;
	int sword_power;
	int normal_power;
	bool dead;
	bool gameClear;
	bool start;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision(void);

	void hitDamage(float damage);

	image* getShipImage() { return _ship; }

	yankeeGoHome* getYankeeMissile() { return _ygh; }
	void boss_collision();
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
	RECT getRECT(void) { return rc; }
	RECT getSheild() { return shield; }
	void powerDELETE();
	bool isDead() { return dead; }
	bool getClear() { return gameClear; }
	spaceShip();
	~spaceShip();
};

