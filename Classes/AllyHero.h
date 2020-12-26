#ifndef __ALLY_HERO_H__
#define __ALLY_HERO_H__

#include "cocos2d.h"
USING_NS_CC;
class AllyHero
{
public:
	std::string name;
	short health;
	short strength;
	virtual void setName(std::string name) = 0;
	virtual std::string getName() = 0;
	virtual void initFirstSpell() = 0;
	virtual void castFirstSpell() = 0;
	virtual void initSecondSpell() = 0;
	virtual void castSecondSpell() = 0;
	virtual void runFirstSpellCooldown() = 0;
	virtual void runSecondSpellCooldown() = 0;
	virtual void initFirstSpellCooldownAnimate() = 0;
	virtual void initSecondSpellCooldownAnimate() = 0;
	virtual void initFirstSpellCooldownSprite() = 0;
	virtual void initSecondSpellCooldownSprite() = 0;
	virtual void addFirstSpellCooldownSpriteToRunningScene() = 0;
	virtual void addSecondSpellCooldownSpriteToRunningScene() = 0;
	Animate* firstSpellAnimate, * secondSpellAnimate,
		* firstSpellCooldownAnimate, * secondSpellCooldownAnimate;
	Menu* spellsMenu;
	MenuItemImage* spellOneIcon, * spellTwoIcon;
	Sprite* firstSpellCooldownSprite, * secondSpellCooldownSprite;
	Label* hpLabel;
	float timeToDealDamageInFirstSpell;
	float timeToDealDamageInSecondSpell;
};
#endif
