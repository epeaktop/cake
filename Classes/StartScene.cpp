#include "StartScene.h"
#include "InGameScene.h"
#include "AppDelegate.h"
#include "Defines.h"

using namespace cocos2d;
//using namespace CocosDenshion;

bool StartScene::isSetting = false;
bool StartScene::isAbout = false;

StartScene::StartScene()
:m_pSetting(NULL)
,m_pAbout(NULL)
{
	
}

StartScene::~StartScene()
{
	//CC_SAFE_RELEASE_NULL(m_pSetting);
	//CC_SAFE_RELEASE_NULL(m_pAbout);
}

Scene* StartScene::scene()
{
    Scene * scene = NULL;
    do 
    {
        scene = Scene::create();
        CC_BREAK_IF(! scene);

        StartScene *layer = StartScene::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void StartScene::createStarAnimation(Vec2 pos, float delay)
{
//     Vector<SpriteFrame*> animationFrameStar;
// 	for(int i = 1; i < 20; ++i)
// 	{
// 		__String *fileName = __String::createWithFormat("star_ani%04d.png",i);
// 		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName->getCString());
//         animationFrameStar.pushBack(frame);
// 	}
// 	Animation* animationStar = Animation::createWithSpriteFrames(animationFrameStar,delay);
// 	Sprite* star = Sprite::createWithSpriteFrameName("star_ani0001.png");
// 	star->setPosition(pos);
// 	star->setScale(0.7f);
// 	star->runAction(RepeatForever::create(Animate::create(animationStar)));
// 	this->addChild(star);
}

bool StartScene::init()
{
    bool bRet = false;
    do 
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        CC_BREAK_IF(! Layer::init());
        auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

        label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);

// 		InGameScene::reset();
// 
// 		StartScene::isSetting = false;
// 		StartScene::isAbout = false;
// 
// 		Size winSize = Director::getInstance()->getWinSize();
// 
//         //创建开始界面背景
// 		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("backgrounds/BG1-800x_port_mdpi.plist");
// 		
// 		Sprite* pBG1 = Sprite::createWithSpriteFrameName("BG1.png");
// 		pBG1->setPosition(Vec2(winSize.width/2,winSize.height/2));
// 		this->addChild(pBG1);
// 
// 		//创建游戏logo "Diamond Dash"
// 		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/tutorialIntro/menu-720x_land_mdpi.plist");
// 
// 		Sprite* p03 = Sprite::createWithSpriteFrameName("dd_logo.png");
// 		p03->setPosition(Vec2(400,1050));
// 		this->addChild(p03);
// 
// 		//创建星星闪烁效果动画
// 		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/starAnimation-800x_port_mdpi.plist");
// 		createStarAnimation(Vec2(520,1170),0.13f);
// 		createStarAnimation(Vec2(400,1100),0.12f);
// 		createStarAnimation(Vec2(605,1000),0.125f);
// 		createStarAnimation(Vec2(355,880),0.15f);
// 		createStarAnimation(Vec2(255,940),0.135f);
// 		createStarAnimation(Vec2(75,1080),0.125f);
// 
// 		//创建开始界面中的熊猫
// 		float pandaX = 680, pandaY = 550;
// 		Sprite* pPanda = Sprite::createWithSpriteFrameName("panda.png");
// 		pPanda->setPosition(Vec2(pandaX,pandaY));
// 		this->addChild(pPanda);
// 
// 		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/pandaBlink-800x_port_mdpi.plist");
// 		//创建开始界面中的熊猫眨眼效果
// 		Sprite* pPandaEye = Sprite::createWithSpriteFrameName("panda_eye1.png");
// 		pPandaEye->setPosition(Vec2(pandaX-20,pandaY+130));
// 		this->addChild(pPandaEye);
// 		pPandaEye->runAction(RepeatForever::create(Sequence::create(
// 			CallFuncN::create(this, callfuncN_selector(StartScene::pandaCallback1)),
// 			DelayTime::create(2.5f),
// 			CallFuncN::create(this, callfuncN_selector(StartScene::pandaCallback2)),
// 			DelayTime::create(.1f),
// 			NULL)));
// 
// 		//放置"PLAY"按钮的气泡
// 		Sprite* pBubble = Sprite::createWithSpriteFrameName("speechbubble.png");
// 		pBubble->setPosition(Vec2(250,650));
// 		this->addChild(pBubble);
// 
// 		//创建"Play"按钮
// 		MenuItemImage *pPlayItem = MenuItemImage::create();
// 		pPlayItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btnPlay.png"));
// 		pPlayItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btnPlay.png"));
// 		pPlayItem->setTarget(this,menu_selector(StartScene::menuCallback));
//         CC_BREAK_IF(! pPlayItem);
// 		pPlayItem->setTag(101);  //设置"开始"按钮tag，回调时使用
// 		pPlayItem->setPosition(Vec2(223,647));
// 
// 		Size playSize = pPlayItem->getContentSize();
// 
// 		LabelTTF* pPlayLabel = LabelTTF::create("Play","fonts/Verdana Bold.ttf",60);
// 		pPlayLabel->setPosition(Vec2(playSize.width/2,playSize.height/2));
// 		pPlayItem->addChild(pPlayLabel);
// 
// 		MenuItemImage* pSettingItem = MenuItemImage::create(
// 			"images/mainmenu/720x_port_hdpi/btn_settings.png",
// 			"images/mainmenu/720x_port_hdpi/btn_settings.png",
// 			this,
// 			menu_selector(StartScene::menuCallback));
// 		pSettingItem->setTag(102);  //设置"设置"按钮tag，回调时使用
// 		pSettingItem->setPosition(Vec2(240, 150));
// 
// 		MenuItemImage* pAboutItem = MenuItemImage::create(
// 			"images/mainmenu/720x_port_hdpi/btn_credits.png",
// 			"images/mainmenu/720x_port_hdpi/btn_credits.png",
// 			this,
// 			menu_selector(StartScene::menuCallback));
// 		pAboutItem->setTag(103);  //设置"关于"按钮tag，回调时使用
// 		pAboutItem->setPosition(Vec2(560,150));
// 
// 		Menu* pMenu = Menu::create(pPlayItem, pSettingItem, pAboutItem, NULL);
// 		CC_BREAK_IF(! pMenu);
// 		pMenu->setPosition(Vec2::ZERO);
// 	
// 		this->addChild(pMenu);

        bRet = true;
    } while (0);

    return bRet;
}

void StartScene::pandaCallback1(Node *pSender)
{
	//((Sprite *)pSender)->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("panda_eye1.png"));
}
void StartScene::pandaCallback2(Node *pSender)
{
	//((Sprite *)pSender)->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("panda_eye2.png"));
}

void StartScene::updateSetting(float delta)
{
	//if(! StartScene::isSetting)
// 	{
// 		this->unschedule(schedule_selector(StartScene::updateSetting));
// 		this->removeChild(m_pSetting);
// 		CC_SAFE_RELEASE_NULL(m_pSetting);
// 	}
}

void StartScene::updateAbout(float delta)
{
// 	if(! StartScene::isAbout)
// 	{
// 		this->unschedule(schedule_selector(StartScene::updateAbout));
// 		this->removeChild(m_pAbout);
// 		CC_SAFE_RELEASE_NULL(m_pAbout);
// 	}
}

void StartScene::menuCallback(Ref* pSender)
{
// 	Node *p = (Node *)pSender;
// 
// 	switch(p->getTag())
// 	{
// 	case 101: //Play
// 		{
// 			if(UserDefault::getInstance()->getBoolForKey("isEffectEnabled", false))
// 				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
// 			Scene *pScene = InGameScene::scene();
// 			Director::getInstance()->replaceScene(pScene);
// 		}
// 		break;
// 	case 102: //Setting
// 		{
// 			if(UserDefault::getInstance()->getBoolForKey("isEffectEnabled", false))
// 				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
// 			StartScene::isSetting = true;
// 			this->schedule(schedule_selector(StartScene::updateSetting));
// 			m_pSetting = SettingLayer::create();
// 			m_pSetting->retain();
// 			this->addChild(m_pSetting);
// 		}
// 		break;
// 	case 103: //About
// 		{
// 			if(UserDefault::getInstance()->getBoolForKey("isEffectEnabled", false))
// 				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
// 			StartScene::isAbout = true;
// 			this->schedule(schedule_selector(StartScene::updateAbout));
// 			m_pAbout = AboutLayer::create();
// 			m_pAbout->retain();
// 			this->addChild(m_pAbout);
// 		}
// 		break;
// 	}
}

