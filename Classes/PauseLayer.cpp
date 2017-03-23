#include "PauseLayer.h"
#include "InGameScene.h"
#include "StartScene.h"
#include "AppDelegate.h"
#include "Defines.h"
#include "HelpScene.h"


using namespace cocos2d;
using namespace CocosDenshion;

// on "init" you need to initialize your instance
bool PauseLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		auto bgInfoScreen = Sprite::create("images/mainmenu/720x_port_hdpi/bg_info_screen.png");
		bgInfoScreen->setPosition(ccp(720/2,620));
		this->addChild(bgInfoScreen);
		bgInfoScreen->setTag(99);

		Size bgSize = bgInfoScreen->getContentSize();

		auto  pContinueItem = CCMenuItemImage::create(
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			this,
			menu_selector(PauseLayer::menuCallback));
        CC_BREAK_IF(! pContinueItem);
		pContinueItem->setTag(101);
		pContinueItem->setPosition(ccp(bgSize.width/2, bgSize.height*3/4));

		CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			this,
			menu_selector(PauseLayer::menuCallback));
        CC_BREAK_IF(! pRestartItem);
		pRestartItem->setTag(102);
		pRestartItem->setPosition(ccp(bgSize.width/2, bgSize.height*2/4));

		CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			"images/mainmenu/720x_port_hdpi/btn_request.png",
			this,
			menu_selector(PauseLayer::menuCallback));
        CC_BREAK_IF(! pQuitItem);
		pQuitItem->setTag(103);
		pQuitItem->setPosition(ccp(bgSize.width/2, bgSize.height*1/4));

        CCMenu* pMenu = CCMenu::create(pContinueItem, pRestartItem, pQuitItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
		pMenu->setTag(100);

        bgInfoScreen->addChild(pMenu);

		CCLabelTTF* pResumeLabel = CCLabelTTF::create("Resume","fonts/Verdana Bold.ttf",45);
		pResumeLabel->setPosition(ccp(bgSize.width/2, bgSize.height*3/4));
		bgInfoScreen->addChild(pResumeLabel);

		CCLabelTTF* pRestartLabel = CCLabelTTF::create("Restart","fonts/Verdana Bold.ttf",45);
		pRestartLabel->setPosition(ccp(bgSize.width/2, bgSize.height*2/4));
		bgInfoScreen->addChild(pRestartLabel);

		CCLabelTTF* pQuitLabel = CCLabelTTF::create("Quit","fonts/Verdana Bold.ttf",45);
		pQuitLabel->setPosition(ccp(bgSize.width/2, bgSize.height*1/4));
		bgInfoScreen->addChild(pQuitLabel);

		this->setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void PauseLayer::menuCallback(CCObject* pSender)
{
	CCNode* p = (CCNode*)pSender;

	switch(p->getTag())
	{
	case 101: //resume
		{
			if(CCUserDefault::sharedUserDefault()->getBoolForKey("isEffectEnabled", false))
				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
			
			InGameScene::isPaused = false;
		}
		break;

	case 102: //restart
		{
			if(CCUserDefault::sharedUserDefault()->getBoolForKey("isEffectEnabled", false))
				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
			CCScene *pScene = InGameScene::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		break;

	case 103: //quit to start
		{
			if(CCUserDefault::sharedUserDefault()->getBoolForKey("isEffectEnabled", false))
				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
            auto s = HelpScene::scene();
            auto t = TransitionFade::create(0.5, s);
            Director::getInstance()->replaceScene(t);
		}
		break;
	}
}

