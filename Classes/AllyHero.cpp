#include "AllyHero.h"
void AllyHero::setName(std::string name)
{
	this->name = name;
}
std::string AllyHero::getName()
{
	return name;
}
void AllyHero::initFirstSpell()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/spells/first/" + name + "FirstSpellAnimate.plist");
	for (int i = 0; i <= firstSpellNumberOfFrames; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + num + ".png"));
	}
	auto firstSpellAnimation = Animation::createWithSpriteFrames(frames, firstSpellFrameDuration);
	firstSpellAnimate = Animate::create(firstSpellAnimation);
	cache->destroyInstance();
}
void AllyHero::initSecondSpell()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/spells/second/" + name + "SecondSpellAnimate.plist");
	for (int i = 0; i <= secondSpellNumberOfFrames; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + num + ".png"));
	}
	auto secondSpellAnimation = Animation::createWithSpriteFrames(frames, secondSpellFrameDuration);
	secondSpellAnimate = Animate::create(secondSpellAnimation);
	cache->destroyInstance();
}
void AllyHero::runFirstSpellCooldown()
{
	initFirstSpellCooldownAnimate();
	initFirstSpellCooldownSprite();
	spellOneIcon->setEnabled(0);
	auto seq = Sequence::create(firstSpellCooldownAnimate, RemoveSelf::create(), CallFunc::create([this]() {this->spellOneIcon->setEnabled(1); }), NULL);
	firstSpellCooldownSprite->runAction(seq);
}
void AllyHero::runSecondSpellCooldown()
{
	initSecondSpellCooldownAnimate();
	initSecondSpellCooldownSprite();
	spellTwoIcon->setEnabled(0);
	auto seq = Sequence::create(secondSpellCooldownAnimate, RemoveSelf::create(), CallFunc::create([this]() {this->spellTwoIcon->setEnabled(1); }), NULL);
	secondSpellCooldownSprite->runAction(seq);
}
void AllyHero::initFirstSpellCooldownAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/spells/first/" + name + "FirstSpellCooldown.plist");
	for (int i = firstSpellCooldownNumberOfFrames; i >= 0; i--)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + "Cooldown" + num + ".png"));
	}
	auto firstSpellCooldownAnimation = Animation::createWithSpriteFrames(frames, 1.0f);
	firstSpellCooldownAnimate = Animate::create(firstSpellCooldownAnimation);
	cache->destroyInstance();
}
void AllyHero::initSecondSpellCooldownAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/spells/second/" + name + "SecondSpellCooldown.plist");
	for (int i = secondSpellCooldownNumberOfFrames; i >= 0; i--)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + "Cooldown" + num + ".png"));
	}
	auto secondSpellCooldownAnimation = Animation::createWithSpriteFrames(frames, 1.0f);
	secondSpellCooldownAnimate = Animate::create(secondSpellCooldownAnimation);
	cache->destroyInstance();
}
void AllyHero::initFirstSpellCooldownSprite()
{
	firstSpellCooldownSprite = Sprite::create();
	firstSpellCooldownSprite->setPosition(Vec2(290, 132));
	firstSpellCooldownSprite->setContentSize(spellOneIcon->getContentSize());
	addFirstSpellCooldownSpriteToRunningScene();
}
void AllyHero::initSecondSpellCooldownSprite()
{
	secondSpellCooldownSprite = Sprite::create();
	secondSpellCooldownSprite->setPosition(Vec2(470, 132));
	secondSpellCooldownSprite->setContentSize(spellTwoIcon->getContentSize());
	addSecondSpellCooldownSpriteToRunningScene();
}
void AllyHero::addFirstSpellCooldownSpriteToRunningScene()
{
	auto node = spellOneIcon->getScene();
	node->addChild(firstSpellCooldownSprite);
}
void AllyHero::addSecondSpellCooldownSpriteToRunningScene()
{
	auto node = spellTwoIcon->getScene();
	node->addChild(secondSpellCooldownSprite);
}
void AllyHero::turnOffSpells()
{
	spellOneIcon->setEnabled(0);
	spellTwoIcon->setEnabled(0);
}