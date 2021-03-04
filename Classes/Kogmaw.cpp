#include "Kogmaw.h"
Kogmaw::Kogmaw()
{
	this->setName("kogmaw");
	this->setSprite(name);
	this->strength = 2;
	this->health = 50;
	this->constHealth = 50;
	this->defaultPosition = Vec2(190, 400);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 1.6f;
	this->firstSpellNumberOfFrames = 16;
	this->firstSpellFrameDuration = 0.2f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 5;
	this->numberOfLevel = 8;
}
void Kogmaw::castFirstSpell()
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
	auto dmg = CallFunc::create(CC_CALLBACK_0(Kogmaw::dealDamageToAllyHero, this));
	auto delay = DelayTime::create(timeToDealDamageInFirstSpell);
	auto delayBetween = DelayTime::create(firstSpellFrameDuration * 2.85);
	auto damageSequence = Sequence::create(delay, dmg, delayBetween, dmg, delayBetween, dmg, delayBetween, dmg, nullptr);
	node->runAction(damageSequence);
}
