#pragma once
#include "BZDMX.h"
class GameMap : public cocos2d::CCTMXTiledMap
{
public:
	GameMap(void);
	~GameMap(void);
	CC_PROPERTY_READONLY(CCTMXLayer*, platformLayer, PlatformLayer);
	CC_PROPERTY_READONLY(CCTMXLayer*, hideBlockLayer, HideBlockLayer);
	CC_PROPERTY_READONLY(CCTMXLayer*, platformDynamicLayer,PlatformDynamicLayer);
	CC_PROPERTY_READONLY(CCTMXLayer*, biqiLayer,BiqiLayer);
	// ����һ����Ա�����Լ�get##funName������û��set������get##funName����ֻ����������û�ж��塣��������:
	//��̬��������������GameMapʵ��
	static GameMap* gameMapWithTMXFile(const char *tmxFile);
	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	CCPoint tileCoordForPosition(CCPoint position);
	CCPoint positionForTileCoord(CCPoint tileCoord);
	void hideBlockAnimate(CCPoint target);
	void blockMoveFinished(CCNode *sender);
	void removeGold(CCNode *sender);
	//�����Ƴ�ש��
	void removeFloor(CCPoint point);
protected:
	//TiledMap����ĳ�ʼ������
	void extraInit();
	//������ͼ����������
	void enableAnitiAliasForEachLayer();
};

