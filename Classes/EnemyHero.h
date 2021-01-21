#ifndef __ENEMY_HERO_H__
#define __ENEMY_HERO_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
USING_NS_CC;
class AllyHero;
class EnemyHero
{
public:
	virtual void castFirstSpell() = 0;
	void initAnimates();
	void updateFirstSpellTime(float dt);
	void runWalkAnimate();
	void stopWalkAnimate();
	void initWalkAnimate();
	void dealDamageToAllyHero();
	void setName(std::string name);
	std::string getName();
	void updateAllyHeroHpBar(short health);
	void finishBattleWithLose();
	void initAllyHero(AllyHero* hero);
	void setSprite(std::string nameOfHero);
	short strength, health, const constHealth;
	Sprite* sprite;
	float firstSpellCooldown, timeToDealDamageInFirstSpell;
	Animate* firstSpellAnimate, *walkAnimate;
	Label* hpLabel;
	AllyHero* oponent;
	ui::LoadingBar* hpBar;
	short numberOfArtefact;
protected:
	std::string name;
	float firstSpellTimer, firstSpellFrameDuration,const firstSpellCooldownConst, walkFrameDuration;
	short firstSpellNumberOfFrames, walkNumberOfFrames;
	Vec2 defaultPosition;
};
#endif