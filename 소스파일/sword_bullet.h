#pragma once
#include "bullets.h"
class sword_bullet :
	public yankeeGoHome
{
private:
	vector<tagBullet>  _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;
	int _bulletMax;
	public:
	HRESULT init(int missileMax, float range);
	void fire(float x, float y,int power);
	void render(void);
	void move();
	void update();
	void removeSW(int arrNum);
	sword_bullet();
	~sword_bullet();
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
};

