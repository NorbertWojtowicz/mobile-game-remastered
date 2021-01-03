#ifndef __GAREN_H__
#define __GAREN_H__

#include "AllyHero.h"
class Garen : public AllyHero
{
public:
	Garen();
	virtual void castFirstSpell();
	virtual void castSecondSpell();
};

#endif // !__GAREN_H__