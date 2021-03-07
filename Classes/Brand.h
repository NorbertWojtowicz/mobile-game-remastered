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
private:
	void castFirstSpell();
};
#endif