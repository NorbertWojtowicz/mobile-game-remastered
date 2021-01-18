#ifndef __ELISE_H__
#define __ELISE_H__

#include "AllyHero.h"
class Elise : public AllyHero
{
public:
	Elise();
	virtual void castFirstSpell();
	virtual void castSecondSpell();
};

#endif // !__GAREN_H__