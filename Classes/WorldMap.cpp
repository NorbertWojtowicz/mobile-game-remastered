#include "WorldMap.h"
#include "BrandLevel.h"
#include "Brand.h"
#include "Ashe.h"
#include "Garen.h"
#include "Cassiopeia.h"
#include "Darius.h"
#include "Twisted_Fate.h"
#include "Taliyah.h"
#include "Karthus.h"
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
	MenuItemImage* level2 = MenuItemImage::create("worldMap/islandLevel2.png", "worldMap/islandLevel2.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 1, allyId));
	level2->setPosition(Vec2(0, -155));
	MenuItemImage* level3 = MenuItemImage::create("worldMap/islandLevel3.png", "worldMap/islandLevel3.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 2, allyId));
	level3->setPosition(Vec2(0, 120));
	MenuItemImage* level4 = MenuItemImage::create("worldMap/islandLevel3.png", "worldMap/islandLevel3.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 3, allyId));
	level4->setPosition(Vec2(0, 340));
	MenuItemImage* level5 = MenuItemImage::create("worldMap/islandLevel3.png", "worldMap/islandLevel3.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 4, allyId));
	level5->setPosition(Vec2(0, 500));
	Menu* menu = Menu::create(level1, NULL);
	menu->addChild(level2);
	menu->addChild(level3);
	menu->addChild(level4);
	menu->addChild(level5);
	scrollView->addChild(menu, 1);
}
void WorldMap::startLevelWithHeroesId(short enemyId, short allyId)
{
	prepareEnemyMap();
	prepareAllyMap();
	auto enemy = mapEnemy[enemiesTab[enemyId]]();
	auto ally = mapAlly[alliesTab[allyId]]();
	auto scene = BrandLevel::createSceneWithEnemyAndAllyHero(enemy, ally);
	Director::getInstance()->replaceScene(scene);
}
template <typename T>
EnemyHero* createEnemyHeroInstance() { return new T; }
void WorldMap::prepareEnemyMap()
{
	mapEnemy["Brand"] = &createEnemyHeroInstance<Brand>;
	mapEnemy["Cassiopeia"] = &createEnemyHeroInstance<Cassiopeia>;
	mapEnemy["Darius"] = &createEnemyHeroInstance<Darius>;
	mapEnemy["Taliyah"] = &createEnemyHeroInstance<Taliyah>;
	mapEnemy["Karthus"] = &createEnemyHeroInstance<Karthus>;
}
template <typename T>
AllyHero* createAllyHeroInstance() { return new T; }
void WorldMap::prepareAllyMap()
{
	mapAlly["Ryze"] = &createAllyHeroInstance<Ryze>;
	mapAlly["Ashe"] = &createAllyHeroInstance<Ashe>;
	mapAlly["Garen"] = &createAllyHeroInstance<Garen>;
	mapAlly["Twisted_Fate"] = &createAllyHeroInstance<Twisted_Fate>;
}
