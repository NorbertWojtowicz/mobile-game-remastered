#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Shop.h"
#include "Teleport.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	Scene* pushWorldMapScene();
};
#endif
