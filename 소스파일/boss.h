#pragma once
#include "enemy.h"
#include "progressBar.h"
enum bossACTION
{
	BOSS_NORMAL = 1,
	BOSS_RIFLE = 0,
	BOSS_BLAST = 2,
	BOSS_X
};
class boss :
	public enemy
{
private:
	int action;
	bool animation;
	int change;
	int change_count;
	progressBar* _hpBar;
	image* hp_bar;
	image* red_bar;
	RECT hp_rc;
	float hit_hp;
	float _currentHP, _maxHP;
	bool dead;
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	void draw(void);
	bool bulletCountFire();
	void get_out();
	inline RECT getRect() { return _rc; }
	inline POINT firePOINT() { return fire; }
	inline int  returnTYPE() { return action; }
	inline RECT gethitRect() { return hit_rc; }
	inline bool getDEAD() { return dead; }
	int  getACTION() { return action; }
	void hit();
	boss();
	~boss();
};

