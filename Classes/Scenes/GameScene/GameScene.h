#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Teleport/Teleport.h"
#include "Scenes/WorldMap/WorldMap.h"
USING_NS_CC;

class GameScene : public cocos2d::Node
{
public:
	static Scene* createScene();
private:
	CREATE_FUNC(GameScene);
	void addPickedHero();
	std::string heroes[8] = { "", "ryze", "ashe" ,"garen", "twisted_fate", "elise", "katarina", "kaisa" };
	virtual bool init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
};
#endif
