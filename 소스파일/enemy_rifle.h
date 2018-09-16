#pragma once
#include "gameNode.h"
struct BLASTER
{
	image* bulletImage;		//총알의 이미지
	image* blast;
	RECT rc;				//총알의 렉트
	float x, y;				//총알 좌표
	float speed;			//총알 슷히드
	bool isFire;			//발사유무
	int count;				//프레임 돌릴 카운트
};
class enemy_rifle :
	public gameNode
{
private:
	vector<BLASTER>				_vBullet;
	vector<BLASTER>::iterator		_viBullet;

	float _range;
	int _bulletMax;
	int count;
public:
	HRESULT init(int missileMax, float range);
	void release(void);
	void update();
	void render(void);
	void fire(float x, float y);
	void move();

	void remove_rifle(int arrNum);

	//총알에 대한 접근자
	vector<BLASTER> getVBullet() { return _vBullet; }
	vector<BLASTER>::iterator getVIBullet() { return _viBullet; }
	enemy_rifle();
	~enemy_rifle();
};

