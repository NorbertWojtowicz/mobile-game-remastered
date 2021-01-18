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
#include "Pantheon.h"
#include "Lucian.h"
#include "Kogmaw.h"
#include "Malhazar.h"
#include "Irelia.h"
#include "Yuumi.h"
#include "Elise.h"
#include "Katarina.h"
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
	scrollViewBackground->setPosition(Vec2(320, 1345));
	scrollView = ui::ScrollView::create();
	scrollView->setPosition(Vec2(0, 0));
	scrollView->setBounceEnabled(1);
	scrollView->setInnerContainerSize(scrollViewBackground->getBoundingBox().size * 1.56);
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
	level1->setPosition(Vec2(-80, -390));
	MenuItemImage* level2 = MenuItemImage::create("worldMap/islandLevel2.png", "worldMap/islandLevel2.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 1, allyId));
	level2->setPosition(Vec2(0, -155));
	MenuItemImage* level3 = MenuItemImage::create("worldMap/islandLevel3.png", "worldMap/islandLevel3.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 2, allyId));
	level3->setPosition(Vec2(0, 120));
	MenuItemImage* level4 = MenuItemImage::create("worldMap/islandLevel4.png", "worldMap/islandLevel4.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 3, allyId));
	level4->setPosition(Vec2(0, 380));
	MenuItemImage* level5 = MenuItemImage::create("worldMap/islandLevel5.png", "worldMap/islandLevel5.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 4, allyId));
	level5->setPosition(Vec2(0, 630));
	MenuItemImage* level6 = MenuItemImage::create("worldMap/islandLevel6.png", "worldMap/islandLevel6.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 5, allyId));
	level6->setPosition(Vec2(0, 910));
	MenuItemImage* level7 = MenuItemImage::create("worldMap/islandLevel7.png", "worldMap/islandLevel7.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 6, allyId));
	level7->setPosition(Vec2(0, 1180));
	MenuItemImage* level8 = MenuItemImage::create("worldMap/islandLevel8.png", "worldMap/islandLevel8.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 7, allyId));
	level8->setPosition(Vec2(0, 1450));
	MenuItemImage* level9 = MenuItemImage::create("worldMap/islandLevel9.png", "worldMap/islandLevel9.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 8, allyId));
	level9->setPosition(Vec2(0, 1720));
	MenuItemImage* level10 = MenuItemImage::create("worldMap/islandLevel10.png", "worldMap/islandLevel10.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 9, allyId));
	level10->setPosition(Vec2(0, 1960));
	MenuItemImage* level11 = MenuItemImage::create("worldMap/islandLevel1.png", "worldMap/islandLevel1.png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, 10, allyId));
	level11->setPosition(Vec2(80, -390));
	Menu* menu = Menu::create(level1, level2, level3, level4, level5, level6, level7, level8, level9, level10, level11, NULL);
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
	mapEnemy["Pantheon"] = &createEnemyHeroInstance<Pantheon>;
	mapEnemy["Lucian"] = &createEnemyHeroInstance<Lucian>;
	mapEnemy["Kogmaw"] = &createEnemyHeroInstance<Kogmaw>;
	mapEnemy["Malhazar"] = &createEnemyHeroInstance<Malhazar>;
	mapEnemy["Irelia"] = &createEnemyHeroInstance<Irelia>;
	mapEnemy["Yuumi"] = &createEnemyHeroInstance<Yuumi>;
}
template <typename T>
AllyHero* createAllyHeroInstance() { return new T; }
void WorldMap::prepareAllyMap()
{
	mapAlly["Ryze"] = &createAllyHeroInstance<Ryze>;
	mapAlly["Ashe"] = &createAllyHeroInstance<Ashe>;
	mapAlly["Garen"] = &createAllyHeroInstance<Garen>;
	mapAlly["Twisted_Fate"] = &createAllyHeroInstance<Twisted_Fate>;
	mapAlly["Elise"] = &createAllyHeroInstance<Elise>;
	mapAlly["Katarina"] = &createAllyHeroInstance<Katarina>;
}
