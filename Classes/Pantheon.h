#ifndef __PANTHEON_H__
#define __PANTHEON_H__
#include "EnemyHero.h"
class Pantheon : public EnemyHero
{
public:
	Pantheon();
private:
	void castFirstSpell();
};
#endif