#ifndef __GAREN_H__
#define __GAREN_H__

#include "AllyHeroes/AllyHero.h"
class Garen : public AllyHero
{
public:
	Garen();
private:
	virtual void castFirstSpell();
	virtual void castSecondSpell();
};

#endif // !__GAREN_H__