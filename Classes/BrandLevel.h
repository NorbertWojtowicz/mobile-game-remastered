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
class BrandLevel : public cocos2d::Node
{
public:
	BrandLevel(EnemyHero* enemy, AllyHero *ally);
	~BrandLevel() {};
	//static BrandLevel createLevelWithEnemyAndAllyHero(EnemyHero* enemy, Ryze* ally);
	static Scene* createSceneWithEnemyAndAllyHero(EnemyHero* enemy, AllyHero* ally);
	virtual bool init();
	static BrandLevel* create(EnemyHero* enemy, AllyHero* ally);
	//static Scene* createScene();
	EnemyHero* enemyHero;
	AllyHero* allyHero;
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
	void updateEnemyHeroHpBar(short amountOfHp);

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
#endif