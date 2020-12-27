#include "Ryze.h"
#include "BrandLevel.h"
Ryze::Ryze()
{
	setName("ryze");
	this->health = 10;
	this->strength = 2;
	this->timeToDealDamageInFirstSpell = 1.95f;
	this->timeToDealDamageInSecondSpell = 0.8f;
	this->firstSpellNumberOfFrames = 16;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 7;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.15f;
	this->secondSpellFrameDuration = 0.2f;
}
void Ryze::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 250));
	sceneNode->addChild(sprite);
	auto moveBy = MoveBy::create(1.95f, Vec2(0, 300));
	sprite->runAction(moveBy);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
}
void Ryze::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 510));
	sceneNode->addChild(sprite);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
}