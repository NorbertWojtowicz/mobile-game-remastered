#ifndef __ALLY_HERO_H__
#define __ALLY_HERO_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;
class AllyHero
{
public:
	std::string name;
	short health, strength;
	void setName(std::string name);
	std::string getName();
	void initFirstSpell();
	virtual void castFirstSpell() = 0;
	void initSecondSpell();
	virtual void castSecondSpell() = 0;
	void runFirstSpellCooldown();
	void runSecondSpellCooldown();
	void initFirstSpellCooldownAnimate();
	void initSecondSpellCooldownAnimate();
	void initFirstSpellCooldownSprite();
	void initSecondSpellCooldownSprite();
	void addFirstSpellCooldownSpriteToRunningScene();
	void addSecondSpellCooldownSpriteToRunningScene();
	Animate* firstSpellAnimate, * secondSpellAnimate,
		   * firstSpellCooldownAnimate, * secondSpellCooldownAnimate;
	Menu* spellsMenu;
	MenuItemImage* spellOneIcon, * spellTwoIcon;
	Sprite* firstSpellCooldownSprite, * secondSpellCooldownSprite;
	Label* hpLabel;
	float timeToDealDamageInFirstSpell, timeToDealDamageInSecondSpell,
		  firstSpellFrameDuration, secondSpellFrameDuration;
	short firstSpellNumberOfFrames, secondSpellNumberOfFrames, 
		  firstSpellCooldownNumberOfFrames, secondSpellCooldownNumberOfFrames;
};
#endif
