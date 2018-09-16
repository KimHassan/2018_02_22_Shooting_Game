#pragma once
#include "gameNode.h"
class bomb : public gameNode
{
private:
	POINT pt;
	image *img;
	int currentFrameX;
public:
	HRESULT init(POINT position);
	void render();
	void update();
	bomb();
	~bomb();
	bool remove_bomb();
};

