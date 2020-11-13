#include "Brand.h"
#include "BrandLevel.h"
Brand::Brand()
{
	this->setName("brand");
	this->setSprite("brand");
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
}
void Brand::castFirstSpell()
{
	this->initAnimates();
	auto heroSprite = Director::getInstance()->getRunningScene();
	auto c = heroSprite->getChildByName("levelNode");
	auto x = c->getChildByName("heroSprite");
	auto seq = Sequence::create(firstSpellAnimate, RemoveSelf::create(), CallFunc::create([c, this]() { 
																										 this->setSprite(this->name); 
																										 c->addChild(this->sprite);
																										 this->sprite->setName("heroSprite");
																									  }), NULL);
	x->runAction(seq);
	x->setPosition(Vec2(296, 598));
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

