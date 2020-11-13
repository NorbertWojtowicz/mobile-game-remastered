#ifndef __ENEMY_HERO_H__
#define __ENEMY_HERO_H__
#include "cocos2d.h"
#include <string>
USING_NS_CC;
class EnemyHero
{
public:
	virtual void castFirstSpell() = 0;
	virtual void castFirstSpellAnimate() = 0;
	virtual void castSecondSpell() = 0;
	virtual void initAnimates() = 0;
	virtual void updateFirstSpellTime(float dt) = 0;
	virtual void dealDamageToAllyHero(short damage) = 0;
	void setName(std::string name);
	std::string getName();
	void setSprite(std::string nameOfHero);
	short strength, health;
	Sprite* sprite;
	float firstSpellCooldown, secondSpellCooldown, timeToGetDamage;
	Animate* firstSpellAnimate, * secondSpellAnimate;
	Label* hpLabel;
protected:
	std::string name;
	float firstSpellTimer, secondSpellTimer;
};
#endif