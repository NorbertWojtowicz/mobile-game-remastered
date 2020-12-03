#ifndef __BRAND_LEVEL_H__
#define __BRAND_LEVEL_H__
#include <string>
#include "cocos2d.h"
#include "WorldMap.h"
#include "Ryze.h"
#include "Brand.h"
#include <sstream>
#include "EnemyHero.h"
#include "GameScene.h"
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
	ui::LoadingBar* allyHeroHpBar, *enemyHeroHpBar;
	void addEssentialElements();
	void initHeroesHealth();
	void addBackground(std::string backgroundFilePath);
	void addHeroFace(std::string nameOfHero);
	void addHud();
	void addHeroSpells(std::string nameOfHero);
	void updateSpellsCooldown(float dt);
	//hp bars
	void addAllyHeroHpBar();
	void addEnemyHeroHpBar();
	void addAllyHeroHpBorder();
	void addEnemyHeroHpBorder();
	void addAllyHeroHpLoadingBar();
	void addEnemyHeroHpLoadingBar();
	void addAllyHeroHpLabel();
	void addEnemyHeroHpLabel();
	void updateAllyHeroHpBar(short amountOfHp);
	void updateEnemyHeroHpBar(short amountOfHp);

	void dealDamageToAllyHero(short strength);
	void dealDamageToEnemyHero(short strength);
	void castFirstAllyHeroSpell();
	void castFirstEnemyHeroSpell();
	void castSecondAllyHeroSpell();
	void updateAllyHeroFirstSpellCooldown(float dt);
	void updateEnemyHeroFirstSpellCooldown(float dt);

	//end level
	void finishLevel();
	void finishBattleWithWin();
	void finishBattleWithLose();
	void showWinPopUp();
	void showLosePopUp();
	void prepareSceneToBeDeleted();
	void stopRunningActions();

	void returnToGameScene();

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
	this->enemyHero.runWalkAnimate();
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
	addAllyHeroHpBar();
	addEnemyHeroHpBar();
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
	auto spellTwoIcon = MenuItemImage::create("combatScene/spells/" + nameOfHero + "Spell2.png", "combatScene/spells/" + nameOfHero + "Spell2.png", CC_CALLBACK_0(BrandLevel<enemy, ally>::castSecondAllyHeroSpell, this));
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
void BrandLevel<T, U>::addAllyHeroHpBar()
{
	addAllyHeroHpBorder();
	addAllyHeroHpLoadingBar();
	addAllyHeroHpLabel();
}
template <typename T, typename U>
void BrandLevel<T, U>::addEnemyHeroHpBar()
{
	addEnemyHeroHpBorder();
	addEnemyHeroHpLoadingBar();
	addEnemyHeroHpLabel();
}
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(360, 35));
	this->addChild(healthBarBorder, 2);
}
template <typename T, typename U>
void BrandLevel<T, U>::addEnemyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(320, 870));
	this->addChild(healthBarBorder, 2);
}
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpLoadingBar()
{
	allyHeroHpBar = ui::LoadingBar::create("combatScene/health.png");
	allyHeroHpBar->setPosition(Vec2(360, 35));
	allyHeroHpBar->setPercent(100);
	this->addChild(allyHeroHpBar, 2);
}
template <typename T, typename U>
void BrandLevel<T, U>::addEnemyHeroHpLoadingBar()
{
	enemyHeroHpBar = ui::LoadingBar::create("combatScene/health.png");
	enemyHeroHpBar->setPosition(Vec2(320, 870));
	enemyHeroHpBar->setPercent(100);
	this->addChild(enemyHeroHpBar, 2);
}
template <typename T, typename U>
void BrandLevel<T, U>::addAllyHeroHpLabel()
{
	std::stringstream ss;
	ss << allyHeroHealth << "/" << allyHeroHealth;
	allyHero.hpLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 30.0f);
	allyHero.hpLabel->setPosition(Vec2(360, 35));
	allyHero.hpLabel->setTextColor(Color4B::BLACK);
	this->addChild(allyHero.hpLabel, 3);
}
template <typename T, typename U>
void BrandLevel<T, U>::addEnemyHeroHpLabel()
{
	std::stringstream ss;
	ss << enemyHeroHealth << "/" << enemyHeroHealth;
	enemyHero.hpLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 30.0f);
	enemyHero.hpLabel->setPosition(Vec2(320, 870));
	enemyHero.hpLabel->setTextColor(Color4B::BLACK);
	this->addChild(enemyHero.hpLabel, 3);
}
template <typename T, typename U>
void BrandLevel<T, U>::updateAllyHeroHpBar(short amountOfHp)
{
	std::stringstream ss;
	ss << amountOfHp << "/" << allyHeroHealth;
	std::string health = ss.str();
	allyHero.hpLabel->setString(health);
	double remainingHealthInPercent = ((double)amountOfHp / allyHeroHealth) * 100;
	allyHeroHpBar->setPercent(remainingHealthInPercent);
}
template <typename T, typename U>
void BrandLevel<T, U>::updateEnemyHeroHpBar(short amountOfHp)
{
	std::stringstream ss;
	ss << amountOfHp << "/" << enemyHeroHealth;
	std::string health = ss.str();
	enemyHero.hpLabel->setString(health);
	double remainingHealthInPercent = ((double)amountOfHp / enemyHeroHealth) * 100;
	enemyHeroHpBar->setPercent(remainingHealthInPercent);
}
template <typename T, typename U>
void BrandLevel<T, U>::dealDamageToAllyHero(short strength)
{
	allyHero.health -= strength;
	updateAllyHeroHpBar(allyHero.health);
	if (allyHero.health <= 0)
		finishBattleWithLose();
}
template <typename T, typename U>
void BrandLevel<T, U>::dealDamageToEnemyHero(short strength)
{
	enemyHero.health -= strength;
	updateEnemyHeroHpBar(enemyHero.health);
	if (enemyHero.health <= 0)
		finishBattleWithWin();
}
template <typename T, typename U>
void BrandLevel<T, U>::castFirstAllyHeroSpell()
{
	allyHero.castFirstSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel<T, U>::dealDamageToEnemyHero, this, allyHero.strength));
	auto damageSequence = Sequence::create(DelayTime::create(allyHero.timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
template <typename T, typename U>
void BrandLevel<T, U>::castSecondAllyHeroSpell()
{
	allyHero.castSecondSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel<T, U>::dealDamageToEnemyHero, this, allyHero.strength));
	auto damageSequence = Sequence::create(DelayTime::create(allyHero.timeToDealDamageInSecondSpell), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
template <typename T, typename U>
void BrandLevel<T, U>::castFirstEnemyHeroSpell()
{
	enemyHero.castFirstSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel<T, U>::dealDamageToAllyHero, this, enemyHero.strength));
	auto damageSequence = Sequence::create(DelayTime::create(enemyHero.timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	this->runAction(damageSequence);
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
void BrandLevel<T, U>::finishBattleWithWin()
{
	stopRunningActions();
	showWinPopUp();
}
template <typename T, typename U>
void BrandLevel<T, U>::finishBattleWithLose()
{
	stopRunningActions();
	finishLevel();
}
template <typename T, typename U>
void BrandLevel<T, U>::finishLevel()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
template <typename T, typename U>
void BrandLevel<T, U>::showWinPopUp()
{
	auto spritePopup = Sprite::create("popups/popup.png");
	spritePopup->setPosition(Vec2(320, 630));
	this->addChild(spritePopup, 4);
	auto okBtn = MenuItemImage::create("buttons/okBtn.png", "buttons/pressedOkBtn.png", CC_CALLBACK_0(BrandLevel<T, U>::returnToGameScene, this));
	okBtn->setPosition(Vec2(0, -200));
	auto menu = Menu::create(okBtn, NULL);
	this->addChild(menu, 4);
}
template <typename T, typename U>
void BrandLevel<T, U>::showLosePopUp()
{

}
template <typename T, typename U>
void BrandLevel<T, U>::stopRunningActions()
{
	this->stopAllActions();
	this->unscheduleAllCallbacks();
}
template <typename T, typename U>
void BrandLevel<T, U>::prepareSceneToBeDeleted()
{
	this->removeAllChildrenWithCleanup(true);
}
template <typename T, typename U>
void BrandLevel<T, U>::returnToGameScene()
{
	prepareSceneToBeDeleted();
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
#endif