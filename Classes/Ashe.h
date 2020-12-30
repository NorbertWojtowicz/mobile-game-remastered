#ifndef __ASHE_H__
#define __ASHE_H__
#include "cocos2d.h"
#include "AllyHero.h"
USING_NS_CC;
class Ashe : public AllyHero
{
public:
	Ashe();
	void castFirstSpell();
	void castSecondSpell();
};
#endif