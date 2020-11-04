#ifndef __BRAND_LEVEL_H__
#define __BRAND_LEVEL_H__
#include <string>
#include "cocos2d.h"
#include "WorldMap.h"
#include "Ryze.h"
#include "Brand.h"
#include "EnemyHero.h"
USING_NS_CC;
template <typename T, typename U>
class BrandLevel : public cocos2d::Node
{
public:
	BrandLevel() {};
	virtual bool init();
	static BrandLevel<T, U>* create();
	static Scene* createScene();
	T enemyHero;
	U allyHero;
	void addEssentialElements();
	void addBackground(std::string backgroundFilePath);
	void addHeroFace(std::string nameOfHero);
	void addHud();
	void addHeroSpells(std::string nameOfHero);
	void updateSpellsCooldown(float dt);
};
template <typename T, typename U>
Scene* BrandLevel<T, U>::createScene()
{
	auto scene = Scene::create();
	auto node = BrandLevel<T, U>::create();
	scene->addChild(node);
	node->setName("levelNode");
	return scene;
}
template <typename T, typename U>
BrandLevel<T, U>* BrandLevel<T, U>::create()
{
	auto scene = new BrandLevel<T, U>();
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
	else
	{
		delete scene;
		return nullptr;
	}
}
template <typename T, typename U>
bool BrandLevel<T, U>::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->enemyHero = T();
	this->allyHero = U();
	this->addEssentialElements();
	this->addChild(enemyHero.sprite);
	this->enemyHero.sprite->setName("heroSprite");
	this->schedule(SEL_SCHEDULE(&BrandLevel<T, U>::updateSpellsCooldown), 0.1);
	return true;
}
template <typename enemy, typename ally>
void BrandLevel<enemy, ally>::addEssentialElements()
{
	addBackground("backgrounds/firstSceneBG.png");
	addHeroFace(allyHero.getName());
	addHud();
}
template <typename enemy, typename ally>
void BrandLevel<enemy, ally>::addBackground(std::string backgroundFilePath)
{
	auto background = Sprite::create(backgroundFilePath);
	background->setPosition(Vec2(320, 650));
	addChild(background);
}
template <typename enemy, typename ally>
void BrandLevel<enemy, ally>::addHeroFace(std::string nameOfHero)
{
	auto heroFace = Sprite::create("combatScene/" + nameOfHero + "Face.png");
	heroFace->setPosition(Vec2(74, 126));
	addChild(heroFace);
}
template <typename enemy, typename ally>
void BrandLevel<enemy, ally>::addHud()
{
	auto hud = Sprite::create("combatScene/hud.png");
	hud->setPosition(Vec2(320, 128));
	addChild(hud);
	addHeroSpells(allyHero.getName());
}
template <typename enemy, typename ally>
void BrandLevel<enemy, ally>::addHeroSpells(std::string nameOfHero)
{
	auto spellOneIcon = MenuItemImage::create("combatScene/spells/" + nameOfHero + "Spell1.png", "combatScene/spells/" + nameOfHero + "Spell1.png", CC_CALLBACK_0(ally::castFirstSpell, this->allyHero));
	//TBD correct filepath
	auto spellTwoIcon = MenuItemImage::create("combatScene/spells/ryzeSpell2.png", "combatScene/spells/ryzeSpell2.png");
	spellOneIcon->setPosition(Vec2(-30, -436));
	spellTwoIcon->setPosition(Vec2(+150, -436));
	auto spellsIconMenu = Menu::create();
	spellsIconMenu->addChild(spellOneIcon);
	spellsIconMenu->addChild(spellTwoIcon);
	addChild(spellsIconMenu);
}
template <typename T, typename U>
void BrandLevel<T, U>::updateSpellsCooldown(float dt)
{
	this->enemyHero.updateFirstSpellTime(dt);
}
#endif