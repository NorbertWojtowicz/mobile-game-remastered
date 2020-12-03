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
	Animate* firstSpellAnimate, *secondSpellAnimate;
	Label* hpLabel;
	float timeToDealDamageInFirstSpell;
	float timeToDealDamageInSecondSpell;
};
#endif