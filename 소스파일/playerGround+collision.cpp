#include "stdafx.h"
#include "playGround.h"

//C++이 개발되면서, 헤더파일은 여러개 CPP파일을 가질 수 있게 되는데
//게임개발쪽 특성상 코드량이 많다보니까
//가독성 및 관리를 편하게 하기 위해서 함수별로 cpp를 빼서 관리가 가능해짐

//void playGround::collision()
//{
//	for ( int i = 0; i < _ship->getYankeeMissile()->getVBullet().size(); ++i )
//	{
//		for ( int j = 0; j < _em->getVMinion().size(); ++j )
//		{
//			RECT temp;
//			if ( IntersectRect(&temp, &_em->getVMinion()[j]->getRect(),
//				&_ship->getYankeeMissile()->getVBullet()[i].rc) )
//			{
//				_em->removeMinion(j);
//				_ship->getYankeeMissile()->removeYankee(i);
//				break;
//			}
//		}
//	}
//
//}