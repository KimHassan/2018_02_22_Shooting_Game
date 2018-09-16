#pragma once
#include "gameNode.h"
struct BLAST
{
	image* bulletImage;		//총알의 이미지
	image* blast;
	RECT rc;				//총알의 렉트
	float x, y;				//총알 좌표
	float radius;			//총알 붼지름
	float speed;			//총알 슷히드
	float angle;			//총알 앵글
	float fireX, fireY;		//총알 발사위치
	bool isFire;			//발사유무
	int count;				//프레임 돌릴 카운트
	int height;
};
class rifle_bullet : public gameNode
{
private:
	vector<BLAST>				_vBullet;
	vector<BLAST>::iterator		_viBullet;

	float _range;
	int _bulletMax;
	int frame;
	int count;
	int blast_height;

public:
	HRESULT init(int missileMax, float range);
	void release(void);
	void update(float x, float y);
	void render(void);

	void fire(float x, float y,float height);

	void move(float x, float y);

	void remove_rifle(int arrNum);

	//총알에 대한 접근자
	vector<BLAST> getVBullet() { return _vBullet; }
	vector<BLAST>::iterator getVIBullet() { return _viBullet; }
	rifle_bullet();
	~rifle_bullet();
};

