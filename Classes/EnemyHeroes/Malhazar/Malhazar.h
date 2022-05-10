#ifndef __MALHAZAR_H__
#define __MALHAZAR_H__
#include "EnemyHeroes/EnemyHero.h"
class Malhazar : public EnemyHero
{
public:
	Malhazar();
private:
	void castFirstSpell();
};
#endif