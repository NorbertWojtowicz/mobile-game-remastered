#include "AllyHero.h"
#include "Scenes/GameScene/GameScene.h"
#include <time.h>
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
void AllyHero::initEnemyHero(EnemyHero* oponent)
{
	this->oponent = oponent;
}
void AllyHero::updateEnemyHeroHpBar(short health)
{
	std::stringstream ss;
	ss << health << "/" << oponent->constHealth;
	std::string healthStr = ss.str();
	oponent->hpLabel->setString(healthStr);
	double remainingHealthInPercent = ((double)health / oponent->constHealth) * 100;
	oponent->hpBar->setPercent(remainingHealthInPercent);
}
void AllyHero::dealDamageToEnemyHero(short dmg)
{
	oponent->health -= dmg;
	updateEnemyHeroHpBar(oponent->health);
	if (oponent->health <= 0)
		finishBattleWithWin();
}
void AllyHero::finishBattleWithWin()
{
	auto scene = GameScene::createScene();
	checkIfYuumi(scene);
	Director::getInstance()->replaceScene(scene);
	std::stringstream ss;
	ss << oponent->numberOfArtefact;
	std::string num = ss.str();
	auto baner = Sprite::create("artefacts/a" + num + "R.png");
	baner->setName("artifactPopup");
	baner->setPosition(Vec2(320, 550));
	scene->addChild(baner);
	auto btnOk = MenuItemImage::create("buttons/okBtn.png", "buttons/pressedOkBtn.png", CC_CALLBACK_0(AllyHero::removePopupsFromScene, this, scene));
	auto btnMenu = Menu::create(btnOk, NULL);
	btnMenu->setName("buttonMenu");
	btnOk->setPosition(Vec2(0, -300));
	scene->addChild(btnMenu);
	unlockLevel(oponent->numberOfLevel + 1);
	unlockArtifact(oponent->numberOfArtefact);
}
void AllyHero::removePopupsFromScene(Scene* scene)
{
	scene->removeChildByName("artifactPopup");
	scene->removeChildByName("buttonMenu");
	if (oponent->numberOfArtefact == 10)
		scene->removeChildByName("moneyLabel");
}
void AllyHero::checkIfYuumi(Scene* scene)
{
	if (oponent->numberOfArtefact == 10)
	{
		int multiplier = UserDefault::getInstance()->getIntegerForKey("multiplier");
		if (multiplier == 0)
			multiplier = 1;
		srand(time(NULL));
		int moneyPrize = rand() % 20 + 20;
		moneyPrize *= multiplier;
		std::stringstream ss;
		ss << moneyPrize;
		int money = UserDefault::getInstance()->getIntegerForKey("money");
		money += moneyPrize;
		UserDefault::getInstance()->setIntegerForKey("money", money);
		auto moneyLabel = Label::createWithTTF("Your prize: " + ss.str(), "fonts/Marker Felt.ttf", 40.0f);
		moneyLabel->setPosition(Vec2(320, 550));
		moneyLabel->setName("moneyLabel");
		scene->addChild(moneyLabel, 2);
	}
}
void AllyHero::unlockLevel(int numberOfLevel)
{
	std::stringstream ss;
	ss << numberOfLevel;
	std::string key = "lvl" + ss.str() + "Unlocked";
	UserDefault::getInstance()->setBoolForKey(key.c_str(), true);
}
void AllyHero::unlockArtifact(int numberOfArtifact)
{
	std::stringstream ss;
	ss << numberOfArtifact;
	std::string key = "artifact" + ss.str();
	UserDefault::getInstance()->setStringForKey(key.c_str(), "clear");
}