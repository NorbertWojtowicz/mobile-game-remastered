#ifndef __KAISA_H__
#define __KAISA_H__

#include "AllyHero.h"
class Kaisa : public AllyHero
{
public:
	Kaisa();
	virtual void castFirstSpell();
	virtual void castSecondSpell();
	DelayTime* delay(float timeDelay);
};

#endif
