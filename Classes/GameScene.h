#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Shop.h"
#include "Teleport.h"
#include "WorldMap.h"
USING_NS_CC;

class GameScene : public cocos2d::Node
{
public:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void addArtifactChest();
	void runArtifactView();
	void addPickedHero();
	std::string heroes[8] = {"", "ryze", "ashe" ,"garen", "twisted_fate", "elise", "katarina", "kaisa" };
};
#endif
