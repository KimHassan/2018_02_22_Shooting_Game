#include "stdafx.h"
#include "playGround.h"

//C++�� ���ߵǸ鼭, ��������� ������ CPP������ ���� �� �ְ� �Ǵµ�
//���Ӱ����� Ư���� �ڵ差�� ���ٺ��ϱ�
//������ �� ������ ���ϰ� �ϱ� ���ؼ� �Լ����� cpp�� ���� ������ ��������

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