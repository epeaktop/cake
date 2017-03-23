#include "AboutLayer.h"
#include "StartScene.h"
#include "AppDelegate.h"
#include "Defines.h"

using namespace cocos2d;
using namespace CocosDenshion;

// on "init" you need to initialize your instance
bool AboutLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! Layer::init());

		Size winSize = Director::getInstance()->getWinSize();

		Sprite* bgInfoScreen = Sprite::create("images/mainmenu/720x_port_hdpi/bg_info_screen.png");
		bgInfoScreen->setPosition(Vec2(400,620));
		this->addChild(bgInfoScreen);

		Size bgSize = bgInfoScreen->getContentSize();

		MenuItemImage *pQuitItem = MenuItemImage::create(
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			this,
			menu_selector(AboutLayer::menuCallback));
        CC_BREAK_IF(! pQuitItem);
		pQuitItem->setPosition(Vec2(bgSize.width/2, bgSize.height*1/4));

        Menu* pMenu = Menu::create(pQuitItem, NULL);
        pMenu->setPosition(Vec2::ZERO);
        CC_BREAK_IF(! pMenu);

        bgInfoScreen->addChild(pMenu);

		LabelTTF* pAboutLabel = LabelTTF::create("Author: Buvey Room\nQQ: 2399695400","fonts/Verdana Bold.ttf",36);
		pAboutLabel->setColor(ccc3(0,255,255));
		pAboutLabel->setPosition(Vec2(bgSize.width/2, bgSize.height*3/5));
		bgInfoScreen->addChild(pAboutLabel);

		LabelTTF* pOkLabel = LabelTTF::create("OK","fonts/Verdana Bold.ttf",45);
		pOkLabel->setPosition(Vec2(bgSize.width/2, bgSize.height*1/4));
		bgInfoScreen->addChild(pOkLabel);
		//------------------//

		this->setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void AboutLayer::menuCallback(Ref* pSender)
{
	if(UserDefault::getInstance()->getBoolForKey("isEffectEnabled", false))
		SimpleAudioEngine()->playEffect("sounds/Click.ogg");
	StartScene::isAbout = false;
}

