#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class WorldMap : public cocos2d::Node
{
public:
	WorldMap createMap();
	CREATE_FUNC(WorldMap);
	virtual bool init();
};

#endif
