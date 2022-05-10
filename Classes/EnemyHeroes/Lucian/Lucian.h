#ifndef __LUCIAN_H__
#define __LUCIAN_H__
#include "EnemyHeroes/EnemyHero.h"
class Lucian : public EnemyHero
{
public:
	Lucian();
private:
	void castFirstSpell();
};
#endif