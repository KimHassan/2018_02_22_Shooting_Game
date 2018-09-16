#pragma once
#include "gameNode.h"
struct ITEM
{
	int type;
	image *img;
	int angle;
	int x;
	int y;
	RECT rc;
	int count;
	float speed;
};
class item :
	public gameNode
{
private:
	vector<ITEM> _vitem;
	vector<ITEM>::iterator _viitem;
	int item_max;
public:
	HRESULT init(int max);
	void update();
	void render();
	void create(float x,float y);
	void move();
	void remove(int num);
	vector<ITEM> getVitem() { return  _vitem; }
	vector<ITEM>::iterator getVIitem() { return  _viitem; }
	item();
	~item();
};

