#ifndef __RYZE_H__
#define __RYZE_H__
#include <string>
#include "cocos2d.h"
#include "AllyHero.h"
USING_NS_CC;
class Ryze : public AllyHero
{
public:
	Ryze();
private:
	void castFirstSpell();
	void castSecondSpell();
};
#endif