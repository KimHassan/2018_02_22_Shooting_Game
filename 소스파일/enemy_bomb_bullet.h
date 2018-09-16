#pragma once
#include "bullets.h"
class enemy_bomb_bullet : public bullet
{
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:

	HRESULT init(int bulletMax);
	void release(void);
	void update(void);
	void render(void);
	void explode();
	void fire(float x, float y);
	void move(void);
	void removeBullet(int arrNum);
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
public:
	enemy_bomb_bullet();
	~enemy_bomb_bullet();
};

