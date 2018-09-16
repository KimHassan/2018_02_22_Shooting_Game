#pragma once
#include "gameNode.h"
struct BLASTER
{
	image* bulletImage;		//�Ѿ��� �̹���
	image* blast;
	RECT rc;				//�Ѿ��� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ
	float speed;			//�Ѿ� ������
	bool isFire;			//�߻�����
	int count;				//������ ���� ī��Ʈ
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

	//�Ѿ˿� ���� ������
	vector<BLASTER> getVBullet() { return _vBullet; }
	vector<BLASTER>::iterator getVIBullet() { return _viBullet; }
	enemy_rifle();
	~enemy_rifle();
};

