#ifndef __RYZE_H__
#define __RYZE_H__

#include "cocos2d.h"
USING_NS_CC;
class Ryze
{
public:
	Ryze::Ryze();
	std::string name;
	void setName(std::string name);
	std::string getName();
	void castFirstSpell();
	void castSecondSpell();
	void initFirstSpell();
	Animate* firstSpellAnimate;
};
#endif