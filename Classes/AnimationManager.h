#pragma once
#include "BZDMX.h"
class AnimationManager : public Singleton<AnimationManager>
{
public:
	AnimationManager(void);
	~AnimationManager(void);
	//��ʼ������ģ�滺���
	bool initAnimationMap();
	//�������ֵõ�һ������ģ��
	CCAnimation* getAnimation(int key);
	//����һ������ʵ��
	CCAnimate* createAnimate(int key);
	//����һ������ʵ��
	CCAnimate* createAnimate(const char* key);
	CCSpriteFrame * getSpritFrame(int key);
	
protected:
	//������ʿ���߶���ģ��
	CCAnimation* createHeroMovingAnimationByDirection(HeroDirection direction);
	CCAnimation* createCryAnimation();
	CCAnimation* createVictoryAnimation();
	CCAnimation* createBiqiSmile();
};

//���嶯��������ʵ���ı���
#define sAnimationMgr AnimationManager::instance()
