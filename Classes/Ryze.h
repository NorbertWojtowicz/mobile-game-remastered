#ifndef __RYZE_H__
#define __RYZE_H__

#include "cocos2d.h"
#include "AllyHero.h"
USING_NS_CC;
class Ryze : public AllyHero
{
public:
	Ryze::Ryze();
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
};
#endif