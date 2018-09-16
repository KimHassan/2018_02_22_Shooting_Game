#pragma once
#include "gameNode.h"
#include <vector>

//총알 구조체
struct tagBullet
{
	image* bulletImage;		//총알의 이미지
	RECT rc;				//총알의 렉트
	float x, y;				//총알 좌표
	float radius;			//총알 붼지름
	float speed;			//총알 슷히드
	float angle;			//총알 앵글
	float fireX, fireY;		//총알 발사위치
	bool isFire;			//발사유무
	int count;				//프레임 돌릴 카운트
	int power;
	int range;
	bool explode;
	int max_count;
};

class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
};

//장전을 해두고 발사하는 미사일
class missile : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;			//사거리
public:
	missile();
	~missile();

	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);

	void move(void);
};

//발사할때 생성해서 쏠 미사일
class yankeeGoHome : public gameNode
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _bulletMax;

public:
	yankeeGoHome();
	~yankeeGoHome();

	HRESULT init(int missileMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);

	void move();

	void removeYankee(int arrNum);

	//총알에 대한 접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};

