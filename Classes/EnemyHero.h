#ifndef __ENEMY_HERO_H__
#define __ENEMY_HERO_H__
#include "cocos2d.h"
#include <string>
USING_NS_CC;
class EnemyHero
{
public:
	virtual void castFirstSpell() = 0;
	void initAnimates();
	void updateFirstSpellTime(float dt);
	void runWalkAnimate();
	void stopWalkAnimate();
	void initWalkAnimate();
	void setName(std::string name);
	std::string getName();
	void setSprite(std::string nameOfHero);
	short strength, health;
	Sprite* sprite;
	float firstSpellCooldown, timeToDealDamageInFirstSpell;
	Animate* firstSpellAnimate, *walkAnimate;
	Label* hpLabel;
protected:
	std::string name;
	float firstSpellTimer, firstSpellFrameDuration,const firstSpellCooldownConst, walkFrameDuration;
	short firstSpellNumberOfFrames, walkNumberOfFrames;
	Vec2 defaultPosition;
};
#endif