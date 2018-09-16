#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _imageName;
	RECT _rc;
	RECT hit_rc;
	image *boost_image;
	//������ ��ȣ�� ���� �δ� ������ �����ִ� (�� �� ���촺)
	int _currentFrameX;
	int _currentFrameY;
	int index;
	int _count;				//ī��Ʈ
	int _fireCount;			//�߻� ī��Ʈ
	int _rndFireCount;		//�����ϰ� �߻��ϱ� ���� ī��Ʈ
	float speed; //ĳ������ ���ǵ�
	POINT boost; // �ν��� ��ġ
	int boost_frame; // �ν��� ������
	POINT fire; //�߻��ϴ� ��ġ
	int type; //��� ������
	int move_count; // ������ �ð�
	int moving; //Ÿ�̸�
	int move_angle; //������ ����
	POINT move_pt; //������ ��ġ
	POINT moving_pt; //������ġ
	bool dead; //�׾�����
	int move_action_count; // �󸶳� ���������� (3�������̸� ����)
	int tpye;
public:
	enemy();
	~enemy();

	HRESULT init(const char* imageName, POINT position);
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	void draw(void);
	bool bulletCountFire();
	void get_out();

	inline RECT getRect() { return _rc; }
	inline POINT firePOINT() { return fire; }
	inline int  returnTYPE() { return type; }
	inline RECT gethitRect() { return hit_rc; }
	inline bool getDEAD() { return dead; }
	inline int getTPYE() { return type; }
	inline int getMove_count() { return move_action_count; }
};

