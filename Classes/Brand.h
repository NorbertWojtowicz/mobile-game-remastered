#ifndef __BRAND_H__
#define __BRAND_H__
#include "cocos2d.h";
#include <string>
#include "EnemyHero.h"

USING_NS_CC;
class Brand : public EnemyHero
{
public:
	Brand();
	void castFirstSpell();
	void castSecondSpell();
	void castFirstSpellAnimate();
	void initAnimates();
	void dealDamageToAllyHero(short damage);
	void updateFirstSpellTime(float dt);
	void updateSecondSpellTime();/*
private:
	std::string name;
	Sprite* sprite;
	float firstSpellCooldown, secondSpellCooldown, firstSpellTimer, secondSpellTimer;
	Animate* firstSpellAnimate, * secondSpellAnimate;*/
};
#endif