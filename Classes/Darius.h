#ifndef __DARIUS_H__
#define __DARIUS_H__
#include "EnemyHero.h"
class Darius : public EnemyHero
{
public:
	Darius();
	void castFirstSpell(AllyHero* hero);
};
#endif