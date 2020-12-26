#include <BrandLevel.h>
BrandLevel::BrandLevel(EnemyHero* enemy, Ryze* ally)
{
	this->allyHero = ally;
	this->enemyHero = enemy;
}
bool BrandLevel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->initHeroesHealth();
	this->addEssentialElements();
	this->addChild(enemyHero->sprite);
	this->enemyHero->sprite->setName("heroSprite");
	this->enemyHero->runWalkAnimate();
	this->schedule(SEL_SCHEDULE(&BrandLevel::updateSpellsCooldown), 0.1);
	return true;
}
void BrandLevel::initHeroesHealth()
{
	allyHeroHealth = allyHero->health;
	enemyHeroHealth = enemyHero->health;
}

Scene* BrandLevel::createSceneWithEnemyAndAllyHero(EnemyHero* enemy, Ryze* ally)
{
	auto scene = Scene::create();
	auto node = BrandLevel::create(enemy, ally);
	scene->addChild(node);
	node->setName("levelNode");
	return scene;
}
BrandLevel* BrandLevel::create(EnemyHero* enemy, Ryze* ally)
{
	auto scene = new BrandLevel(enemy, ally);
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
	else
	{
		delete scene;
		return nullptr;
	}
}
void BrandLevel::addEssentialElements()
{
	addBackground("backgrounds/firstSceneBG.png");
	addAllyHeroHpBar();
	addEnemyHeroHpBar();
	addHeroFace(allyHero->getName());
	addHud();
}
void BrandLevel::addBackground(std::string backgroundFilePath)
{
	auto background = Sprite::create(backgroundFilePath);
	background->setPosition(Vec2(320, 650));
	addChild(background);
}
void BrandLevel::addHeroFace(std::string nameOfHero)
{
	auto heroFace = Sprite::create("combatScene/" + nameOfHero + "Face.png");
	heroFace->setPosition(Vec2(74, 126));
	addChild(heroFace);
}
void BrandLevel::addHud()
{
	auto hud = Sprite::create("combatScene/hud.png");
	hud->setPosition(Vec2(320, 128));
	addChild(hud);
	addHeroSpells(allyHero->getName());
}
void BrandLevel::addHeroSpells(std::string nameOfHero)
{
	allyHero->spellOneIcon = MenuItemImage::create("combatScene/spells/" + nameOfHero + "Spell1.png", "combatScene/spells/" + nameOfHero + "Spell1.png", CC_CALLBACK_0(BrandLevel::castFirstAllyHeroSpell, this));
	//TBD correct filepath
	allyHero->spellTwoIcon = MenuItemImage::create("combatScene/spells/" + nameOfHero + "Spell2.png", "combatScene/spells/" + nameOfHero + "Spell2.png", CC_CALLBACK_0(BrandLevel::castSecondAllyHeroSpell, this));
	allyHero->spellOneIcon->setPosition(Vec2(-30, -436));
	allyHero->spellTwoIcon->setPosition(Vec2(+150, -436));
	allyHero->spellsMenu = Menu::create();
	allyHero->spellsMenu->addChild(allyHero->spellOneIcon);
	allyHero->spellsMenu->addChild(allyHero->spellTwoIcon);
	addChild(allyHero->spellsMenu);
}

void BrandLevel::updateSpellsCooldown(float dt)
{
	updateEnemyHeroFirstSpellCooldown(dt);
}
//TBD
void BrandLevel::addAllyHeroHpBar()
{
	addAllyHeroHpBorder();
	addAllyHeroHpLoadingBar();
	addAllyHeroHpLabel();
}
void BrandLevel::addEnemyHeroHpBar()
{
	addEnemyHeroHpBorder();
	addEnemyHeroHpLoadingBar();
	addEnemyHeroHpLabel();
}
void BrandLevel::addAllyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(360, 35));
	this->addChild(healthBarBorder, 2);
}
void BrandLevel::addEnemyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(320, 870));
	this->addChild(healthBarBorder, 2);
}
void BrandLevel::addAllyHeroHpLoadingBar()
{
	allyHeroHpBar = ui::LoadingBar::create("combatScene/health.png");
	allyHeroHpBar->setPosition(Vec2(360, 35));
	allyHeroHpBar->setPercent(100);
	this->addChild(allyHeroHpBar, 2);
}
void BrandLevel::addEnemyHeroHpLoadingBar()
{
	enemyHeroHpBar = ui::LoadingBar::create("combatScene/health.png");
	enemyHeroHpBar->setPosition(Vec2(320, 870));
	enemyHeroHpBar->setPercent(100);
	this->addChild(enemyHeroHpBar, 2);
}
void BrandLevel::addAllyHeroHpLabel()
{
	std::stringstream ss;
	ss << allyHeroHealth << "/" << allyHeroHealth;
	allyHero->hpLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 30.0f);
	allyHero->hpLabel->setPosition(Vec2(360, 35));
	allyHero->hpLabel->setTextColor(Color4B::BLACK);
	this->addChild(allyHero->hpLabel, 3);
}
void BrandLevel::addEnemyHeroHpLabel()
{
	std::stringstream ss;
	ss << enemyHeroHealth << "/" << enemyHeroHealth;
	enemyHero->hpLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 30.0f);
	enemyHero->hpLabel->setPosition(Vec2(320, 870));
	enemyHero->hpLabel->setTextColor(Color4B::BLACK);
	this->addChild(enemyHero->hpLabel, 3);
}
void BrandLevel::updateAllyHeroHpBar(short amountOfHp)
{
	std::stringstream ss;
	ss << amountOfHp << "/" << allyHeroHealth;
	std::string health = ss.str();
	allyHero->hpLabel->setString(health);
	double remainingHealthInPercent = ((double)amountOfHp / allyHeroHealth) * 100;
	allyHeroHpBar->setPercent(remainingHealthInPercent);
}
void BrandLevel::updateEnemyHeroHpBar(short amountOfHp)
{
	std::stringstream ss;
	ss << amountOfHp << "/" << enemyHeroHealth;
	std::string health = ss.str();
	enemyHero->hpLabel->setString(health);
	double remainingHealthInPercent = ((double)amountOfHp / enemyHeroHealth) * 100;
	enemyHeroHpBar->setPercent(remainingHealthInPercent);
}
void BrandLevel::dealDamageToAllyHero(short strength)
{
	allyHero->health -= strength;
	updateAllyHeroHpBar(allyHero->health);
	if (allyHero->health <= 0)
		finishBattleWithLose();
}
void BrandLevel::dealDamageToEnemyHero(short strength)
{
	enemyHero->health -= strength;
	updateEnemyHeroHpBar(enemyHero->health);
	if (enemyHero->health <= 0)
		finishBattleWithWin();
}
void BrandLevel::castFirstAllyHeroSpell()
{
	allyHero->castFirstSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel::dealDamageToEnemyHero, this, allyHero->strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(Ryze::runFirstSpellCooldown, allyHero));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(allyHero->timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
void BrandLevel::castSecondAllyHeroSpell()
{
	allyHero->castSecondSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel::dealDamageToEnemyHero, this, allyHero->strength));
	auto cooldownCallFunc = CallFunc::create(CC_CALLBACK_0(Ryze::runSecondSpellCooldown, allyHero));
	auto damageSequence = Sequence::create(cooldownCallFunc, DelayTime::create(allyHero->timeToDealDamageInSecondSpell), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
void BrandLevel::castFirstEnemyHeroSpell()
{
	enemyHero->castFirstSpell();
	auto damageCallFunc = CallFunc::create(CC_CALLBACK_0(BrandLevel::dealDamageToAllyHero, this, enemyHero->strength));
	auto damageSequence = Sequence::create(DelayTime::create(enemyHero->timeToDealDamageInFirstSpell), damageCallFunc, nullptr);
	this->runAction(damageSequence);
}
void BrandLevel::updateAllyHeroFirstSpellCooldown(float dt)
{

}
void BrandLevel::updateEnemyHeroFirstSpellCooldown(float dt)
{
	enemyHero->firstSpellCooldown -= dt;
	if (enemyHero->firstSpellCooldown <= 0)
	{
		castFirstEnemyHeroSpell();
		enemyHero->firstSpellCooldown = 5.0 + enemyHero->firstSpellAnimate->getDuration();
	}
}
void BrandLevel::finishBattleWithWin()
{
	stopRunningActions();
	showWinPopUp();
}
void BrandLevel::finishBattleWithLose()
{
	stopRunningActions();
	finishLevel();
}
void BrandLevel::finishLevel()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void BrandLevel::showWinPopUp()
{
	auto spritePopup = Sprite::create("popups/popup.png");
	spritePopup->setPosition(Vec2(320, 630));
	this->addChild(spritePopup, 4);
	auto okBtn = MenuItemImage::create("buttons/okBtn.png", "buttons/pressedOkBtn.png", CC_CALLBACK_0(BrandLevel::returnToGameScene, this));
	okBtn->setPosition(Vec2(0, -200));
	auto menu = Menu::create(okBtn, NULL);
	this->addChild(menu, 4);
}
void BrandLevel::showLosePopUp()
{

}
void BrandLevel::stopRunningActions()
{
	this->stopAllActions();
	this->unscheduleAllCallbacks();
}
void BrandLevel::prepareSceneToBeDeleted()
{
	this->removeAllChildrenWithCleanup(true);
}
void BrandLevel::returnToGameScene()
{
	prepareSceneToBeDeleted();
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}



