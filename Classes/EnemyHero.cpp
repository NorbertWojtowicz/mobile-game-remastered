#include "EnemyHero.h"
void EnemyHero::setName(std::string name)
{
	this->name = name;
}
std::string EnemyHero::getName()
{
	return name;
}
void EnemyHero::setSprite(std::string nameOfHero)
{
	//TBD fill filePath correctly
	sprite = Sprite::create("heroes/" + nameOfHero + "/" + nameOfHero + "Sprite.png");
	sprite->setPosition(Vec2(320, 570));
}
void EnemyHero::initAnimates()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/" + name + "FirstSpellAnimate.plist");
	for (int i = 0; i <= firstSpellNumberOfFrames; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + num + ".png"));
	}
	auto firstSpellAnimation = Animation::createWithSpriteFrames(frames, firstSpellFrameDuration);
	firstSpellAnimate = Animate::create(firstSpellAnimation);
	cache->destroyInstance();
}
void EnemyHero::updateFirstSpellTime(float dt)
{
	firstSpellCooldown -= dt;
	cocos2d::log("Actual time2 is: %d", firstSpellCooldown);
	if (firstSpellCooldown <= 0)
	{
		castFirstSpell();
		firstSpellCooldown = firstSpellCooldownConst + firstSpellAnimate->getDuration();
	}
}
void EnemyHero::initWalkAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/" + name + "WalkAnimate.plist");
	for (int i = 0; i <= walkNumberOfFrames; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + num + ".png"));
	}
	auto walkAnimation = Animation::createWithSpriteFrames(frames, walkFrameDuration);
	walkAnimate = Animate::create(walkAnimation);
	cache->destroyInstance();
}
void EnemyHero::runWalkAnimate()
{
	initWalkAnimate();
	sprite->runAction(RepeatForever::create(walkAnimate))->setTag(1);
}
void EnemyHero::stopWalkAnimate()
{
	sprite->stopActionByTag(1);
}