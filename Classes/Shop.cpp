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
	numberOfCategory = 0;
	cocos2d::log("numberOfPage: %d", numberOfPage);
	std::string heroString = shop_products[numberOfCategory][numberOfPage];
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
	addMoneyStatusToShopLayer();
	addButtons();
	runningScene->addChild(shopLayer);
}
void Shop::changeShopPage(int numberOfPage)
{
	shopMenu->removeChildByTag(20);
	std::string heroString = shop_products[numberOfCategory][numberOfPage];
	MenuItemSprite* background = MenuItemImage::create("shop/" + heroString + ".png", "shop/" + heroString + ".png");
	background->setTag(20);
	background->setEnabled(0);
	background->setPosition(Vec2(320, 630));
	shopMenu->addChild(background, -1);
}
void Shop::turnPageToRight()
{
	if ((numberOfPage == 6) || ((numberOfPage == 3) && (numberOfCategory == 1)))
		return;
	numberOfPage++;
	changeShopPage(numberOfPage);
}
void Shop::turnPageToLeft()
{
	if (numberOfPage == 0)
		return;
	numberOfPage--;
	changeShopPage(numberOfPage);
}
std::string const Shop::shop_products[2][7] = { { "ryze", "ashe" ,"garen", "twisted_fate", "elise", "katarina", "kaisa" }, {"2x", "3x", "4x", "5x"} };
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
	MenuItemImage* mltBtn = MenuItemImage::create("buttons/mltBtn.png", "buttons/mltBtn.png", CC_CALLBACK_0(Shop::changeCategory, this, 1));
	mltBtn->setPosition(Vec2(120, 985));
	shopMenu->addChild(mltBtn);
	shopMenu->addChild(buyButton);
	shopMenu->addChild(crossButton);
	shopMenu->addChild(rightArrow);
	shopMenu->addChild(leftArrow);
}
void Shop::closeShop()
{
	shopMenu->removeAllChildren();
	shopLayer->removeChildByName("moneyLabel");
}
void Shop::buyHero()
{
	removePreviousHero();
	if (money < costsOfProducts[numberOfCategory][numberOfPage])
	{
		addNoMoneyPopup();
		closeShop();
		return;
	}
	money -= costsOfProducts[numberOfCategory][numberOfPage];
	std::string moneyStr = generateMoneyStringFromInt(money);
	moneyLabel->setString(moneyStr);
	UserDefault::getInstance()->setIntegerForKey("money", money);
	if (numberOfCategory == 1)
	{
		buyMultiplier();
		closeShop();
		return;
	}
	boughtHeroSprite = Sprite::create("heroes/" + shop_products[numberOfCategory][numberOfPage] + "/bodySprite.png");
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
	money = UserDefault::getInstance()->getIntegerForKey("money");
	std::string moneyStr = generateMoneyStringFromInt(money);
	moneyLabel = Label::createWithTTF(moneyStr, "fonts/Marker Felt.ttf", 40.0f);
	moneyLabel->setPosition(Vec2(100, 880));
	moneyLabel->setName("moneyLabel");
	moneyLabel->setTextColor(Color4B::BLACK);
	shopLayer->addChild(moneyLabel);
}
std::string Shop::generateMoneyStringFromInt(int money)
{
	std::stringstream ss;
	ss << money << " X";
	return ss.str();
}
void Shop::addNoMoneyPopup()
{
	auto popup = Sprite::create("popups/popup.png");
	popup->setPosition(Vec2(320, 650));
	popup->setName("noMoneyPopup");
	auto btnOk = MenuItemImage::create("buttons/okBtn.png", "buttons/pressedOkBtn.png", CC_CALLBACK_0(Shop::removeNoMoneyPopup, this));
	auto btnMenu = Menu::create(btnOk, NULL);
	btnMenu->setName("buttonMenu");
	btnMenu->setName("btnMenu");
	btnOk->setPosition(Vec2(0, -250));
	shopLayer->addChild(btnMenu);
	shopLayer->addChild(popup);
}
void Shop::removeNoMoneyPopup()
{
	shopLayer->removeChildByName("noMoneyPopup");
	shopLayer->removeChildByName("btnMenu");
}
void Shop::changeCategory(int numberOfCategory)
{
	this->numberOfCategory = numberOfCategory;
	this->numberOfPage = -1;
	turnPageToRight();
}
void Shop::buyMultiplier()
{
	int multiplier;
	if (numberOfPage == 0)
		multiplier = 2;
	else if (numberOfPage == 1)
		multiplier = 3;
	else if (numberOfPage == 2)
		multiplier = 4;
	else if (numberOfPage == 3)
		multiplier = 5;
	UserDefault::getInstance()->setIntegerForKey("multiplier", multiplier);
}