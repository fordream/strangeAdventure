#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

typedef enum {
	hdie =  0,//����
	hnormal=1,//����
	hleftJump=2,//������
	hrightJump=5,
	hright=4,//���ҷ���
	hleft=3,//
	hjump=6,//���Ϸ���

} HeroDirection;//��ʿ����

typedef enum
{
	kNone = 1,//����ͨ��
	kWall,//ǽ
	kItem,//��Ʒ
	kDoor,//��
	khideblock,
	kbiqi
	
} CollisionType;//��ײ����

typedef enum
{
	anormal=0,
	aLeftjump,
	arightjump,
	aDie ,//
	aLeft,//�������߶���
	aRight,//�������߶���
	aother,
	heroCry,
	victory,
	biqiSmile,
} AnimationKey;//����ģ���ֵ
typedef enum
{
	heronormalkey=0,
	heroleftJumpkey,
	herorightJumpkey,
	controlLeftkey ,//
	controlLeftPressedkey,
	controlRightkey,
	controlRightPressedkey,
	controlJumpkey,
	controlJumpPressedkey,
	whyBlockKey,
	firmBlockKey,
	goldCoinkey,
	failedboxkey,
	cryFramekey,
	onkey,
	offkey,
}CCSpriteFrameKey;//CCSpriteFrameģ���ֵ
enum 
{
	kZMap = 0,//��ͼ��zOrder
	kZNPC,
	kZTeleport,
	kZHero,//��ʿ�����zOrder
	kZTip,//��ʾ��Ϣ��zOrder
};//GameLayer�и����ֵ���ʾzOrder��tag

enum 
{
	kGameLayer = 0,
	kControlLayer,
	kFadeLayer,
};

enum{
	eSize = 50,
};
#endif