#include "Garen.h"
Garen::Garen()
{
	this->setName("garen");
	this->health = 10;
	this->strength = 4;
	this->timeToDealDamageInFirstSpell = 0.4f;
	this->timeToDealDamageInSecondSpell = 1.05f;
	this->firstSpellNumberOfFrames = 2;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 8;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.2f;
	this->secondSpellFrameDuration = 0.15f;
}
void Garen::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 450));
	sceneNode->addChild(sprite);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
}
void Garen::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	Sprite* sword = Sprite::create();
	sword->setPosition(Vec2(320, 610));
	sceneNode->addChild(sword);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	sword->runAction(attackSequence);
}