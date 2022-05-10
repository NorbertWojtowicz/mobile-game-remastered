#include "Katarina.h"
#include <time.h>
Katarina::Katarina()
{
	this->setName("katarina");
	this->health = 15;
	this->health += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->constHealth = 15;
	this->constHealth += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->strength = 2;
	this->strength += UserDefault::getInstance()->getIntegerForKey("additionalAttack");
	this->timeToDealDamageInFirstSpell = 1.05f;
	this->timeToDealDamageInSecondSpell = 0.21f;
	this->firstSpellNumberOfFrames = 7;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 7;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.15f;
	this->secondSpellFrameDuration = 0.03f;
}
void Katarina::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 250));
	sceneNode->addChild(sprite, 3);
	auto moveBy = MoveBy::create(1.2f, Vec2(0, 300));
	sprite->runAction(moveBy);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runFirstSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
}
void Katarina::castSecondSpell()
{
	static int seed = 90000;
	static int throwsCounter = 0;
	if (throwsCounter == 6)
	{
		throwsCounter = 0;
		return;
	}
	if (oponent->health <= strength)
	{
		throwsCounter = -1;
	}
	seed += 1000;
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	srand(seed);
	int x = rand() % 150 + 230;
	sprite->setPosition(Vec2(x, 250));
	sceneNode->addChild(sprite, 3);
	auto moveBy = MoveBy::create(0.24f, Vec2(0, 300));
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), CallFunc::create(CC_CALLBACK_0(AllyHero::castSecondSpell, this)), nullptr);
	sprite->runAction(moveBy);
	sprite->runAction(attackSequence);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runSecondSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInSecondSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
	throwsCounter++;
}