#pragma once
#include "BZDMX.h"
class Hero  : public cocos2d::CCNode
{
public:
	Hero(void);
	~Hero(void);
	//��̬���������ڴ�����ʿʵ��
	static Hero *heroWithinLayer();
	//����ʿ��ָ�������ƶ�һ��
	void move(int i);
	void jump();
	void animateDone(CCNode *sender);
	bool isHeroMoving;
	bool isJumpDone;
	float hspeed;
	float vspeed;
	void setLayerEmpty(CCPoint start,int width,int height);
	bool isanimate;
	//��ʼ������
	bool heroInit();
	bool isDead;
	bool isWin;
	//CollisionType checkCollision(CCPoint targetosition);
	void setViewpointCenter(CCPoint p);
	CollisionType checkCollisionOnly(CCPoint heroPosition);
	CollisionType checHeadkCollision(CCPoint heroPosition);
private:
	//������ʾ��ʿ����ľ���
	CCSprite *heroSprite;
	//��ʱ����Ŀ���Tilemap����
	CCPoint targetTileCoord;
	CCPoint targetPosition;
	float speed;
};

