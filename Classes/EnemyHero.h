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
	void setName(std::string name);
	std::string getName();
	void updateAllyHeroHpBar(short health);
	void initAllyHero(AllyHero* hero);
	ui::LoadingBar* hpBar;
	short numberOfArtefact, numberOfLevel, health, const constHealth;
	float firstSpellCooldown;
	Label* hpLabel;
	Sprite* sprite;
	Animate* firstSpellAnimate;
	void dealDamageToAllyHero();
	void runWalkAnimate();
protected:
	short strength;
	std::string name;
	float firstSpellTimer, firstSpellFrameDuration,const firstSpellCooldownConst, walkFrameDuration;
	short firstSpellNumberOfFrames, walkNumberOfFrames;
	Vec2 defaultPosition;
	void addLosePopupToScene(Scene* scene);
	void removeLosePopupFromScene(Scene* scene);
	float timeToDealDamageInFirstSpell;
	Animate * walkAnimate;
	AllyHero* oponent;
	void finishBattleWithLose();
	void initAnimates();
	void updateFirstSpellTime(float dt);
	void stopWalkAnimate();
	void initWalkAnimate();
	void setSprite(std::string nameOfHero);
};
#endif