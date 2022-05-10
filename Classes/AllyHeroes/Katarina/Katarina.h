#ifndef __KATARINA_H__
#define __KATARINA_H__

#include "AllyHeroes/AllyHero.h"
class Katarina : public AllyHero
{
public:
	Katarina();
private:
	virtual void castFirstSpell();
	virtual void castSecondSpell();
};

#endif // !__KATARINA_H__