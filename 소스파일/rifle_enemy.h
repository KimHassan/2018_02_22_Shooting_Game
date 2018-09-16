#pragma once
#include "enemy.h"

class enemy;
class rifle_enemy : public enemy
{

public:
	rifle_enemy();
	~rifle_enemy();
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	int getTYPE() { return type; }
	inline bool getDEAD() { return dead; }
};

