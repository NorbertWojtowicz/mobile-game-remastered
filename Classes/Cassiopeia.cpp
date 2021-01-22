#include "Cassiopeia.h"
Cassiopeia::Cassiopeia()
{
	this->setName("cassiopeia");
	this->setSprite(name);
	this->strength = 6;
	this->health = 15;
	this->constHealth = 15;
	this->defaultPosition = Vec2(260, 400);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 1.4;
	this->firstSpellNumberOfFrames = 7;
	this->firstSpellFrameDuration = 0.2f;
	this->walkFrameDuration = 0.2f;
	this->walkNumberOfFrames = 7;
	this->numberOfArtefact = 2;
	this->numberOfLevel = 2;
}
void Cassiopeia::castFirstSpell()
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
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(EnemyHero::dealDamageToAllyHero, this));
	auto damageSequence = Sequence::create(DelayTime::create(timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	node->runAction(damageSequence);
}