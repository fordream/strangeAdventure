#include "Game_1_1.h"

Hero *hero;
CCSprite* shi;
CCSprite* daodan;
int shicount;
int daodancount;
CCMenuItemImage *backItem;
Game_1_1::Game_1_1(void)
{
	sGlobal->game_1_1 = this;
}


Game_1_1::~Game_1_1(void)
{
}
CCScene* Game_1_1::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		// 'layer' is an autorelease object
		Game_1_1 *layer = Game_1_1::create();
		CC_BREAK_IF(!layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool Game_1_1::init()
{
	bool bRet = false;
	do
	{
		daodancount = 0;
		shicount = 0;
		haveTouchBiqi = true;
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		this->setTouchEnabled(true);
		//CCTMXTiledMap	*_tileMap=CCTMXTiledMap::create("TMX_1_5.tmx");
		//addChild(_tileMap);
		GameMap *gameMap = GameMap::gameMapWithTMXFile("TMX_1_5.tmx");
		addChild(gameMap);
		//返回按钮
		backItem = CCMenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(Game_1_1::backItemCallback));
		CC_BREAK_IF(!backItem);

		// Place the menu item bottom-right conner.
		backItem->setPosition(ccp(36, size.height - 36));
		//this->addChild(skipItem);
		CCMenu* backItemMenu = CCMenu::create(backItem, NULL);
		backItemMenu->setPosition(CCPointZero);
		addChild(backItemMenu, 2);
		//初始化精灵
		//hero=CCSprite::create("Hero_image.png",CCRectMake(0,50,50,50));
		//hero->setAnchorPoint(ccp(0,0));
		//hero->setPosition(ccp(46*3,46*2+2));
		//addChild(hero,2);
		hero = Hero::heroWithinLayer();
		addChild(hero);
		hero->setPosition(ccp(46 * 3, 46 * 9));
		ControlLayer *controlLayer = ControlLayer::create();
		addChild(controlLayer);
		controlLayer->setPosition(ccp(0, 0));
		bRet = true;
		if (sGlobal->isMusicOn)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio_bgm_1.mp3", true);
		}


		this->scheduleUpdate();
	} while (0);
	return bRet;
}

void Game_1_1::backItemCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}

CCAnimation* Game_1_1::createAnimationByState(State direction)
{
	CCTexture2D *heroTexture = CCTextureCache::sharedTextureCache()->addImage("hero.png");
	// CCSpriteFrame *frame0,*frame1,*frame2,*frame3;
	CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(heroTexture, CCRectMake(32 * 0, 32 * direction, 32, 32));
	CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(heroTexture, CCRectMake(32 * 1, 32 * direction, 32, 32));
	CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(heroTexture, CCRectMake(32 * 2, 32 * direction, 32, 32));
	CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(heroTexture, CCRectMake(32 * 3, 32 * direction, 32, 32));
	CCArray *animFrames = CCArray::createWithCapacity(4);
	animFrames->addObject(frame0);
	animFrames->addObject(frame1);
	animFrames->addObject(frame2);
	animFrames->addObject(frame3);
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.07f);
	//animation->initWithAnimationFrames(animFrames,0.2f,1);
	animFrames->release();
	return animation;
}

void  Game_1_1::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void  Game_1_1::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void Game_1_1::update(float dt){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	backItem->setPosition(ccp(36 - this->getPositionX(), size.height - 36));
	//产生导弹

	if (sGlobal->hero->getPositionX() + 50 >= 15 * 48 && daodancount == 0 && sGlobal->hero->isDead == false)
	{
		daodan = CCSprite::create("Missileop.png", CCRectMake(0, 0, 48, 72));
		daodancount++;
		daodan->setAnchorPoint(ccp(0, 0));
		daodan->setPosition(ccp(15 * 48, 5 * 48));
		this->addChild(daodan);
	}

	if (daodancount == 1)
	{
		daodan->setPosition(ccp(15 * 48, daodan->getPositionY() + 2));
		if (daodan->getPositionY() > 480)
		{
			daodan->setPosition(ccp(15 * 48, 5 * 48));
		}
		CCRect herRect = CCRectMake(sGlobal->hero->getPositionX(), sGlobal->hero->getPositionY(), 45, 45);
		if (herRect.intersectsRect(CCRectMake(daodan->getPositionX() + 6, daodan->getPositionY() + 8, 40, 65)))
		{
			sGlobal->hero->isDead = true;

		}
	}
	//产生便便

	if (sGlobal->hero->getPositionX() + 50 >= 22 * 48 && shicount == 0 && sGlobal->hero->isDead == false)
	{
		shi = CCSprite::create("shi.png", CCRectMake(0, 0, 47, 57));
		shicount++;
		shi->setAnchorPoint(ccp(0, 0));
		shi->setPosition(ccp(22 * 48, 480));
		this->addChild(shi);
	}
	if (shicount == 1)
	{
		shi->setPosition(ccp(22 * 48, shi->getPositionY() - 6));
		if (shi->getPositionY() < -50)
		{
			shi->setPosition(ccp(22 * 48, 480));
		}
		CCRect herRect = CCRectMake(sGlobal->hero->getPositionX(), sGlobal->hero->getPositionY(), 45, 45);
		if (herRect.intersectsRect(CCRectMake(shi->getPositionX() + 6, shi->getPositionY() + 6, 47, 57)))
		{
			sGlobal->hero->isDead = true;
			shicount = 0;
		}
	}
}