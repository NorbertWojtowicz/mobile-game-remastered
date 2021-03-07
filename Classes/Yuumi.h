#ifndef __YUUMI_H__
#define __YUUMI_H__
#include "EnemyHero.h"
class Yuumi : public EnemyHero
{
public:
	Yuumi();
private:
	void castFirstSpell();
};
#endif