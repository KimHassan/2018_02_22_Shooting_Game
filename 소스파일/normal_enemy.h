#pragma once
#include "enemy.h"
class enemy;
class normal_enemy : public enemy
{

public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);

	normal_enemy();
	~normal_enemy();
	int getTYPE() { return type; }
	inline bool getDEAD() { return dead; }
};

