#include "Ryze.h"

void Ryze::setName(std::string name)
{
	this->name = name;
}
std::string Ryze::getName()
{
	return name;
}
void Ryze::castFirstSpell()
{
	initFirstSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 250));
	sceneNode->addChild(sprite);
	auto moveBy = MoveBy::create(1.95f, Vec2(0, 300));
	sprite->runAction(moveBy);
	auto attackSequence = Sequence::create(firstSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
}
void Ryze::initFirstSpell()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("combatScene/spells/" + name + "FirstSpellAnimate.plist");
	for (int i = 0; i <= 16; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName("ryze" + num + ".png"));
	}
	auto firstSpellAnimation = Animation::createWithSpriteFrames(frames, 0.15f);
	firstSpellAnimate = Animate::create(firstSpellAnimation);
}
Ryze::Ryze()
{
	this->setName("ryze");
	this->health = 10;
	this->strength = 2;
	this->timeToGetDamage = 1.95f;
}