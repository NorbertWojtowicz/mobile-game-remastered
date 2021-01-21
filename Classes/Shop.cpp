#include "Shop.h"
#include <sstream>

Shop* Shop::createShopLayer()
{
	Shop *shop = new Shop();
	MenuItemImage* table = MenuItemImage::create("shop/shop.png", "shop/shop.png", CC_CALLBACK_0(Shop::addShopMenuToLayer, shop));
	Menu* menu = Menu::create();
	menu->setPosition(Vec2(114, 750));
	menu->addChild(table);
	shop->money = UserDefault::getInstance()->getIntegerForKey("money");
	//this->shopLayer->setPosition(Vec2(114, 750));
	shop->shopIconsLayer->addChild(menu, 1);
	shop->addSignToLayer();
	shop->addMoneyStatusToShopLayer();
	return shop;
}
void Shop::addSignToLayer()
{
	Sprite* sign = Sprite::create("other/sign.png");
	sign->setPosition(Vec2(114, 900));
	this->shopIconsLayer->addChild(sign);
}
void Shop::addShopMenuToLayer()
{
	shopLayer = Node::create();
	numberOfPage = 0;
	cocos2d::log("numberOfPage: %d", numberOfPage);
	std::string heroString = hero_names[numberOfPage];
	auto runningScene = Director::getInstance()->getRunningScene();
	MenuItemSprite* background = MenuItemImage::create("shop/" + heroString + ".png", "shop/" + heroString + ".png");
	background->setTag(20);
	background->setPosition(Vec2(320, 630));
	background->setEnabled(0);
	//MenuItemImage* buyButton = MenuItemImage::create();
	shopMenu = Menu::create();
	shopMenu->setPosition(Vec2(0, 0));
	shopMenu->addChild(background, -1);
	shopMenu->setTag(21);
	shopLayer->addChild(shopMenu);
	addButtons();
	runningScene->addChild(shopLayer);
}
void Shop::changeShopPage(int numberOfPage)
{
	shopMenu->removeChildByTag(20);
	cocos2d::log("%d", numberOfPage);
	std::string heroString = hero_names[numberOfPage];
	MenuItemSprite* background = MenuItemImage::create("shop/" + heroString + ".png", "shop/" + heroString + ".png");
	background->setTag(20);
	background->setEnabled(0);
	background->setPosition(Vec2(320, 630));
	shopMenu->addChild(background, -1);
}
void Shop::turnPageToRight()
{
	if (numberOfPage == 6)
		return;
	numberOfPage++;
	cocos2d::log("numberOfPage incremented in turnPageToRigth function: %d", this->numberOfPage);
	changeShopPage(numberOfPage);
}
void Shop::turnPageToLeft()
{
	if (numberOfPage == 0)
		return;
	numberOfPage--;
	cocos2d::log("numberOfPage decremented in turnPageToRigth function: %d", this->numberOfPage);
	changeShopPage(numberOfPage);
}
std::string const Shop::hero_names[7] = { "ryze", "ashe" ,"garen", "twisted_fate", "elise", "katarina", "kaisa" };
void Shop::addButtons()
{
	MenuItemImage* buyButton = MenuItemImage::create("buttons/buyBtn.png", "buttons/pressedBuyBtn.png", CC_CALLBACK_0(Shop::buyHero, this));
	buyButton->setPosition(Vec2(320, 200));
	MenuItemImage* crossButton = MenuItemImage::create("buttons/cross.png", "buttons/cross.png", CC_CALLBACK_0(Shop::closeShop, this));
	crossButton->setPosition(Vec2(520, 880));
	MenuItemImage* rightArrow = MenuItemImage::create("buttons/rArrow.png", "buttons/pressedrArrow.png", CC_CALLBACK_0(Shop::turnPageToRight, this));
	rightArrow->setPosition(Vec2(540, 630));
	MenuItemImage* leftArrow = MenuItemImage::create("buttons/lArrow.png", "buttons/pressedlArrow.png", CC_CALLBACK_0(Shop::turnPageToLeft, this));
	leftArrow->setPosition(Vec2(100, 630));
	shopMenu->addChild(buyButton);
	shopMenu->addChild(crossButton);
	shopMenu->addChild(rightArrow);
	shopMenu->addChild(leftArrow);
}
void Shop::closeShop()
{
	shopMenu->removeAllChildren();
}
void Shop::buyHero()
{
	removePreviousHero();
	money -= costsOfHeroes[numberOfPage];
	std::string moneyStr = generateMoneyStringFromInt(money);
	moneyLabel->setString(moneyStr);
	UserDefault::getInstance()->setIntegerForKey("money", money);
	boughtHeroSprite = Sprite::create("heroes/" + hero_names[numberOfPage] + "/bodySprite.png");
	boughtHeroSprite->setTag(1212);
	boughtHeroSprite->setPosition(Vec2(320, 920));
	Director::getInstance()->getRunningScene()->addChild(boughtHeroSprite);
	UserDefault::getInstance()->setIntegerForKey("allyHeroId", numberOfPage);
	closeShop();
}
void Shop::removePreviousHero()
{
	if (boughtHeroSprite)
		Director::getInstance()->getRunningScene()->removeChild(boughtHeroSprite);
}
void Shop::addMoneyStatusToShopLayer()
{
	std::string moneyStr = generateMoneyStringFromInt(money);
	moneyLabel = Label::createWithTTF(moneyStr, "fonts/Marker Felt.ttf", 40.0f);
	moneyLabel->setPosition(Vec2(80, 1070));
	moneyLabel->setTextColor(Color4B::BLACK);
	shopIconsLayer->addChild(moneyLabel);
}
std::string Shop::generateMoneyStringFromInt(int money)
{
	std::stringstream ss;
	ss << money << "  X";
	return ss.str();
}
