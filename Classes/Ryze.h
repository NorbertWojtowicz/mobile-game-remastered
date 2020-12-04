#ifndef __RYZE_H__
#define __RYZE_H__

#include "cocos2d.h"
USING_NS_CC;
class Ryze
{
public:
	Ryze::Ryze();
	std::string name;
	short health;
	short strength;
	void setName(std::string name);
	std::string getName();
	void initFirstSpell();
	void castFirstSpell();
	void initSecondSpell();
	void castSecondSpell();
	void runFirstSpellCooldown();
	void runSecondSpellCooldown();
	void initFirstSpellCooldownAnimate();
	void initSecondSpellCooldownAnimate();
	void initFirstSpellCooldownSprite();
	void initSecondSpellCooldownSprite();
	void addFirstSpellCooldownSpriteToRunningScene();
	void addSecondSpellCooldownSpriteToRunningScene();
	Animate* firstSpellAnimate, *secondSpellAnimate, 
		    *firstSpellCooldownAnimate, *secondSpellCooldownAnimate;
	Menu* spellsMenu;
	MenuItemImage* spellOneIcon, * spellTwoIcon;
	Sprite* firstSpellCooldownSprite, *secondSpellCooldownSprite;
	Label* hpLabel;
	float timeToDealDamageInFirstSpell;
	float timeToDealDamageInSecondSpell;
};
#endif