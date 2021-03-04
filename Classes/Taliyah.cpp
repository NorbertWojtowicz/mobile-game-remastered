#include "Taliyah.h"
Taliyah::Taliyah()
{
	this->setName("taLiyah");
	this->setSprite(name);
	this->strength = 2;
	this->health = 20;
	this->constHealth = 20;
	this->defaultPosition = Vec2(190, 450);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 1;
	this->firstSpellNumberOfFrames = 14;
	this->firstSpellFrameDuration = 0.125f;
	this->walkFrameDuration = 0.3f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 3;
	this->numberOfLevel = 4;
}
void Taliyah::castFirstSpell()
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
	auto dmg = CallFunc::create(CC_CALLBACK_0(Taliyah::dealDamageToAllyHero, this));
	auto delay = DelayTime::create(timeToDealDamageInFirstSpell);
	auto delayBetween = DelayTime::create(firstSpellFrameDuration);
	auto damageSequence = Sequence::create(delay, dmg, delayBetween, dmg, delayBetween, dmg, delayBetween, dmg, delayBetween, dmg, delayBetween, delayBetween, dmg, nullptr);
	node->runAction(damageSequence);
}
