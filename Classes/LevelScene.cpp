#include <LevelScene.h>
LevelScene::LevelScene(EnemyHero* enemy, AllyHero* ally)
{
	this->allyHero = ally;
	this->enemyHero = enemy;
	this->enemyHero->initAllyHero(this->allyHero);
	this->allyHero->initEnemyHero(this->enemyHero);
}
bool LevelScene::init()
{
	if (!Node::init())
	{
		return false;
	}

	// Initialize health of selected heroes
	this->initHeroesHealth();

	// Add hero hp bars and hud
	this->addEssentialElements();
	this->addChild(enemyHero->sprite, 2);
	this->enemyHero->sprite->setName("heroSprite");

	// EnemyHero Animate
	this->enemyHero->runWalkAnimate();

	// Updating Spells Colldown - Interval 0.1s
	this->schedule(SEL_SCHEDULE(&LevelScene::updateSpellsCooldown), 0.1);
	return true;
}
void LevelScene::initHeroesHealth()
{
	allyHeroHealth = allyHero->health;
	enemyHeroHealth = enemyHero->health;
}
Scene* LevelScene::createSceneWithEnemyAndAllyHero(EnemyHero* enemy, AllyHero* ally)
{
	auto scene = Scene::create();
	auto node = LevelScene::create(enemy, ally);
	scene->addChild(node);
	node->setName("levelNode");
	return scene;
}
LevelScene* LevelScene::create(EnemyHero* enemy, AllyHero* ally)
{
	auto scene = new LevelScene(enemy, ally);
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
void LevelScene::addEssentialElements()
{
	addBackground("backgrounds/" + enemyHero->getName() + "Bg.png");
	addAllyHeroHpBar();
	addEnemyHeroHpBar();
	addHeroFace(allyHero->getName());
	addHud();
}
void LevelScene::addBackground(std::string backgroundFilePath)
{
	auto background = Sprite::create(backgroundFilePath);
	background->setPosition(Vec2(320, 568));
	addChild(background);
}
void LevelScene::addHeroFace(std::string nameOfHero)
{
	auto heroFace = Sprite::create("heroes/" + nameOfHero + "/" + nameOfHero + "Face.png");
	heroFace->setPosition(Vec2(61, 132));
	addChild(heroFace);
}
void LevelScene::addHud()
{
	auto hud = Sprite::create("combatScene/hud.png");
	hud->setPosition(Vec2(320, 128));
	addChild(hud);
	addHeroSpells(allyHero->getName());
}
void LevelScene::addHeroSpells(std::string nameOfHero)
{
	allyHero->spellOneIcon = MenuItemImage::create("heroes/" + nameOfHero + "/spells/first/" + nameOfHero + "Spell1.png", "heroes/" + nameOfHero + "/spells/first/" + nameOfHero + "Spell1.png", CC_CALLBACK_0(LevelScene::castFirstAllyHeroSpell, this));
	allyHero->spellTwoIcon = MenuItemImage::create("heroes/" + nameOfHero + "/spells/second/" + nameOfHero + "Spell2.png", "heroes/" + nameOfHero + "/spells/second/" + nameOfHero + "Spell2.png", CC_CALLBACK_0(LevelScene::castSecondAllyHeroSpell, this));
	allyHero->spellOneIcon->setPosition(Vec2(-30, -436));
	allyHero->spellTwoIcon->setPosition(Vec2(+150, -436));
	allyHero->spellsMenu = Menu::create();
	allyHero->spellsMenu->addChild(allyHero->spellOneIcon);
	allyHero->spellsMenu->addChild(allyHero->spellTwoIcon);
	addChild(allyHero->spellsMenu);
}

void LevelScene::updateSpellsCooldown(float dt)
{
	updateEnemyHeroFirstSpellCooldown(dt);
}
void LevelScene::addAllyHeroHpBar()
{
	addAllyHeroHpBorder();
	addAllyHeroHpLoadingBar();
	addAllyHeroHpLabel();
}
void LevelScene::addEnemyHeroHpBar()
{
	addEnemyHeroHpBorder();
	addEnemyHeroHpLoadingBar();
	addEnemyHeroHpLabel();
}
void LevelScene::addAllyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(360, 35));
	this->addChild(healthBarBorder, 2);
}
void LevelScene::addEnemyHeroHpBorder()
{
	auto healthBarBorder = Sprite::create("combatScene/healthBar.png");
	healthBarBorder->setPosition(Vec2(320, 920));
	this->addChild(healthBarBorder, 2);
}
void LevelScene::addAllyHeroHpLoadingBar()
{
	allyHero->hpBar = ui::LoadingBar::create("combatScene/health.png");
	allyHero->hpBar->setPosition(Vec2(360, 35));
	allyHero->hpBar->setPercent(100);
	this->addChild(allyHero->hpBar, 2);
}
void LevelScene::addEnemyHeroHpLoadingBar()
{
	enemyHero->hpBar = ui::LoadingBar::create("combatScene/health.png");
	enemyHero->hpBar->setPosition(Vec2(320, 920));
	enemyHero->hpBar->setPercent(100);
	enemyHero->hpBar->setName("enemyHpBar");
	this->addChild(enemyHero->hpBar, 2);
}
void LevelScene::addAllyHeroHpLabel()
{
	std::stringstream ss;
	ss << allyHeroHealth << "/" << allyHeroHealth;
	allyHero->hpLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 30.0f);
	allyHero->hpLabel->setPosition(Vec2(360, 35));
	allyHero->hpLabel->setTextColor(Color4B::WHITE);
	this->addChild(allyHero->hpLabel, 3);
}
void LevelScene::addEnemyHeroHpLabel()
{
	std::stringstream ss;
	ss << enemyHeroHealth << "/" << enemyHeroHealth;
	enemyHero->hpLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 30.0f);
	enemyHero->hpLabel->setPosition(Vec2(320, 920));
	enemyHero->hpLabel->setTextColor(Color4B::BLACK);
	this->addChild(enemyHero->hpLabel, 3);
}
void LevelScene::castFirstAllyHeroSpell()
{
	allyHero->castFirstSpell();
}
void LevelScene::castSecondAllyHeroSpell()
{
	allyHero->castSecondSpell();
}
void LevelScene::castFirstEnemyHeroSpell()
{
	enemyHero->castFirstSpell();
}
void LevelScene::updateEnemyHeroFirstSpellCooldown(float dt)
{
	enemyHero->firstSpellCooldown -= dt;
	if (enemyHero->firstSpellCooldown <= 0)
	{
		castFirstEnemyHeroSpell();
		enemyHero->firstSpellCooldown = 5.0 + enemyHero->firstSpellAnimate->getDuration();
	}
}




