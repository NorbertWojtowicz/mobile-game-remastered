#ifndef __CASSIOPEIA_H__
#define __CASSIOPEIA_H__
#include "EnemyHeroes/EnemyHero.h"
class Cassiopeia : public EnemyHero
{
public:
	Cassiopeia();
private:
	void castFirstSpell();
};
#endif
