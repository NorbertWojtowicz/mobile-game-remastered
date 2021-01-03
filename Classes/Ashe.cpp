#include "Ashe.h"
Ashe::Ashe()
{
	this->setName("ashe");
	this->health = 10;
	this->strength = 3;
	this->timeToDealDamageInFirstSpell = 1.95f;
	this->timeToDealDamageInSecondSpell = 2.25f;
	this->firstSpellNumberOfFrames = 12;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 16;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.15f;
	this->secondSpellFrameDuration = 0.15f;
}
void Ashe::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 250));
	sceneNode->addChild(sprite);
	auto moveBy = MoveBy::create(1.65f, Vec2(0, 220));
	sprite->runAction(moveBy);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
}
void Ashe::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	Sprite* arrow = Sprite::create();
	arrow->setPosition(Vec2(620, 710));
	MoveBy* arrowMove = MoveBy::create(2.25f, Vec2(-250, -300));
	sceneNode->addChild(arrow);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	arrow->runAction(attackSequence);
	arrow->runAction(arrowMove);
}