#include "Ryze.h"
#include "BrandLevel.h"
Ryze::Ryze()
{
	this->setName("ryze");
	this->health = 10;
	this->strength = 2;
	this->timeToDealDamageInFirstSpell = 1.95f;
	this->timeToDealDamageInSecondSpell = 0.8f;
}
void Ryze::setName(std::string name)
{
	this->name = name;
}
std::string Ryze::getName()
{
	return name;
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
	cache->destroyInstance();
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
void Ryze::initSecondSpell()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("combatScene/spells/" + name + "SecondSpellAnimate.plist");
	for (int i = 0; i <= 7; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName("ryze" + num + ".png"));
	}
	auto secondSpellAnimation = Animation::createWithSpriteFrames(frames, 0.2f);
	secondSpellAnimate = Animate::create(secondSpellAnimation);
	cache->destroyInstance();
}
void Ryze::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 510));
	sceneNode->addChild(sprite);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
}
void Ryze::runFirstSpellCooldown()
{
	initFirstSpellCooldownAnimate();
	initFirstSpellCooldownSprite();
	spellOneIcon->setEnabled(0);
	auto seq = Sequence::create(firstSpellCooldownAnimate, RemoveSelf::create(), CallFunc::create([this]() {this->spellOneIcon->setEnabled(1); }), NULL);
	firstSpellCooldownSprite->runAction(seq);
}
void Ryze::initFirstSpellCooldownAnimate()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	cache->addSpriteFramesWithFile("heroes/" + name + "/spells/first/" + name + "FirstSpellCooldown.plist");
	for (int i = 0; i <= 4; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName(name + "Cooldown" + num + ".png"));
	}
	auto firstSpellCooldownAnimation = Animation::createWithSpriteFrames(frames, 1.0f);
	firstSpellCooldownAnimate = Animate::create(firstSpellCooldownAnimation);
	cache->destroyInstance();
}
void Ryze::initFirstSpellCooldownSprite()
{
	firstSpellCooldownSprite = Sprite::create();
	firstSpellCooldownSprite->setPosition(Vec2(290, 132));
	firstSpellCooldownSprite->setContentSize(spellOneIcon->getContentSize());
	addFirstSpellCooldownSpriteToRunningScene();
}
void Ryze::addFirstSpellCooldownSpriteToRunningScene()
{
	auto node = spellOneIcon->getScene();
	node->addChild(firstSpellCooldownSprite);
}