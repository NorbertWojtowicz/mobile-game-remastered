#include "Scenes/WorldMap/WorldMap.h"
#include "Scenes/LevelScene/LevelScene.h"
#include "AllyHeroes/Ashe/Ashe.h"
#include "AllyHeroes/Garen/Garen.h"
#include "EnemyHeroes/Cassiopeia/Cassiopeia.h"
#include "EnemyHeroes/Darius/Darius.h"
#include "AllyHeroes/Twisted_Fate/Twisted_Fate.h"
#include "EnemyHeroes/Taliyah/Taliyah.h"
#include "EnemyHeroes/Karthus/Karthus.h"
#include "EnemyHeroes/Pantheon/Pantheon.h"
#include "EnemyHeroes/Lucian/Lucian.h"
#include "EnemyHeroes/Kogmaw/Kogmaw.h"
#include "EnemyHeroes/Malhazar/Malhazar.h"
#include "EnemyHeroes/Irelia/Irelia.h"
#include "EnemyHeroes/Yuumi/Yuumi.h"
#include "AllyHeroes/Elise/Elise.h"
#include "AllyHeroes/Katarina/Katarina.h"
#include "AllyHeroes/Kaisa/Kaisa.h"
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
	scrollView->setInnerContainerSize(scrollViewBackground->getBoundingBox().size * 1.58);
	scrollView->setContentSize(scrollViewBackground->getContentSize());
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setScrollBarEnabled(0);
	scrollView->jumpToBottom();
	scrollView->addChild(scrollViewBackground);
	addIslandsToScrollView();
	addCloseButton();
}
void WorldMap::addIslandsToScrollView()
{
	auto basePosition = -155;
	allyId = UserDefault::getInstance()->getIntegerForKey("allyHeroId");
	levelsMenu = Menu::create();
	for (int i = 1; i < 12; i++)
	{
		auto num = StringUtils::format("%d", i);
		if (i == 11)
			num = StringUtils::format("%d", 0);
		levels.push_back(MenuItemImage::create("worldMap/islandLevel" + num + ".png", "worldMap/islandLevel" + num + ".png", CC_CALLBACK_0(WorldMap::startLevelWithHeroesId, this, i - 1, allyId)));
		if (i == 1)
			levels[i - 1]->setPosition(Vec2(-80, -390));
		else if (i == 11)
			levels[i - 1]->setPosition(Vec2(80, -390));
		else
		{
			levels[i - 1]->setPosition(0, basePosition);
			basePosition += 265;
		}
		levelsMenu->addChild(levels[i - 1]);
		std::string key = "lvl" + num + "Unlocked";
		if ((UserDefault::getInstance()->getBoolForKey(key.c_str()) != true) && (((i!=1)&&(i!=11))))
		{
			levels[i - 1]->setEnabled(0);
			auto padlockSprite = Sprite::create("other/padlock.png");
			padlockSprite->setPosition(Vec2(320, levels[i - 1]->getPositionY() + 590));
			scrollView->addChild(padlockSprite, 2);
		}
	}
	scrollView->addChild(levelsMenu, 1);
}
void WorldMap::startLevelWithHeroesId(short enemyId, short allyId)
{
	prepareEnemyMap();
	prepareAllyMap();
	auto enemy = mapEnemy[enemiesTab[enemyId]]();
	auto ally = mapAlly[alliesTab[allyId]]();
	auto scene = LevelScene::createSceneWithEnemyAndAllyHero(enemy, ally);
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
	mapAlly["Kaisa"] = &createAllyHeroInstance<Kaisa>;
}
void WorldMap::addCloseButton()
{
	auto closeBtn = MenuItemImage::create("buttons/cross.png", "buttons/cross.png", CC_CALLBACK_0(WorldMap::closeScene, this));
	closeBtn->setPosition(Vec2(270, 500));
	auto menu = Menu::create(closeBtn, NULL);
	this->addChild(menu, 2);
}
void WorldMap::closeScene()
{
	this->removeAllChildren();
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}
