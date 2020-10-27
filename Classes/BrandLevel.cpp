#include "BrandLevel.h"
Scene* BrandLevel::createScene()
{
	auto scene = Scene::create();
	auto node = BrandLevel::create();
	scene->addChild(node);
	return scene;
}
bool BrandLevel::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	return true;
}