#include "Irelia.h"
Irelia::Irelia()
{
	this->setName("irelia");
	this->setSprite(name);
	this->strength = 3;
	this->health = 40;
	this->constHealth = 40;
	this->defaultPosition = Vec2(260, 500);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 0.5f;
	this->firstSpellNumberOfFrames = 12;
	this->firstSpellFrameDuration = 0.1f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 7;
	this->numberOfLevel = 10;
}
void Irelia::castFirstSpell()
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
	auto dmg = CallFunc::create(CC_CALLBACK_0(Irelia::dealDamageToAllyHero, this));
	auto delay = DelayTime::create(timeToDealDamageInFirstSpell);
	auto delayBetween = DelayTime::create(firstSpellFrameDuration);
	auto damageSequence = Sequence::create(delay, dmg, delayBetween, delayBetween, dmg, delayBetween, dmg, delayBetween, delayBetween, dmg, delayBetween, dmg, delayBetween, dmg, nullptr);
	node->runAction(damageSequence);
}