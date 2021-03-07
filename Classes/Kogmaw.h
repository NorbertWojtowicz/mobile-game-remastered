#ifndef __KOGMAW_H__
#define __KOGMAW_H__
#include "EnemyHero.h"
class Kogmaw : public EnemyHero
{
public:
	Kogmaw();
private:
	void castFirstSpell();
};
#endif