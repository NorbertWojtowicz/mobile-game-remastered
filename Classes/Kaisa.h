#ifndef __KAISA_H__
#define __KAISA_H__

#include "AllyHero.h"
class Kaisa : public AllyHero
{
public:
	Kaisa();
private:
	virtual void castFirstSpell();
	virtual void castSecondSpell();
	DelayTime* delay(float timeDelay);
};

#endif
