#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__
#include "cocos2d.h"
#include "EnemyHero.h"
#include "Brand.h"
#include "Ryze.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class WorldMap : public cocos2d::Node
{
public:
	CREATE_FUNC(WorldMap);
	virtual bool init();
	static Scene* createScene();
	static void createSceneWithAllyHero(int heroId);
	ui::ScrollView* scrollView;
	void initScrollView();
	void setupFirstLevel();
private:
	void addIslandsToScrollView();
	static void startLevel();
};

#endif
