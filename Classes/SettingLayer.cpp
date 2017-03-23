#include "SettingLayer.h"
#include "StartScene.h"
#include "AppDelegate.h"
#include "Defines.h"

using namespace cocos2d;
using namespace CocosDenshion;

SettingLayer::SettingLayer()
:m_pBgInfoScreen(NULL)
,m_pSelected(NULL)
{
	
}
SettingLayer::~SettingLayer()
{
	CC_SAFE_RELEASE_NULL(m_pBgInfoScreen);
	CC_SAFE_RELEASE_NULL(m_pSelected);
}

// on "init" you need to initialize your instance
bool SettingLayer::init()
{
    bool bRet = false;
//     do 
//     {
//         CC_BREAK_IF(! Layer::init());
// 
// 		this->setTouchEnabled(true);
// 
// 		Size winSize = Director::getInstance()->getWinSize();
// 
// 		m_pBgInfoScreen = Sprite::create("images/mainmenu/720x_port_hdpi/bg_info_screen.png");
// 		CC_BREAK_IF(! m_pBgInfoScreen);
// 		m_pBgInfoScreen->retain();
// 		m_pBgInfoScreen->setPosition(Vec2(400,620));
// 		this->addChild(m_pBgInfoScreen);
// 
// 		m_nBgSize = m_pBgInfoScreen->getContentSize();
// 
// 		//创建"OK"按钮
// 		MenuItemImage *pOkItem = MenuItemImage::create(
// 			"images/mainmenu/720x_port_hdpi/btn_request.png",
// 			"images/mainmenu/720x_port_hdpi/btn_request.png",
// 			this,
// 			menu_selector(SettingLayer::menuCallback));
//         CC_BREAK_IF(! pOkItem);
// 		pOkItem->setTag(101);
// 		pOkItem->setPosition(Vec2(m_nBgSize.width/2, m_nBgSize.height/5));
// 
// 		Size okSize = pOkItem->getContentSize();
// 
// 		LabelTTF* pOkLabel = LabelTTF::create("OK","fonts/Verdana Bold.ttf",45);
// 		CC_BREAK_IF(! pOkLabel);
// 		pOkLabel->setPosition(Vec2(okSize.width/2, okSize.height/2));
// 		pOkItem->addChild(pOkLabel);
// 
// 		//-------------创建背景音乐开关按钮-----------------//
// 		LabelTTF* pMusicLabel = LabelTTF::create("Music","fonts/Verdana Bold.ttf",40);
// 		CC_BREAK_IF(! pMusicLabel);
// 		pMusicLabel->setColor(ccc3(0,255,255));
// 		pMusicLabel->setPosition(Vec2(m_nBgSize.width/4, m_nBgSize.height*39/70));
// 		m_pBgInfoScreen->addChild(pMusicLabel);
// 
// 		//读取保存的数据
// 		bool isMusicEnabled = UserDefault::getInstance()->getBoolForKey("isMusicEnabled");
// 		__String *fileName0 = __String::createWithFormat("images/mainmenu/720x_port_hdpi/button_trigger_%s.png",
// 			(isMusicEnabled ? "on" : "off"));
// 
// 		Sprite *pMusic = Sprite::create(fileName0->getCString());
//         CC_BREAK_IF(! pMusic);
// 		pMusic->setTag(102);
// 		pMusic->setPosition(Vec2(m_nBgSize.width/4, m_nBgSize.height*29/70));
// 		m_pBgInfoScreen->addChild(pMusic);
// 		//-------------创建背景音乐开关按钮-END----------------//
// 
// 		//--------------创建音效开关按钮-------------//
// 		LabelTTF* pEffectLabel = LabelTTF::create("Effect","fonts/Verdana Bold.ttf",40);
// 		CC_BREAK_IF(! pEffectLabel);
// 		pEffectLabel->setColor(ccc3(0,255,255));
// 		pEffectLabel->setPosition(Vec2(m_nBgSize.width*3/4, m_nBgSize.height*39/70));
// 		m_pBgInfoScreen->addChild(pEffectLabel);
// 
// 		bool isEffectEnabled = UserDefault::getInstance()->getBoolForKey("isEffectEnabled");
// 		__String *fileName1 = __String::createWithFormat("images/mainmenu/720x_port_hdpi/button_trigger_%s.png",
// 			(isEffectEnabled ? "on" : "off"));
// 
// 		Sprite *pEffect = Sprite::create(fileName1->getCString());
//         CC_BREAK_IF(! pEffect);
// 		pEffect->setTag(103);
// 		pEffect->setPosition(Vec2(m_nBgSize.width*3/4, m_nBgSize.height*29/70));
// 		m_pBgInfoScreen->addChild(pEffect);
// 		//--------------创建音效开关按钮-END------------//
// 
//         Menu *pMenu = Menu::create(pOkItem, NULL);
//         CC_BREAK_IF(! pMenu);
// 		pMenu->setPosition(Vec2::ZERO);
// 
//         m_pBgInfoScreen->addChild(pMenu);
// 		
// 		//-------------创建设置框里的难度调节功能----------------//
// 		Sprite *pLevel = Sprite::create("images/mainmenu/720x_port_hdpi/bg_small.png");
// 		CC_BREAK_IF(! pLevel);
// 		pLevel->setTag(104);
// 		pLevel->setPosition(Vec2(m_nBgSize.width/2, m_nBgSize.height*5/7));
// 		m_pBgInfoScreen->addChild(pLevel);
// 
// 		Size levelSize = pLevel->getContentSize();
// 
// 		LabelTTF* pSimpleLable = LabelTTF::create("Simple","fonts/Verdana Bold.ttf",35);
// 		CC_BREAK_IF(! pSimpleLable);
// 		pSimpleLable->setColor(ccc3(255,0,0));
// 		pSimpleLable->setPosition(Vec2(m_nBgSize.width*1/4, m_nBgSize.height*6/7));
// 		m_pBgInfoScreen->addChild(pSimpleLable);
// 
// 		Sprite *pDiamond01 = Sprite::create("images/mainmenu/720x_port_hdpi/magicDiamond.png");
// 		CC_BREAK_IF(! pDiamond01);
// 		pDiamond01->setTag(201);
// 		pDiamond01->setPosition(Vec2(levelSize.width/5, levelSize.height/2));
// 		pLevel->addChild(pDiamond01);
// 
// 		LabelTTF* pNormalLable = LabelTTF::create("Normal","fonts/Verdana Bold.ttf",35);
// 		CC_BREAK_IF(! pNormalLable);
// 		pNormalLable->setColor(ccc3(228,0,0));
// 		pNormalLable->setPosition(Vec2(m_nBgSize.width/2, m_nBgSize.height*6/7));
// 		m_pBgInfoScreen->addChild(pNormalLable);
// 
// 		Sprite *pDiamond02 = Sprite::create("images/mainmenu/720x_port_hdpi/magicDiamond.png");
// 		CC_BREAK_IF(! pDiamond02);
// 		pDiamond02->setTag(202);
// 		pDiamond02->setPosition(Vec2(levelSize.width/2, levelSize.height/2));
// 		pLevel->addChild(pDiamond02);
// 
// 		LabelTTF* pHardLable = LabelTTF::create("Expert","fonts/Verdana Bold.ttf",35);
// 		CC_BREAK_IF(! pHardLable);
// 		pHardLable->setColor(ccc3(200,0,0));
// 		pHardLable->setPosition(Vec2(m_nBgSize.width*3/4, m_nBgSize.height*6/7));
// 		m_pBgInfoScreen->addChild(pHardLable);
// 
// 		Sprite *pDiamond03 = Sprite::create("images/mainmenu/720x_port_hdpi/magicDiamond.png");
// 		CC_BREAK_IF(! pDiamond03);
// 		pDiamond03->setTag(203);
// 		pDiamond03->setPosition(Vec2(levelSize.width*4/5, levelSize.height/2));
// 		pLevel->addChild(pDiamond03);
// 
// 		//int diamondCount = 3 + UserDefault::getInstance()->getIntegerForKey("level");
// 
// 		m_pSelected = Sprite::create("images/mainmenu/720x_port_hdpi/asklife_ico_check.png");
// 		CC_BREAK_IF(! m_pSelected);
// 		m_pSelected->retain();
// 		m_pSelected->setTag(210);
// 		switch(UserDefault::getInstance()->getIntegerForKey("level"))
// 		{
// 		case 0: m_pSelected->setPosition(Vec2(levelSize.width/5, levelSize.height/10)); break;
// 		case 1: m_pSelected->setPosition(Vec2(levelSize.width/2, levelSize.height/10)); break;
// 		case 2: m_pSelected->setPosition(Vec2(levelSize.width*4/5, levelSize.height/10)); break;
// 		default:
// 			UserDefault::getInstance()->setIntegerForKey("level", 1);
// 			m_pSelected->setPosition(Vec2(levelSize.width/4, levelSize.height/10));
// 			break;
// 		}
// 		pLevel->addChild(m_pSelected);
// 		//-------------创建设置框里的难度调节功能-END---------------//
// 
//         bRet = true;
//     } while (0);

    return bRet;
}


void SettingLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
// 	Vec2 location = pTouch->getLocationInView();
// 	location = Director::getInstance()->convertToGL(location);
// 
// 	//获取m_pBgInfoScreen贴图左下角坐标
// 	Vec2 bgPos = m_pBgInfoScreen->getPosition();
// 	bgPos = Vec2(bgPos.x-m_nBgSize.width/2, bgPos.y-m_nBgSize.height/2);
// 
// 	//设置背景音乐
// 	Sprite *p1 = (Sprite *)(m_pBgInfoScreen->getChildByTag(102));
// 	Vec2 pos1 = p1->getPosition(); //pos1是相对于m_pBgInfoScreen左下角的坐标
// 	Size size1 = p1->getContentSize();
// 	CCRect rect1 = CCRect((bgPos.x+pos1.x)-size1.width/2, (bgPos.y+pos1.y)-size1.height/2, size1.width, size1.height);
// 	
// 	if(rect1.containsPoint(location))
// 	{
// 		m_pBgInfoScreen->removeChildByTag(102,true);
// 
// 		if(UserDefault::getInstance()->getBoolForKey("isMusicEnabled"))
// 		{
// 			UserDefault::getInstance()->setBoolForKey("isMusicEnabled",false);
// 			p1 = Sprite::create("images/mainmenu/720x_port_hdpi/button_trigger_off.png");
// 		}
// 		else
// 		{
// 			UserDefault::getInstance()->setBoolForKey("isMusicEnabled",true);
// 			p1 = Sprite::create("images/mainmenu/720x_port_hdpi/button_trigger_on.png");
// 		}
// 		p1->setTag(102);
// 		p1->setPosition(Vec2(m_nBgSize.width/4, m_nBgSize.height*29/70));
// 		m_pBgInfoScreen->addChild(p1);
// 		
// 		return;
// 	}
// 
// 	//设置音效
// 	Sprite *p2 = (Sprite *)(m_pBgInfoScreen->getChildByTag(103));
// 	Vec2 pos2 = p2->getPosition();
// 	Size size2 = p2->getContentSize();
// 	CCRect rect2 = CCRect((bgPos.x+pos2.x)-size2.width/2, (bgPos.y+pos2.y)-size2.height/2, size2.width, size2.height);
// 	
// 	if(rect2.containsPoint(location))
// 	{
// 		m_pBgInfoScreen->removeChildByTag(103,true);
// 		
// 		if(UserDefault::getInstance()->getBoolForKey("isEffectEnabled"))
// 		{
// 			UserDefault::getInstance()->setBoolForKey("isEffectEnabled",false);
// 			p2 = Sprite::create("images/mainmenu/720x_port_hdpi/button_trigger_off.png");
// 		}
// 		else
// 		{
// 			UserDefault::getInstance()->setBoolForKey("isEffectEnabled",true);
// 			p2 = Sprite::create("images/mainmenu/720x_port_hdpi/button_trigger_on.png");
// 		}
// 		p2->setTag(103);
// 		p2->setPosition(Vec2(m_nBgSize.width*3/4, m_nBgSize.height*29/70));
// 		m_pBgInfoScreen->addChild(p2);
// 		
// 		return;
// 	}
// 	
// 	Sprite *p3 = (Sprite *)(m_pBgInfoScreen->getChildByTag(104));
// 	Vec2 levelPos = p3->getPosition();
// 	Size levelSize = p3->getContentSize();
// 	levelPos = Vec2(levelPos.x-levelSize.width/2, levelPos.y-levelSize.height/2);
// 
// 	//设置简单难度
// 	Sprite *p31 = (Sprite *)(p3->getChildByTag(201));
// 	Vec2 pos31 = p31->getPosition();
// 	Size size31 = p31->getContentSize();
// 	CCRect rect31 = CCRect(
// 		(bgPos.x+levelPos.x+pos31.x)-size31.width/2,
// 		(bgPos.y+levelPos.y+pos31.y)-size31.height/2,
// 		size31.width,
// 		size31.height);
// 	
// 	if(rect31.containsPoint(location))
// 	{
// 		m_pSelected->setPosition(Vec2(levelSize.width/5, levelSize.height/10));
// 		UserDefault::getInstance()->setIntegerForKey("level", 0);
// 		return;
// 	}
// 
// 	//设置普通难度
// 	Sprite *p32 = (Sprite *)(p3->getChildByTag(202));
// 	Vec2 pos32 = p32->getPosition();
// 	Size size32 = p32->getContentSize();
// 	CCRect rect32 = CCRect(
// 		(bgPos.x+levelPos.x+pos32.x)-size32.width/2,
// 		(bgPos.y+levelPos.y+pos32.y)-size32.height/2,
// 		size32.width,
// 		size32.height);
// 	
// 	if(rect32.containsPoint(location))
// 	{
// 		m_pSelected->setPosition(Vec2(levelSize.width/2, levelSize.height/10));
// 		UserDefault::getInstance()->setIntegerForKey("level", 1);
// 		return;
// 	}
// 
// 	//设置专家难度
// 	Sprite *p33 = (Sprite *)(p3->getChildByTag(203));
// 	Vec2 pos33 = p33->getPosition();
// 	Size size33 = p33->getContentSize();
// 	CCRect rect33 = CCRect(
// 		(bgPos.x+levelPos.x+pos33.x)-size33.width/2,
// 		(bgPos.y+levelPos.y+pos33.y)-size33.height/2,
// 		size33.width,
// 		size33.height);
// 	
// 	if(rect33.containsPoint(location))
// 	{
// 		m_pSelected->setPosition(Vec2(levelSize.width*4/5, levelSize.height/10));
// 		UserDefault::getInstance()->setIntegerForKey("level", 2);
// 		return;
// 	}
}

void SettingLayer::menuCallback(Ref* pSender)
{
// 	Node *p = (Node *)pSender;
// 	switch(p->getTag())
// 	{
// 	case 101: //OK
// 		if(UserDefault::getInstance()->getBoolForKey("isEffectEnabled", false))
// 			SimpleAudioEngine()->playEffect("sounds/Click.ogg");
// 		StartScene::isSetting = false;
// 		break;
// 	}
}

