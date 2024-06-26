#include "Pantheon.h"
Pantheon::Pantheon()
{
	this->setName("pantheon");
	this->setSprite(name);
	this->strength = 7;
	this->health = 30;
	this->constHealth = 30;
	this->defaultPosition = Vec2(200, 500);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 1.03f;
	this->firstSpellNumberOfFrames = 12;
	this->firstSpellFrameDuration = 0.08f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 4;
	this->numberOfLevel = 6;
}
void Pantheon::castFirstSpell()
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
	auto dmg = CallFunc::create(CC_CALLBACK_0(Pantheon::dealDamageToAllyHero, this));
	auto delay = DelayTime::create(timeToDealDamageInFirstSpell);
	auto delayBetween = DelayTime::create(firstSpellFrameDuration);
	auto damageSequence = Sequence::create(delay, dmg, nullptr);
	node->runAction(damageSequence);
}
