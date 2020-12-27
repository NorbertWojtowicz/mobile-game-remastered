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
	allyId = UserDefault::getInstance()->getIntegerForKey("allyHeroId");
	MenuItemImage* level1 = MenuItemImage::create("worldMap/islandLevel1.png", "worldMap/islandLevel1.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 0, allyId));
	level1->setPosition(Vec2(0, -380));
	Menu* menu = Menu::create(level1, NULL);
	scrollView->addChild(menu, 1);
}
void WorldMap::startLevelWithHeroesId(short enemyId, short allyId)
{
	prepareEnemyMap();
	auto enemy = mapEnemy[enemiesTab[enemyId]]();
	auto ally = new Ryze();
	auto scene = BrandLevel::createSceneWithEnemyAndAllyHero(enemy, ally);
	Director::getInstance()->replaceScene(scene);
}
template <typename T>
EnemyHero* createInstance() { return new T; }
void WorldMap::prepareEnemyMap()
{
	mapEnemy["Brand"] = &createInstance<Brand>;
}
