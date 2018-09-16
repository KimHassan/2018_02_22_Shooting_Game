#pragma once
#include "bullets.h"
class normal_bullet :
	public yankeeGoHome
{
private:
	vector<tagBullet>  _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;
	int _bulletMax;
public:
	HRESULT init(int missileMax, float range);
	void release();
	void update();
	void render();
	void fire(float x, float y,int power);
	void move();
	void remove_NormalBullet(int arrNum);

	vector<tagBullet> getVBullet(){ return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
	normal_bullet();
	~normal_bullet();
};

