#ifndef __BRAND_LEVEL_H__
#define __BRAND_LEVEL_H__
#include <string>
#include "cocos2d.h"
#include "WorldMap.h"
#include "Ryze.h"
#include "Brand.h"
#include <sstream>
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
	short allyHeroHealth, enemyHeroHealth;
	void addEssentialElements();
	void initHeroesHealth();
	void addBackground(std::string backgroundFilePath);
	void addHeroFace(std::string nameOfHero);
	void addHud();
	void addHeroSpells(std::string nameOfHero);
	void updateSpellsCooldown(float dt);
	void addAllyHeroHpBar(short amountOfHp);
	void addAllyHeroHpBorder();
	void addAllyHeroHpLoadingBar();
	void addAllyHeroHpLabel(short amountOfHp);
	void updateAllyHeroHpBar(short amountOfHp);
	void castFirstAllyHeroSpell();
	void castFirstEnemyHeroSpell();
	void dealDamageToEnemyHero();
	void dealDamageToAllyHero();
	void updateAllyHeroFirstSpellCooldown(float dt);
	void updateEnemyHeroFirstSpellCooldown(float dt);
};
template <typename T, typename U>
bool BrandLevel<T, U>::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->enemyHero = T();
	this->allyHero = U();
	this->initHeroesHealth();
	this->addEssentialElements();
	this->addChild(enemyHero.sprite);
	this->enemyHero.sprite->setName("heroSprite");
	this->schedule(SEL_SCHEDULE(&BrandLevel<T, U>::updateSpellsCooldown), 0.1);
	return true;
}
template <typename T, typename U>
void BrandLevel<T, U>::initHeroesHealth()
{
	allyHeroHealth = allyHero.health;
	enemyHeroHealth = enemyHero.health;
}
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
template <typename enemy, typename ally>
void BrandLevel<enemy, ally>::addEssentialElements()
{
	addBackground("backgrounds/firstSceneBG.png");
	addAllyHeroHpBar(9);
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
	auto spellOneIcon = MenuItemImage::create("combatScene/spells/" + nameOfHero + "Spell1.png", "combatScene/spells/" + nameOfHero + "Spell1.png", CC_CALLBACK_0(BrandLevel<enemy, ally>::castFirstAllyHeroSpell, this));
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
	updateEnemyHeroFirstSpellCooldown(dt);
}
//TBD
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpBar(short amountOfHp)
{
	addAllyHeroHpBorder();
	addAllyHeroHpLoadingBar();
	addAllyHeroHpLabel(amountOfHp);
}
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(360, 35));
	this->addChild(healthBarBorder, 2);
}
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpLoadingBar()
{
	auto healthBar = ui::LoadingBar::create("combatScene/health.png");
	healthBar->setPosition(Vec2(360, 35));
	healthBar->setPercent(100);
	this->addChild(healthBar, 2);
}
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpLabel(short amountOfHp)
{
	allyHero.hpLabel = Label::createWithTTF("10/10", "fonts/Marker Felt.ttf", 30.0f);
	allyHero.hpLabel->setPosition(Vec2(360, 35));
	allyHero.hpLabel->setTextColor(Color4B::BLACK);
	this->addChild(allyHero.hpLabel, 3);
}
template <typename T, typename U>
void BrandLevel<T, U>::updateAllyHeroHpBar(short amountOfHp)
{
	std::stringstream ss;
	ss << amountOfHp << "/" << allyHeroHealth;
	std::string health = ss.str();
	allyHero.hpLabel->setString(health);
}
template <typename T, typename U>
void BrandLevel<T, U>::castFirstAllyHeroSpell()
{
	allyHero.castFirstSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel<T, U>::dealDamageToEnemyHero, this));
	auto damageSequence = Sequence::create(DelayTime::create(5.0f), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
template <typename T, typename U>
void BrandLevel<T, U>::dealDamageToEnemyHero()
{
	
}
template <typename T, typename U>
void BrandLevel<T, U>::dealDamageToAllyHero()
{
	short enemyStrength = 2;
	cocos2d::log("cock :)");
	allyHero.health -= enemyStrength;
	updateAllyHeroHpBar(allyHero.health);
}
template <typename T, typename U>
void BrandLevel<T, U>::updateAllyHeroFirstSpellCooldown(float dt)
{

}
template <typename T, typename U>
void BrandLevel<T, U>::updateEnemyHeroFirstSpellCooldown(float dt)
{
	enemyHero.firstSpellCooldown -= dt;
	if (enemyHero.firstSpellCooldown <= 0)
	{
		castFirstEnemyHeroSpell();
		enemyHero.firstSpellCooldown = 5.0 + enemyHero.firstSpellAnimate->getDuration();
	}
}
template <typename T, typename U>
void BrandLevel<T, U>::castFirstEnemyHeroSpell()
{
	enemyHero.castFirstSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel<T, U>::dealDamageToAllyHero, this));
	auto damageSequence = Sequence::create(DelayTime::create(2.5f), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
#endif