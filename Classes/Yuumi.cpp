#include "Yuumi.h"
Yuumi::Yuumi()
{
	this->setName("yuumi");
	this->setSprite(name);
	this->strength = 1;
	this->health = 10;
	this->constHealth = 10;
	this->defaultPosition = Vec2(190, 530);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 3.0;
	this->firstSpellCooldownConst = 3.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 0.8f;
	this->firstSpellNumberOfFrames = 8;
	this->firstSpellFrameDuration = 0.1f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
}
void Yuumi::castFirstSpell()
{
	stopWalkAnimate();
	initAnimates();
	auto node = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto heroSprite = node->getChildByName("heroSprite");
	auto seq = Sequence::create(firstSpellAnimate, RemoveSelf::create(), CallFunc::create([node, this]() {
		setSprite(name);
		node->addChild(sprite);
		sprite->setPosition(defaultPosition);
		sprite->setName("heroSprite");
		runWalkAnimate();
		}), NULL);
	heroSprite->runAction(seq);
	auto dmg = CallFunc::create(CC_CALLBACK_0(Yuumi::dealDamageToAllyHero, this));
	auto delay = DelayTime::create(timeToDealDamageInFirstSpell);
	auto damageSequence = Sequence::create(delay, dmg, nullptr);
	node->runAction(damageSequence);
}