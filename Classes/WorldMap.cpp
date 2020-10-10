#include "WorldMap.h"
bool WorldMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto sv = ui::ScrollView::create();
	sv->setPosition(Vec2(0, 0));
	sv->setContentSize(Size(640, 1895));
	sv->setBackGroundImage("backgrounds/worldMapBG.png");
	this->addChild(sv);
	return true;
}