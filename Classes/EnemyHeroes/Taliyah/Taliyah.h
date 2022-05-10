#ifndef __TALIYAH_H__
#define __TALIYAH_H__
#include "EnemyHeroes/EnemyHero.h"
class Taliyah : public EnemyHero
{
public:
	Taliyah();
private:
	void castFirstSpell();
};
#endif