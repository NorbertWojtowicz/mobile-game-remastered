#include "Brand.h"
#include "BrandLevel.h"
Brand::Brand()
{
	this->setName("brand");
	this->setSprite("brand");
	sprite->setPosition(310, 545);
	this->strength = 2;
	this->health = 10;
	this->initAnimates();
	this->firstSpellCooldown = 5.0;
	this->secondSpellCooldown = 0.0;
	this->firstSpellTimer = 0.0;
	this->secondSpellTimer = 0.0;
	this->timeToDealDamageInFirstSpell = 2.0;
}
void Brand::initAnimates()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("combatScene/spells/brandFirstSpellAnimate.plist");
	for (int i = 0; i <= 8; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName("brand" + num + ".png"));
	}
	auto firstSpellAnimation = Animation::createWithSpriteFrames(frames, 0.4f);
	firstSpellAnimate = Animate::create(firstSpellAnimation);
	cache->destroyInstance();
}
void Brand::castFirstSpell()
{
	stopWalkAnimate();
	this->initAnimates();
	auto node = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto heroSprite = node->getChildByName("heroSprite");
	auto seq = Sequence::create(firstSpellAnimate, RemoveSelf::create(), CallFunc::create([node, this]() { 
																										 this->setSprite(this->name); 
																										 node->addChild(this->sprite);
																										 sprite->setPosition(310, 545);
																										 this->sprite->setName("heroSprite");
																										 this->runWalkAnimate();
																									  }), NULL);
	heroSprite->runAction(seq);
}
void Brand::castSecondSpell()
{
	auto heroSprite = Director::getInstance()->getRunningScene()->getChildByTag(10);
	heroSprite->runAction(firstSpellAnimate);
}
void Brand::castFirstSpellAnimate()
{
	
}
void Brand::updateFirstSpellTime(float dt)
{
	firstSpellCooldown -= dt;
	cocos2d::log("Actual time2 is: %d", firstSpellCooldown);
	if (firstSpellCooldown <= 0)
	{
		castFirstSpell();
		firstSpellCooldown = 5.0 + firstSpellAnimate->getDuration();
	}
}
void Brand::dealDamageToAllyHero(short damage)
{
	auto scene = Director::getInstance()->getRunningScene();
	
}
void Brand::initWalkAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/brand/brandWalkAnimate.plist");
	for (int i = 0; i <= 3; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName("brand" + num + ".png"));
	}
	auto walkAnimation = Animation::createWithSpriteFrames(frames, 0.4f);
	walkAnimate = Animate::create(walkAnimation);
	cache->destroyInstance();
}
void Brand::runWalkAnimate()
{
	initWalkAnimate();
	sprite->runAction(RepeatForever::create(walkAnimate))->setTag(1);
}
void Brand::stopWalkAnimate()
{
	sprite->stopActionByTag(1);
}


