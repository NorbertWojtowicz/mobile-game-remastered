#ifndef __ENEMY_HERO_H__
#define __ENEMY_HERO_H__
#include "cocos2d.h"
#include <string>
#include "AllyHero.h"
USING_NS_CC;
class EnemyHero
{
public:
	virtual void castFirstSpell(AllyHero* hero) = 0;
	void initAnimates();
	void updateFirstSpellTime(float dt);
	void runWalkAnimate();
	void stopWalkAnimate();
	void initWalkAnimate();
	void dealDamageToAllyHero();
	void setName(std::string name);
	std::string getName();
	void updateAllyHeroHpBar(short health);
	void finishBattleWithWin();
	void finishBattleWithLose();
	void initAllyHero(AllyHero* hero);
	void setSprite(std::string nameOfHero);
	short strength, health;
	Sprite* sprite;
	float firstSpellCooldown, timeToDealDamageInFirstSpell;
	Animate* firstSpellAnimate, *walkAnimate;
	Label* hpLabel;
	AllyHero* oponent;
protected:
	std::string name;
	float firstSpellTimer, firstSpellFrameDuration,const firstSpellCooldownConst, walkFrameDuration;
	short firstSpellNumberOfFrames, walkNumberOfFrames;
	Vec2 defaultPosition;
};
#endif