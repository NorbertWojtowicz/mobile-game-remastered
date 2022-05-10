#include "Shop.h"
#include <sstream>

Shop* Shop::createShopLayer()
{
	Shop *shop = new Shop();
	MenuItemImage* table = MenuItemImage::create("shop/shop.png", "shop/shop.png", CC_CALLBACK_0(Shop::addShopMenuToLayer, shop));
	Menu* menu = Menu::create();
	menu->setPosition(Vec2(114, 220));
	menu->addChild(table);
	shop->money = UserDefault::getInstance()->getIntegerForKey("money");
	shop->shopIconsLayer->addChild(menu, 1);
	shop->addSignToLayer();
	return shop;
}
void Shop::addSignToLayer()
{
	Sprite* sign = Sprite::create("other/sign.png");
	sign->setPosition(Vec2(114, 400));
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
	if ((numberOfPage == 6) || ((numberOfPage == 3) && (numberOfCategory == 1)) || ((numberOfPage == 2) && (numberOfCategory == 2)))
		return;
	numberOfPage++;
	changeShopPage(numberOfPage);
	if (isOwned())
	{
		buyButton->setNormalImage(Sprite::create("buttons/pickBtn.png"));
		buyButton->setDisabledImage(Sprite::create("buttons/pickBtn.png"));
		buyButton->setCallback(CC_CALLBACK_0(Shop::pickOwnedHero, this));
	}
	else
	{
		buyButton->setNormalImage(Sprite::create("buttons/buyBtn.png"));
		buyButton->setDisabledImage(Sprite::create("buttons/buyBtn.png"));
		buyButton->setCallback(CC_CALLBACK_0(Shop::buyHero, this));
	}
}
void Shop::turnPageToLeft()
{
	if (numberOfPage == 0)
		return;
	numberOfPage--;
	changeShopPage(numberOfPage);
	if (isOwned())
	{
		buyButton->setNormalImage(Sprite::create("buttons/pickBtn.png"));
		buyButton->setDisabledImage(Sprite::create("buttons/pickBtn.png"));
		buyButton->setCallback(CC_CALLBACK_0(Shop::pickOwnedHero, this));
	}
	else
	{
		buyButton->setNormalImage(Sprite::create("buttons/buyBtn.png"));
		buyButton->setDisabledImage(Sprite::create("buttons/buyBtn.png"));
		buyButton->setCallback(CC_CALLBACK_0(Shop::buyHero, this));
	}
}
std::string const Shop::shop_products[3][7] = { { "ryze", "ashe" ,"garen", "twisted_fate", "elise", "katarina", "kaisa" }, {"2x", "3x", "4x", "5x"}, {"book", "talisman", "sword"} };
void Shop::addButtons()
{
	buyButton = MenuItemImage::create("buttons/buyBtn.png", "buttons/pressedBuyBtn.png", CC_CALLBACK_0(Shop::buyHero, this));
	buyButton->setPosition(Vec2(320, 200));
	MenuItemImage* crossButton = MenuItemImage::create("buttons/crossBtn.png", "buttons/crossBtn.png", CC_CALLBACK_0(Shop::closeShop, this));
	crossButton->setPosition(Vec2(530, 985));
	MenuItemImage* rightArrow = MenuItemImage::create("buttons/rArrow.png", "buttons/pressedrArrow.png", CC_CALLBACK_0(Shop::turnPageToRight, this));
	rightArrow->setPosition(Vec2(540, 630));
	MenuItemImage* leftArrow = MenuItemImage::create("buttons/lArrow.png", "buttons/pressedlArrow.png", CC_CALLBACK_0(Shop::turnPageToLeft, this));
	leftArrow->setPosition(Vec2(100, 630));
	MenuItemImage* mltBtn = MenuItemImage::create("buttons/mltBtn.png", "buttons/mltBtn.png", CC_CALLBACK_0(Shop::changeCategory, this, 1));
	mltBtn->setPosition(Vec2(255, 985));
	MenuItemImage* itemBtn = MenuItemImage::create("buttons/itemsBtn.png", "buttons/itemsBtn.png", CC_CALLBACK_0(Shop::changeCategory, this, 2));
	itemBtn->setPosition(Vec2(395, 985));
	MenuItemImage* heroBtn = MenuItemImage::create("buttons/heroesBtn.png", "buttons/heroesBtn.png", CC_CALLBACK_0(Shop::changeCategory, this, 0));
	heroBtn->setPosition(Vec2(120, 985));
	shopMenu->addChild(mltBtn);
	shopMenu->addChild(itemBtn);
	shopMenu->addChild(heroBtn);
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
	if ((isOwned()) && (numberOfCategory != 0))
	{
		addPopup("popups/ownedPopup.png");
		closeShop();
		return;
	}
	if(numberOfCategory == 0)
		removePreviousHero();
	if (money < costsOfProducts[numberOfCategory][numberOfPage])
	{
		addPopup("popups/noMoneyPopup.png");
		closeShop();
		return;
	}
	money -= costsOfProducts[numberOfCategory][numberOfPage];
	std::string moneyStr = generateMoneyStringFromInt(money);
	moneyLabel->setString(moneyStr);
	UserDefault::getInstance()->setIntegerForKey("money", money);
	if (numberOfCategory == 1)
	{
		UserDefault::getInstance()->setIntegerForKey(shop_products[numberOfCategory][numberOfPage].c_str(), 1);
		buyMultiplier();
		closeShop();
		return;
	}
	if (numberOfCategory == 2)
	{
		UserDefault::getInstance()->setIntegerForKey(shop_products[numberOfCategory][numberOfPage].c_str(), 1);
		buyItem();
		closeShop();
		return;
	}
	boughtHeroSprite = Sprite::create("heroes/" + shop_products[numberOfCategory][numberOfPage] + "/bodySprite.png");
	boughtHeroSprite->setTag(1212);
	boughtHeroSprite->setPosition(Vec2(320, 920));
	UserDefault::getInstance()->setIntegerForKey(shop_products[numberOfCategory][numberOfPage].c_str(), 1);
	Director::getInstance()->getRunningScene()->addChild(boughtHeroSprite);
	UserDefault::getInstance()->setIntegerForKey("allyHeroId", numberOfPage);
	closeShop();
}
void Shop::removePreviousHero()
{
	if (boughtHeroSprite)
		Director::getInstance()->getRunningScene()->removeChild(boughtHeroSprite);
	Director::getInstance()->getRunningScene()->getChildByName("gameNode")->removeChildByTag(1212);
}
void Shop::addMoneyStatusToShopLayer()
{
	money = UserDefault::getInstance()->getIntegerForKey("money");
	std::string moneyStr = generateMoneyStringFromInt(money);
	moneyLabel = Label::createWithTTF(moneyStr, "fonts/Marker Felt.ttf", 40.0f);
	moneyLabel->setPosition(Vec2(320, 340));
	moneyLabel->setName("moneyLabel");
	moneyLabel->setTextColor(Color4B::BLACK);
	shopLayer->addChild(moneyLabel);
}
std::string Shop::generateMoneyStringFromInt(int money)
{
	std::stringstream ss;
	ss << "Your coins: " <<  money;
	return ss.str();
}
void Shop::addPopup(std::string path)
{
	auto popup = Sprite::create(path);
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
	int multiplier = numberOfPage + 2;
	UserDefault::getInstance()->setIntegerForKey("multiplier", multiplier);
}
void Shop::buyItem()
{
	int attack = 0, health = 0;
	if (numberOfPage == 0)
	{
		attack = 1;
	}
	else if (numberOfPage == 1)
	{
		health = 5;
		health += UserDefault::getInstance()->getIntegerForKey("additionalHealth");
		UserDefault::getInstance()->setIntegerForKey("additionalHealth", health);
	}
	else if (numberOfPage == 2)
		attack = 2;
	if (attack > 0)
	{
		attack += UserDefault::getInstance()->getIntegerForKey("additionalAttack");
		UserDefault::getInstance()->setIntegerForKey("additionalAttack", attack);
	}
}
bool Shop::isOwned()
{
	if (UserDefault::getInstance()->getIntegerForKey(shop_products[numberOfCategory][numberOfPage].c_str()) == 1)
		return true;
	else
		return false;
}
void Shop::pickOwnedHero()
{
	if (numberOfCategory != 0)
		return;
	removePreviousHero();
	boughtHeroSprite = Sprite::create("heroes/" + shop_products[numberOfCategory][numberOfPage] + "/bodySprite.png");
	boughtHeroSprite->setTag(1212);
	boughtHeroSprite->setPosition(Vec2(320, 920));
	Director::getInstance()->getRunningScene()->addChild(boughtHeroSprite);
	UserDefault::getInstance()->setIntegerForKey("allyHeroId", numberOfPage);
	closeShop();
}