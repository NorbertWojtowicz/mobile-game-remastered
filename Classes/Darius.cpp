#include "Darius.h"
Darius::Darius()
{
	this->setName("darius");
	this->setSprite(name);
	this->strength = 3;
	this->health = 30;
	this->constHealth = 30;
	this->defaultPosition = Vec2(290, 450);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 1.4;
	this->firstSpellNumberOfFrames = 7;
	this->firstSpellFrameDuration = 0.2f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 0;
	this->numberOfLevel = 3;
}
void Darius::castFirstSpell()
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
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(Darius::dealDamageToAllyHero, this));
	auto damageSequence = Sequence::create(DelayTime::create(timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	node->runAction(damageSequence);
}