#ifndef __ELISE_H__
#define __ELISE_H__

#include "AllyHeroes/AllyHero.h"
class Elise : public AllyHero
{
public:
	Elise();
private:
	virtual void castFirstSpell();
	virtual void castSecondSpell();
};

#endif // !__ELISE_H__