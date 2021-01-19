#include "Elise.h"
Elise::Elise()
{
	this->setName("elise");
	this->health = 10;
	this->constHealth = 10;
	this->strength = 4;
	this->timeToDealDamageInFirstSpell = 1.65f;
	this->timeToDealDamageInSecondSpell = 1.8f;
	this->firstSpellNumberOfFrames = 13;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 10;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.15f;
	this->secondSpellFrameDuration = 0.2f;
}
void Elise::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 250));
	sceneNode->addChild(sprite, 3);
	auto moveBy = MoveBy::create(1.65f, Vec2(0, 300));
	sprite->runAction(moveBy);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runFirstSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
}
void Elise::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	Sprite* sword = Sprite::create();
	sword->setPosition(Vec2(320, 850));
	sceneNode->addChild(sword, 3);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	sword->runAction(attackSequence);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runSecondSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInSecondSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
}