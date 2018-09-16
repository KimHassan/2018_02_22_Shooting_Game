#pragma once
#include "gameNode.h"
struct BLAST
{
	image* bulletImage;		//�Ѿ��� �̹���
	image* blast;
	RECT rc;				//�Ѿ��� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ
	float radius;			//�Ѿ� ������
	float speed;			//�Ѿ� ������
	float angle;			//�Ѿ� �ޱ�
	float fireX, fireY;		//�Ѿ� �߻���ġ
	bool isFire;			//�߻�����
	int count;				//������ ���� ī��Ʈ
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

	//�Ѿ˿� ���� ������
	vector<BLAST> getVBullet() { return _vBullet; }
	vector<BLAST>::iterator getVIBullet() { return _viBullet; }
	rifle_bullet();
	~rifle_bullet();
};

