#ifndef __KATARINA_H__
#define __KATARINA_H__

#include "AllyHero.h"
class Katarina : public AllyHero
{
public:
	Katarina();
	virtual void castFirstSpell();
	virtual void castSecondSpell();
};

#endif // !__GAREN_H__