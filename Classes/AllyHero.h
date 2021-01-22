#ifndef __ALLY_HERO_H__
#define __ALLY_HERO_H__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
USING_NS_CC;
#include "EnemyHero.h"
class AllyHero
{
public:
	std::string name;
	short health, strength, const constHealth;
	void setName(std::string name);
	std::string getName();
	void initFirstSpell();
	virtual void castFirstSpell() = 0;
	void initSecondSpell();
	virtual void castSecondSpell() = 0;
	void runFirstSpellCooldown();
	void dealDamageToEnemyHero(short dmg);
	void finishBattleWithWin();
	void runSecondSpellCooldown();
	void initFirstSpellCooldownAnimate();
	void initSecondSpellCooldownAnimate();
	void initFirstSpellCooldownSprite();
	void initSecondSpellCooldownSprite();
	void addFirstSpellCooldownSpriteToRunningScene();
	void addSecondSpellCooldownSpriteToRunningScene();
	void turnOffSpells();
	void updateEnemyHeroHpBar(short health);
	void initEnemyHero(EnemyHero* oponent);
	void removePopupsFromScene(Scene* scene);
	void checkIfYuumi(Scene* scene);
	void updateMoneyLabelOnScene(Scene* scene, std::string moneyStr);
	Animate* firstSpellAnimate, * secondSpellAnimate,
		   * firstSpellCooldownAnimate, * secondSpellCooldownAnimate;
	Menu* spellsMenu;
	EnemyHero* oponent;
	MenuItemImage* spellOneIcon, * spellTwoIcon;
	Sprite* firstSpellCooldownSprite, * secondSpellCooldownSprite;
	Label* hpLabel;
	float timeToDealDamageInFirstSpell, timeToDealDamageInSecondSpell,
		  firstSpellFrameDuration, secondSpellFrameDuration;
	short firstSpellNumberOfFrames, secondSpellNumberOfFrames, 
		  firstSpellCooldownNumberOfFrames, secondSpellCooldownNumberOfFrames;
	ui::LoadingBar* hpBar;
};
#endif
