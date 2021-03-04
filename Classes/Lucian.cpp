#include "Lucian.h"
Lucian::Lucian()
{
	this->setName("lucian");
	this->setSprite(name);
	this->strength = 4;
	this->health = 18;
	this->constHealth = 18;
	this->defaultPosition = Vec2(200, 400);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 0.8f;
	this->firstSpellNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.2f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 0;
	this->numberOfLevel = 7;
}
void Lucian::castFirstSpell()
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
	auto dmg = CallFunc::create(CC_CALLBACK_0(Lucian::dealDamageToAllyHero, this));
	auto delay = DelayTime::create(timeToDealDamageInFirstSpell);
	auto delayBetween = DelayTime::create(firstSpellFrameDuration);
	auto damageSequence = Sequence::create(delay, dmg, delayBetween, dmg, delayBetween, dmg, delayBetween, dmg, nullptr);
	node->runAction(damageSequence);
}
