#include "ControlLayer.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
//响应windows键盘事件
#include <windows.h>  
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  
#endif 

CCSprite *leftSprite;
CCSprite *rightSprite;
CCSprite *jumpSprite;
bool leftSpriteTouched;
bool rightSpriteTouched;
bool jumpSpriteTouched;
CCSize size;
ControlLayer::ControlLayer(void)
{
	sGlobal->controlLayer;
}


ControlLayer::~ControlLayer(void)
{
}
bool ControlLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	winLayerInitTimes = 0;
	failedLayerInitTimes = 0;
	leftSpriteTouched = false;
	rightSpriteTouched = false;
	jumpSpriteTouched = false;
	this->setTouchEnabled(true);
	size = CCDirector::sharedDirector()->getWinSize();
	this->setTouchEnabled(true);
	leftSprite = CCSprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(controlLeftkey));
	leftSprite->setPosition(ccp(45, 45));
	this->addChild(leftSprite);
	rightSprite = CCSprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(controlRightkey));
	rightSprite->setPosition(ccp(45 + 90 + 20, 45));
	this->addChild(rightSprite);
	jumpSprite = CCSprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(controlJumpkey));
	jumpSprite->setPosition(ccp(size.width - 70, 45));
	addChild(jumpSprite);
	this->scheduleUpdate();

	return true;
}
void  ControlLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint	location = touch->getLocationInView();
	// touch==NULL;
	location = CCDirector::sharedDirector()->convertToGL(location);
	//左按钮
	if (location.x < 90 && location.y < 90)
	{
		leftSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlLeftPressedkey));
		leftSpriteTouched = true;
	}
	else if (location.x>90 && location.x < 180 && location.y < 90)//右按钮
	{
		rightSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlRightPressedkey));
		rightSpriteTouched = true;
	}
	if (location.x > size.width - 140 && location.y < 90)//跳
	{
		jumpSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlJumpPressedkey));
		jumpSpriteTouched = true;
	}

}
void  ControlLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint	location = touch->getLocationInView();
	// touch==NULL;
	location = CCDirector::sharedDirector()->convertToGL(location);
	if (location.x < 90 && location.y < 90)
	{
		leftSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlLeftkey));
		leftSpriteTouched = false;
	}
	else if (location.x>90 && location.x < 180 && location.y < 90)
	{
		rightSpriteTouched = false;
		rightSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlRightkey));
	}
	if (location.x > size.width - 140 && location.y < 90)
	{
		jumpSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlJumpkey));
		jumpSpriteTouched = false;
	}



}
void ControlLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint	location = touch->getLocationInView();
	// touch==NULL;
	location = CCDirector::sharedDirector()->convertToGL(location);
	if (!(location.x < 90 && location.y < 90))
	{
		if (location.x < size.width / 2)
		{

			leftSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlLeftkey));
			leftSpriteTouched = false;
		}
	}
	if (!(location.x > 110 && location.x < 200 && location.y < 90))
	{
		if (location.x < size.width / 2)
		{
			rightSpriteTouched = false;
			rightSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlRightkey));
		}
	}
	if (!(location.x > (size.width - 135) && location.y < 90))
	{
		if (location.x > size.width / 2)
		{
			jumpSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlJumpkey));
			jumpSpriteTouched = false;
		}
	}

}
void ControlLayer::update(float dt)
{

	if (sGlobal->hero->isDead)
	{
		this->setTouchEnabled(false);
	}
	if (sGlobal->hero->isDead&&failedLayerInitTimes == 0)
	{

		CCLayer *failedLayer = FailedLayer::create();
		sGlobal->game_1_1->addChild(failedLayer, 2);
		//	CCLayer *victoryLayer=VictoryLayer::create();
		//	sGlobal->game_1_1->addChild(victoryLayer);
		failedLayerInitTimes = 1;
		if (sGlobal->isEffectOn)
		{

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio_boos.mp3", false);
		}
	}
	if (sGlobal->hero->isWin&&winLayerInitTimes == 0)
	{
		CCLayer *victoryLayer = VictoryLayer::create();
		sGlobal->game_1_1->addChild(victoryLayer);
		winLayerInitTimes = 1;
		if (sGlobal->isEffectOn)
		{

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio_congratulations.mp3", false);
		}
	}
	int hspeed = 0;
	if (leftSpriteTouched)
	{
		hspeed = -3;
	}
	else if (rightSpriteTouched)
	{
		hspeed = 3;
	}
	else{
		hspeed = 0;
	}

	sGlobal->hero->move(hspeed);
	if (jumpSpriteTouched&&sGlobal->hero->isDead == false)
	{
		if (sGlobal->hero->isJumpDone)
		{
			if (sGlobal->isEffectOn)
			{

				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio_jump.mp3", false);
			}
			sGlobal->hero->isJumpDone = false;
			sGlobal->hero->vspeed = 11;
		}

	}
	sGlobal->hero->jump();
	int x = 0 - sGlobal->game_1_1->getPositionX();
	int y = 0 - sGlobal->game_1_1->getPositionY();
	this->setPosition(ccp(x, y));

//keyboard event
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)      
	if (KEY_DOWN(VK_LEFT)){
		leftSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlLeftPressedkey));
		leftSpriteTouched = true;
	}
	if (KEY_UP(VK_LEFT)){
		leftSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlLeftkey));
		leftSpriteTouched = false;
	}

	if (KEY_DOWN(VK_RIGHT)){
		rightSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlRightPressedkey));
		rightSpriteTouched = true;
	}
	if (KEY_UP(VK_RIGHT)){
		rightSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlRightkey));
		rightSpriteTouched = false;
	}

	if (KEY_DOWN(VK_UP)){
		jumpSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlJumpPressedkey));
		jumpSpriteTouched = true;
	}
	if (KEY_UP(VK_UP)){
		jumpSprite->setDisplayFrame(sAnimationMgr->getSpritFrame(controlJumpkey));
		jumpSpriteTouched = false;
	}
#endif
}