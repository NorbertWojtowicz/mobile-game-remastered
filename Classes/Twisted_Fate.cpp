#include "Twisted_Fate.h"
#include <time.h>
Twisted_Fate::Twisted_Fate()
{
	setName("twisted_fate");
	this->health = 9;
	this->health += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->constHealth = 9;
	this->constHealth += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
	this->strength = 3;
	this->strength += UserDefault::getInstance()->getIntegerForKey("additionalAttack");
	this->timeToDealDamageInFirstSpell = 0.8f;
	this->timeToDealDamageInSecondSpell = 1.5f;
	this->firstSpellNumberOfFrames = 2;
	this->firstSpellCooldownNumberOfFrames = 4;
	this->secondSpellNumberOfFrames = 5;
	this->secondSpellCooldownNumberOfFrames = 9;
	this->firstSpellFrameDuration = 0.2f;
	this->secondSpellFrameDuration = 0.1f;
	isAdded = false;
	cardNum = 3;
}
void Twisted_Fate::castFirstSpell()
{
	addCardMenuToScene();
	changeCard();
}
void Twisted_Fate::castSecondSpell()
{
	initSecondSpell();
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(320, 1000));
	sceneNode->addChild(sprite, 4);
	auto attackSequence = Sequence::create(secondSpellAnimate, RemoveSelf::create(), nullptr);
	sprite->runAction(attackSequence);
	randDiceNumber();
}
void Twisted_Fate::changeCard()
{
	if (cardNum == 4)
		cardNum = 1;
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto num = StringUtils::format("%i", cardNum);
	actualCard->setNormalImage(Sprite::create("heroes/twisted_fate/spells/first/card" + num + ".png"));
	actualCard->setCallback(CC_CALLBACK_0(Twisted_Fate::dealDamageWithCard, this, cardNum));
	cardSeq = Sequence::create(DelayTime::create(firstSpellFrameDuration), CallFunc::create([this]() { changeCard(); }), nullptr);
	cardSeq->setTag(3);
	cardNum++;
	sceneNode->runAction(cardSeq);
}
void Twisted_Fate::addCardMenuToScene()
{
	if (!isAdded)
	{
		auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
		actualCard = MenuItemImage::create();
		cardMenu = Menu::create(actualCard, NULL);
		actualCard->setTag(4);
		actualCard->setPosition(Vec2(-30, -436));
		sceneNode->addChild(cardMenu);
		isAdded = true;
	}
}
void Twisted_Fate::dealDamageWithCard(short num)
{
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	sceneNode->stopActionByTag(3);
	cardMenu->removeChildByTag(4);
	isAdded = false;
	short dmg;
	switch (num)
	{
	case 1:
		dmg = strength - 1;
		break;
	case 2:
		dmg = strength;
		break;
	case 3:
		dmg = strength - 1;
		break;
	}
	runCardAnimate(cardNum);
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, dmg));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runFirstSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);
}
void Twisted_Fate::runCardAnimate(short numberOfCard)
{
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto cardAnimate = createCardAnimate(numberOfCard);
	auto cardSprite = Sprite::create();
	cardSprite->setPosition(Vec2(320, 300));
	auto moveBy = MoveBy::create(0.8f, Vec2(0, 200));
	auto cardAnimSeq = Sequence::create(cardAnimate, DelayTime::create(0.5f), RemoveSelf::create(), nullptr);
	sceneNode->addChild(cardSprite, 3);
	cardSprite->runAction(moveBy);
	cardSprite->runAction(cardAnimSeq);
}
void Twisted_Fate::randDiceNumber()
{
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	srand(time(NULL));
	auto num = rand() % 6 + 1;
	addDiceToSceneWithNumber(num);
	runCardAnimateSecondSpell();
}
Animate* Twisted_Fate::createCardAnimate(short numberOfCard)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	auto num = StringUtils::format("%i", numberOfCard - 1);
	cache->addSpriteFramesWithFile("heroes/twisted_fate/spells/first/tf" + num + ".plist");
	for (int i = 0; i <= 2; i++)
	{
		auto num = StringUtils::format("%d", i);
		frames.pushBack(cache->getSpriteFrameByName("tf" + num + ".png"));
	}
	auto cardAnimation = Animation::createWithSpriteFrames(frames, 0.1f);
	auto cardAnimate = Animate::create(cardAnimation);
	cache->destroyInstance();
	return cardAnimate;
}
void Twisted_Fate::dealDamageAndRunCooldown(short dmg)
{
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::dealDamageToEnemyHero, this, 3 * dmg));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(AllyHero::runSecondSpellCooldown, this));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(timeToDealDamageInSecondSpell), damageCallFunc, nullptr);
	sceneNode->runAction(damageSequence);

}
void Twisted_Fate::addDiceToSceneWithNumber(short num)
{
	auto numStr = StringUtils::format("%i", num);
	auto diceSeq = Sequence::create(DelayTime::create(1.4f), RemoveSelf::create(), nullptr);
	auto diceSprite = Sprite::create("heroes/twisted_fate/spells/second/twisted_fate" + numStr + ".png");
	diceSprite->setPosition(Vec2(320, 1000));
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	dealDamageAndRunCooldown(num);
	sceneNode->addChild(diceSprite);
	diceSprite->runAction(diceSeq);
}
void Twisted_Fate::runCardAnimateSecondSpell()
{
	auto sceneNode = Director::getInstance()->getRunningScene()->getChildByName("levelNode");
	auto cardAnimate = createCardAnimate(3);
	auto cardSprite = Sprite::create();
	cardSprite->setPosition(Vec2(320, 200));
	auto moveBy = MoveBy::create(0.8f, Vec2(0, 200));
	auto cardAnimSeq = Sequence::create(DelayTime::create(0.6f), cardAnimate, DelayTime::create(0.5f), RemoveSelf::create(), nullptr);
	auto cardMoveBySeq = Sequence::create(DelayTime::create(0.6f), moveBy, DelayTime::create(0.5f), RemoveSelf::create(), nullptr);
	sceneNode->addChild(cardSprite, 3);
	cardSprite->runAction(cardMoveBySeq);
	cardSprite->runAction(cardAnimSeq);
}