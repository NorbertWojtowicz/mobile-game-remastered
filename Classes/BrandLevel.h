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
	static Scene* createSceneWithEnemyAndAllyHero(EnemyHero* enemy, AllyHero* ally);
private:
	// Hp bars
	void addAllyHeroHpBar();
	void addEnemyHeroHpBar();
	void addAllyHeroHpBorder();
	void addEnemyHeroHpBorder();
	void addAllyHeroHpLoadingBar();
	void addEnemyHeroHpLoadingBar();
	void addAllyHeroHpLabel();
	void addEnemyHeroHpLabel();
	void initHeroesHealth();
	short allyHeroHealth, enemyHeroHealth;
	ui::LoadingBar* allyHeroHpBar, * enemyHeroHpBar;

	// Spells
	void castFirstAllyHeroSpell();
	void castFirstEnemyHeroSpell();
	void castSecondAllyHeroSpell();
	void addHeroSpells(std::string nameOfHero);

	// Spells Cooldowns
	void updateAllyHeroFirstSpellCooldown(float dt);
	void updateEnemyHeroFirstSpellCooldown(float dt);
	void updateSpellsCooldown(float dt);

	// Heroes
	EnemyHero* enemyHero;
	AllyHero* allyHero;

	// Initial
	void addEssentialElements();
	void addBackground(std::string backgroundFilePath);
	void addHeroFace(std::string nameOfHero);
	void addHud();
	virtual bool init();

	// Constructors
	BrandLevel(EnemyHero* enemy, AllyHero* ally);
	static BrandLevel* create(EnemyHero* enemy, AllyHero* ally);

	// Deconstructor
	~BrandLevel() {};

};
#endif