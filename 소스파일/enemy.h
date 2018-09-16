#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _imageName;
	RECT _rc;
	RECT hit_rc;
	image *boost_image;
	//프레임 번호를 따로 두는 이유는 조금있다 (투 비 컨띠뉴)
	int _currentFrameX;
	int _currentFrameY;
	int index;
	int _count;				//카운트
	int _fireCount;			//발사 카운트
	int _rndFireCount;		//랜덤하게 발사하기 위한 카운트
	float speed; //캐릭터의 스피드
	POINT boost; // 부스터 위치
	int boost_frame; // 부스터 프레임
	POINT fire; //발사하는 위치
	int type; //어느 적인지
	int move_count; // 움직일 시간
	int moving; //타이머
	int move_angle; //움직일 각도
	POINT move_pt; //움직일 위치
	POINT moving_pt; //현재위치
	bool dead; //죽었는지
	int move_action_count; // 얼마나 움직였는지 (3번움직이면 죽음)
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

