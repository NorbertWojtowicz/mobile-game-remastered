#include "Brand.h"
#include "LevelScene.h"
Brand::Brand()
{
	this->setName("brand");
	this->setSprite("brand");
	this->strength = 1;
	this->strength += UserDefault::getInstance()->getIntegerForKey("additionalAttack");
	this->health = 20;
	this->health += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->constHealth = 20;
	this->constHealth += UserDefault::getInstance()->getIntegerForKey("additionalAttack");
	this->defaultPosition = Vec2(310, 550);
	sprite->setPosition(defaultPosition);
	this->firstSpellCooldown = 5.0;
	this->firstSpellCooldownConst = 5.0;
	this->firstSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 2.0;
	this->firstSpellNumberOfFrames = 8;
	this->firstSpellFrameDuration = 0.4f;
	this->walkFrameDuration = 0.4f;
	this->walkNumberOfFrames = 3;
	this->numberOfArtefact = 1;
	this->numberOfLevel = 1;
}
void Brand::castFirstSpell()
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
