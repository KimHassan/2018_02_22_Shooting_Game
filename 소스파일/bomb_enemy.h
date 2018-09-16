#pragma once
#include "enemy.h"
class bomb_enemy : public enemy
{

public:
	bomb_enemy();
	~bomb_enemy();
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	bool bulletCountFire();
	int getTYPE() { return type; }
	inline bool getDEAD() { return dead; }
};

