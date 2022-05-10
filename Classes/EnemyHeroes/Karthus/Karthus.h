#ifndef __KARTHUS_H__
#define __KARTHUS_H__
#include "EnemyHeroes/EnemyHero.h"
class Karthus : public EnemyHero
{
public:
	Karthus();
private:
	void castFirstSpell();
};
#endif