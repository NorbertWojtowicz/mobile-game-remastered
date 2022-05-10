#include "Kaisa.h"
Kaisa::Kaisa()
{
	this->setName("kaisa");
	this->health = 17;
	this->health += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->constHealth = 17;
	this->constHealth += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->strength = 3;
	this->strength += UserDefault::getInstance()->getIntegerForKey("additionalAttack");
	this->timeToDealDamageInFirstSpell = 0.48f;
	this->timeToDealDamageInSecondSpell = 0.5f;
	this->firstSpellNumberOfFrames = 8;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 10;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.06f;
	this->secondSpellFrameDuration = 0.1f;
}
void Kaisa::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 250));
	sceneNode->addChild(sprite, 3);
	auto moveBy = MoveBy::create(0.48f, Vec2(0, 240));
	sprite->runAction(moveBy);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runFirstSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
}
void Kaisa::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 415));
	sceneNode->addChild(sprite, 3);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runSecondSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, delay(timeToDealDamageInSecondSpell), damageCallFunc, damageCallFunc, 
										   delay(secondSpellFrameDuration), damageCallFunc, delay(secondSpellFrameDuration * 2), damageCallFunc, 
										   delay(secondSpellFrameDuration * 2), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
}
DelayTime* Kaisa::delay(float timeDelay)
{
	return DelayTime::create(timeDelay);
}