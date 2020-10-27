#include "WorldMap.h"
#include "BrandLevel.h"
#include "Brand.h"
Scene* WorldMap::createScene()
{
	auto scene = Scene::create();
	auto node = WorldMap::create();
	scene->addChild(node);
	return scene;
}
bool WorldMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->initScrollView();
	this->addChild(this->scrollView);
	return true;
}
void WorldMap::initScrollView()
{
	auto scrollViewBackground = Sprite::create("backgrounds/worldMapBG.png");
	scrollViewBackground->setPosition(Vec2(320, 948));
	scrollView = ui::ScrollView::create();
	scrollView->setPosition(Vec2(0, 0));
	scrollView->setBounceEnabled(1);
	scrollView->setInnerContainerSize(scrollViewBackground->getBoundingBox().size * 1.3);
	scrollView->setContentSize(scrollViewBackground->getContentSize());
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setScrollBarEnabled(0);
	scrollView->jumpToBottom();
	scrollView->addChild(scrollViewBackground);
	addIslandsToScrollView();
}
void WorldMap::addIslandsToScrollView()
{
	MenuItemImage* level1 = MenuItemImage::create("worldMap/islandLevel1.png", "worldMap/islandLevel1.png", CC_CALLBACK_0(WorldMap::setupFirstLevel, this));
	level1->setPosition(Vec2(0, -400));
	Menu* menu = Menu::create(level1, NULL);
	scrollView->addChild(menu, 1);
}
void WorldMap::setupFirstLevel()
{
#define enemy Brand
	createSceneWithAllyHero(0);
}
void WorldMap::createSceneWithAllyHero(int heroId)
{
#if heroId == 0
#define ally Ryze
#endif
#if heroId == 1
#define ally Ashe
#endif
#if heroId == 2
#define ally Garen
#endif
#if heroId == 3
#define ally Twisted_Fate
#endif
	startLevel();
}
void WorldMap::startLevel()
{
	auto scene = BrandLevel<enemy, ally>::createScene();
	Director::getInstance()->replaceScene(scene);
}
