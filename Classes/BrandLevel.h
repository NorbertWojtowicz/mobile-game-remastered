#ifndef __BRAND_LEVEL_H__
#define __BRAND_LEVEL_H__
#include <string>
#include "cocos2d.h"
#include "Brand.h"
#include "EnemyHero.h"
USING_NS_CC;
template <typename T>
class BrandLevel : public cocos2d::Node
{
public:
	BrandLevel() {};
	virtual bool init();
	//CREATE_FUNC(BrandLevel<T>);
	static BrandLevel<T>* create();
	static Scene* createScene();
	T enemyHero;
	void addEssentialElements();
	void addBackground(std::string backgroundFilePath);
	void addHeroFace(std::string nameOfHero);
	void addHud();
	void addHeroSpells(std::string nameOfHero);
	void updateSpellsCooldown(float dt);
};
template <typename T>
Scene* BrandLevel<T>::createScene()
{
	auto scene = Scene::create();
	auto node = BrandLevel<T>::create();
	scene->addChild(node);
	node->setName("levelNode");
	return scene;
}
template <typename T>
BrandLevel<T>* BrandLevel<T>::create()
{
	auto scene = new BrandLevel<T>();
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
template <typename T>
bool BrandLevel<T>::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->enemyHero = T();
	this->addEssentialElements();
	this->addChild(enemyHero.sprite);
	this->enemyHero.sprite->setName("heroSprite");
	this->schedule(CC_SCHEDULE_SELECTOR(BrandLevel<T>::updateSpellsCooldown), 0.1);
	//TO BE DELETED
	/*auto sprite = Sprite::create("combatScene/spells/brand0.png");
	sprite->setPosition(Vec2(296, 598));
	this->addChild(sprite);*/
	//TO BE DELETED
	return true;
}
template <typename T>
void BrandLevel<T>::addEssentialElements()
{
	addBackground("backgrounds/firstSceneBG.png");
	addHeroFace("ryze");
	addHud();
}
template <typename T>
void BrandLevel<T>::addBackground(std::string backgroundFilePath)
{
	auto background = Sprite::create(backgroundFilePath);
	background->setPosition(Vec2(320, 650));
	addChild(background);
}
template <typename T>
void BrandLevel<T>::addHeroFace(std::string nameOfHero)
{
	auto heroFace = Sprite::create("combatScene/" + nameOfHero + "Face.png");
	heroFace->setPosition(Vec2(74, 126));
	addChild(heroFace);
}
template <typename T>
void BrandLevel<T>::addHud()
{
	auto hud = Sprite::create("combatScene/hud.png");
	hud->setPosition(Vec2(320, 128));
	addChild(hud);
	addHeroSpells("ryze");
}
template <typename T>
void BrandLevel<T>::addHeroSpells(std::string nameOfHero)
{
	auto spellOneIcon = MenuItemImage::create("combatScene/spells/" + nameOfHero + "Spell1.png", "combatScene/spells/" + nameOfHero + "Spell1.png", CC_CALLBACK_0(Brand::castFirstSpell, this->enemyHero));
	//TBD correct filepath
	auto spellTwoIcon = MenuItemImage::create("combatScene/spells/ryzeSpell2.png", "combatScene/spells/ryzeSpell2.png");
	spellOneIcon->setPosition(Vec2(-30, -436));
	spellTwoIcon->setPosition(Vec2(+150, -436));
	auto spellsIconMenu = Menu::create();
	spellsIconMenu->addChild(spellOneIcon);
	spellsIconMenu->addChild(spellTwoIcon);
	addChild(spellsIconMenu);
}
template <typename T>
void BrandLevel<T>::updateSpellsCooldown(float dt)
{
	this->enemyHero.updateFirstSpellTime(dt);
}
#endif