#ifndef __IRELIA_H__
#define __IRELIA_H__
#include "EnemyHero.h"
class Irelia : public EnemyHero
{
public:
	Irelia();
private:
	void castFirstSpell();
};
#endif