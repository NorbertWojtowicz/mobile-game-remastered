#ifndef __TWISTED_FATE_H__
#define __TWISTED_FATE_H__
#include "AllyHero.h"
class Twisted_Fate : public AllyHero
{
public:
	Twisted_Fate();
	void castFirstSpell();
	void castSecondSpell();
	void changeCard();
	void addCardMenuToScene();
	void dealDamageWithCard(short num);
	void runCardAnimate(short numberOfCard);
	void randDiceNumber();
	void dealDamageAndRunCooldown(short dmg);
	void addDiceToSceneWithNumber(short number);
	void runCardAnimateSecondSpell();
	Animate* createCardAnimate(short numberOfCard);
	bool isAdded;
	short cardNum;
	Sequence* cardSeq;
	MenuItemImage* firstCardIcon, * secondCardIcon, * thirdCardIcon, * actualCard;
	Menu* cardMenu;
};
#endif // !__TWISTED_FATE_H__

