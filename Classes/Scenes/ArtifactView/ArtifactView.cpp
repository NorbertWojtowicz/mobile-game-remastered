#include "Scenes/ArtifactView/ArtifactView.h"
#include <sstream>
#include "Scenes/GameScene/GameScene.h"
bool ArtifactView::init()
{
	if (!Node::init())
	{
		return false;
	}
	initScrollView();
	this->addChild(scrollView);
	return true;
}
void ArtifactView::initScrollView()
{
	auto scrollViewBackground = Sprite::create("backgrounds/artifactBg.png");
	scrollViewBackground->setPosition(Vec2(320, 1460));
	auto closeBtn = MenuItemImage::create("buttons/cross.png", "buttons/cross.png", CC_CALLBACK_0(ArtifactView::closeScene, this));
	closeBtn->setPosition(Vec2(240, 1250));
	auto menu = Menu::create(closeBtn, NULL);
	scrollView = ui::ScrollView::create();
	scrollView->setPosition(Vec2(0, 0));
	scrollView->addChild(menu, 2);
	scrollView->setInnerContainerSize(scrollViewBackground->getBoundingBox().size * 1.13);
	scrollView->setContentSize(scrollViewBackground->getContentSize());
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setScrollBarEnabled(0);
	scrollView->addChild(scrollViewBackground);
	addArtifactInscription();
	addArtifactsToScrollView();
}
void ArtifactView::addArtifactsToScrollView()
{
	checkArtifactStatuses();
	for (int i = 0; i < 7; i++)
	{
		int x = (i % 2 == 0) ? 160 : 480;
		int y;
		if (i < 2)
			y = 1400;
		else if ((i > 1) && (i <= 3))
			y = 1000;
		else if ((i > 3) && (i <= 5))
			y = 600;
		else if (i > 5)
			y = 200;
		auto artifactSprite = Sprite::create(artifactLocations[i]);
		artifactSprite->setPosition(Vec2(x, y));
		scrollView->addChild(artifactSprite);
	}
}
Scene* ArtifactView::createScene()
{
	auto scene = Scene::create();
	auto node = ArtifactView::create();
	scene->addChild(node);
	return scene;
}
void ArtifactView::checkArtifactStatuses()
{
	for (int i = 0; i < 7; i++)
	{
		std::stringstream ss;
		ss << i + 1;
		std::string num;
		ss >> num;
		std::string artifactKey = "artifact" + num;
		std::string artifactStatus = UserDefault::getInstance()->getStringForKey(artifactKey.c_str());
		artifactLocations[i] = "artefacts/a" + num + artifactStatus + ".png";
	}
}
void ArtifactView::addArtifactInscription()
{
	auto inscriptionSprite = Sprite::create("artefacts/artefactInscription.png");
	inscriptionSprite->setPosition(Vec2(320, 1730));
	scrollView->addChild(inscriptionSprite);
}
void ArtifactView::createNode()
{
	addChestToNode();
	addSignToNode();
}
void ArtifactView::addChestToNode()
{
	auto chest = MenuItemImage::create("artefacts/chest.png", "artefacts/chest.png", CC_CALLBACK_0(ArtifactView::runArtifactView, this));
	auto chestMenu = Menu::create(chest, NULL);
	this->node->addChild(chestMenu);
	chestMenu->setPosition(Vec2(320, 220));
}
void ArtifactView::addSignToNode()
{
	auto sign = Sprite::create("other/sign2.png");
	node->addChild(sign);
	sign->setPosition(Vec2(320, 400));
}
void ArtifactView::runArtifactView()
{
	auto scene = ArtifactView::createScene();
	Director::getInstance()->pushScene(scene);
}
ArtifactView* ArtifactView::createWithChest()
{
	ArtifactView* artifactView = new ArtifactView();
	artifactView->addChestToNode();
	artifactView->addSignToNode();
	return artifactView;
}
void ArtifactView::closeScene()
{
	this->removeAllChildren();
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}