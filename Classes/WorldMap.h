#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class WorldMap : public cocos2d::Node
{
public:
	CREATE_FUNC(WorldMap);
	virtual bool init();
	static Scene* createScene();
	ui::ScrollView* scrollView;
	void initScrollView();
private:
	void addIslandsToScrollView();
	void startFirstLevel();
};

#endif
