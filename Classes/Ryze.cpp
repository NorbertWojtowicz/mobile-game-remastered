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
	auto heroSprite = sceneNode->getChildByName("allyHero");
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
	auto firstSpellAnimation = Animation::createWithSpriteFrames(frames, 0.4f);
	firstSpellAnimate = Animate::create(firstSpellAnimation);
}