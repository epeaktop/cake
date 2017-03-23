#include "ScoreScene.h"
#include "InGameScene.h"
//#include "LevelUpScene.h"
#include "AppDelegate.h"
#include "Defines.h"

using namespace cocos2d;
using namespace CocosDenshion;

const char* ScoreScene::m_pMedal[5] = {"bronce","bronce","silver","silver","gold"};

CCScene* ScoreScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ScoreScene *layer = ScoreScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
    bool bRet = false;
    do 
    {
		CC_BREAK_IF(! CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        //创建开始界面背景
		CCString *back0 = CCString::createWithFormat("backgrounds/BG%d-800x_port_mdpi.plist",InGameScene::background);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(back0->getCString());
		
		CCString *back1 = CCString::createWithFormat("BG%d.png",InGameScene::background);
		CCSprite* background = CCSprite::createWithSpriteFrameName(back1->getCString());
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//给用户评分，五星满分
		int lastScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("LastScore");
		int starNumber = -1;
		if(lastScore >= (int)(InGameScene::limitScore[InGameScene::level]))
		{
			int gap = lastScore - InGameScene::limitScore[InGameScene::level];
			int base = InGameScene::limitScore[InGameScene::level]/5;
			starNumber = gap/base;
			if(starNumber < 0) starNumber = 0;
			if(starNumber > 4) starNumber = 4;
		}

		//-------左上角金币栏-----------//
		/*CCSprite* btn_gold = CCSprite::create("images/mainmenu/720x_port_hdpi/btn_coin.png");
		btn_gold->setPosition(ccp(185,1180));
		this->addChild(btn_gold);

		CCSize goldSize = btn_gold->getContentSize();

		CCSprite* icon_bomb = CCSprite::create("images/mainmenu/720x_port_hdpi/icon_bomb_activ01.png");
		icon_bomb->setPosition(ccp(goldSize.width/5,goldSize.height/2));
		btn_gold->addChild(icon_bomb);

		CCLabelTTF* gold = CCLabelTTF::create(
			CCString::createWithFormat("%d",InGameScene::bomb)->getCString(),
			"fonts/Verdana Bold.ttf",40);
		gold->setPosition(ccp(goldSize.width*2/3,goldSize.height*55/100));
		btn_gold->addChild(gold);
		//-------左上角金币栏-----------//

		//--------右上角进度栏-------------//
		CCSprite* xpbar = CCSprite::create("images/mainmenu/720x_port_hdpi/xpbar.png");
		xpbar->setPosition(ccp(670,1180));
		this->addChild(xpbar);

		CCSize xpbarSize = xpbar->getContentSize();

		CCSprite* xp_bar_fill = CCSprite::create("images/mainmenu/720x_port_hdpi/xp_bar_fill.png");
		xp_bar_fill->setPosition(ccp(xpbarSize.width/4, xpbarSize.height*55/100));
		xpbar->addChild(xp_bar_fill);

		CCLabelTTF* progress = CCLabelTTF::create(
			CCString::createWithFormat("%d%%",25*3)->getCString(),
			"fonts/Verdana Bold.ttf",25);
		progress->setColor(ccc3(0,255,0));
		progress->setPosition(ccp(xpbarSize.width/2,xpbarSize.height/20*11));
		xpbar->addChild(progress);

		CCSprite* xp_bar_star = CCSprite::create("images/mainmenu/720x_port_hdpi/xp_bar_star.png");
		xp_bar_star->setPosition(ccp(-xpbarSize.width/5,xpbarSize.height/2));
		xpbar->addChild(xp_bar_star);

		CCLabelTTF* num = CCLabelTTF::create(
			CCString::createWithFormat("%d",12)->getCString(), //显示多少颗星星
			"fonts/Verdana Bold.ttf",35);
		num->setColor(ccc3(0,255,0));
		num->setPosition(ccp(-xpbarSize.width/5,xpbarSize.height/2));
		xpbar->addChild(num);
		//--------右上角进度栏-------------//

		//-----------偏上方长条栏，显示生命数量的心形-----------//
		CCSprite* heart_bar_bg = CCSprite::create("images/mainmenu/720x_port_hdpi/heart_bar_bg.png");
		heart_bar_bg->setPosition(ccp(400,1050));
		this->addChild(heart_bar_bg);

		CCSize heartSize = heart_bar_bg->getContentSize();

		for(int i = 0; i < 5; ++i)
		{
			CCSprite* heart_fill = CCSprite::create("images/mainmenu/720x_port_hdpi/heart_fill.png");
			heart_fill->setPosition(ccp(heartSize.width/660*65*(i+1)-heartSize.width/100,heartSize.height/2));
			heart_bar_bg->addChild(heart_fill);
		}*/
		//-----------偏上方长条栏，显示生命数量的心形-----------//

		//--------创建得分框----------//
		CCSprite* bgInfoScreen = CCSprite::create("images/mainmenu/720x_port_hdpi/bg_info_screen.png");
		bgInfoScreen->setPosition(ccp(400,720));
		bgInfoScreen->setTag(100); //设置得分框的tag
		this->addChild(bgInfoScreen);

		CCSize bgSize = bgInfoScreen->getContentSize();

		CCSprite* bg_score = CCSprite::create("images/mainmenu/720x_port_hdpi/bg_score.png");
		bg_score->setPosition(ccp(bgSize.width/2,bgSize.height*29/40));
		bgInfoScreen->addChild(bg_score);

		CCSprite* bg_small = CCSprite::create("images/mainmenu/720x_port_hdpi/bg_small.png");
		bg_small->setPosition(ccp(bgSize.width/2,bgSize.height*18/40));
		bgInfoScreen->addChild(bg_small);

		CCSprite* bg_small2 = CCSprite::create("images/mainmenu/720x_port_hdpi/bg_small.png");
		bg_small2->setPosition(ccp(bgSize.width/2,bgSize.height*12/40));
		bgInfoScreen->addChild(bg_small2);
		
		//CCLabelTTF* myScore = CCLabelTTF::create("Your Score","fonts/Verdana Bold.ttf",45);
		//myScore->setPosition(ccp(bgSize.width/2,bgSize.height*83/100));
		//bgInfoScreen->addChild(myScore);
		
		CCString* strLastScore = CCString::createWithFormat("Score:  %d",lastScore);
		CCLabelTTF* score = CCLabelTTF::create(strLastScore->getCString(),"fonts/Verdana Bold.ttf",45);
		score->setAnchorPoint(ccp(0,0.5));
		score->setPosition(ccp(bgSize.width/4-5,bgSize.height*83/100));
		bgInfoScreen->addChild(score);

		CCString *mode = CCString::createWithFormat("HighScore%d", InGameScene::level);
		int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(mode->getCString(),0);
		CCLabelTTF* score1 = CCLabelTTF::create(CCString::createWithFormat("Best:  %d",highScore)->getCString(),"fonts/Verdana Bold.ttf",45);
		score1->setAnchorPoint(ccp(0,0.5));
		score1->setPosition(ccp(bgSize.width/4-5,bgSize.height*73/100));
		bgInfoScreen->addChild(score1);

		CCSize bgScoreSize = bg_score->getContentSize();
		CCSprite* my_level = NULL;
		for(int i = 0; i < 5; ++i)
		{
			if(i <= starNumber && starNumber != -1)
				my_level = CCSprite::create("images/mainmenu/720x_port_hdpi/my_level.png");
			else
				my_level = CCSprite::create("images/mainmenu/720x_port_hdpi/my_level_black.png");
			my_level->setPosition(ccp(bgScoreSize.width*(i+1)/6,bgScoreSize.height/7));
			bg_score->addChild(my_level);
		}

		CCString *expression = NULL;
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isPass"))
			expression = CCString::create("images/mainmenu/720x_port_hdpi/visual_panda_thumbsup.png");
		else
			expression = CCString::create("images/mainmenu/720x_port_hdpi/visual_panda_crying.png");
		CCSprite* panda = CCSprite::create(expression->getCString());
		panda->setAnchorPoint(ccp(0,0));
		panda->setPosition(ccp(0,40));
		bgInfoScreen->addChild(panda);
		
		//显示得到的奖牌：金银铜
		if(starNumber > 0)
		{
			CCString *medalStr = CCString::createWithFormat("images/mainmenu/720x_port_hdpi/medal_%s_big.png",m_pMedal[starNumber]);
			CCSprite* medal_gold_big = CCSprite::create(medalStr->getCString());
			medal_gold_big->setPosition(ccp(bgSize.width/40*28,bgSize.height*15/40));
			bgInfoScreen->addChild(medal_gold_big);
		}
		//--------创建得分框结束----------//
		
		//---------创建"OK"按钮------------//
		CCMenuItemImage* pOkItem = CCMenuItemImage::create(
			"images/mainmenu/720x_port_hdpi/btn_play_ok.png",
			"images/mainmenu/720x_port_hdpi/btn_play_ok.png",
			this,
			menu_selector(ScoreScene::menuCallback));
        CC_BREAK_IF(! pOkItem);
		pOkItem->setTag(201); //设置"OK"按钮tag，回调时使用
		pOkItem->setPosition(ccp(400,180));

		CCSize okSize = pOkItem->getContentSize();

		CCLabelTTF* ok = CCLabelTTF::create("OK","fonts/Verdana Bold.ttf",70);
		ok->setPosition(ccp(okSize.width/2,okSize.height/2));
		pOkItem->addChild(ok);

        CCMenu* pMenu = CCMenu::create(pOkItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
		pMenu->setTag(101); //设置"OK"按钮父节点tag，删除时使用
        this->addChild(pMenu);
		//---------创建"OK"按钮------------//

        bRet = true;
    } while (0);

    return bRet;
}
/*
void ScoreScene::chartsCallback()
{
	this->removeChildByTag(100);
	this->removeChildByTag(101);

	CCSprite* bg_menu_list = CCSprite::create("images/mainmenu/720x_port_hdpi/bg_menu_list.png");
	bg_menu_list->setPosition(ccp(400,620));
	this->addChild(bg_menu_list);
	bg_menu_list->setScale(0.1f);
	bg_menu_list->runAction(CCScaleTo::create(0.5f,1.0f));

	CCSize size = bg_menu_list->getContentSize();

	CCSprite* bg_highscore_list = CCSprite::create("images/mainmenu/720x_port_hdpi/bg_highscore_list.png");
	bg_highscore_list->setPosition(ccp(size.width/2,size.height*44/100));
	bg_menu_list->addChild(bg_highscore_list);

	CCSprite* my_profile_placeholder = CCSprite::create("images/mainmenu/720x_port_hdpi/my_profile_placeholder.png");
	my_profile_placeholder->setPosition(ccp(size.width/7,size.height*91/100));
	bg_menu_list->addChild(my_profile_placeholder);
	
	CCString *highScoreInMode = CCString::createWithFormat("High Score in %s Mode", InGameScene::strMode[InGameScene::level]);
	CCLabelTTF* myHighScore = CCLabelTTF::create(highScoreInMode->getCString(),"fonts/Verdana Bold.ttf",25);
	myHighScore->setAnchorPoint(ccp(0,0.5));
	myHighScore->setPosition(ccp(size.width/4,size.height*95/100));
	bg_menu_list->addChild(myHighScore);

	CCString *mode = CCString::createWithFormat("HighScore%d", InGameScene::level);
	int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(mode->getCString(),0);
	CCLabelTTF* score = CCLabelTTF::create(CCString::createWithFormat("%d",highScore)->getCString(),"fonts/Verdana Bold.ttf",30);
	score->setAnchorPoint(ccp(0,0.5));
	score->setPosition(ccp(size.width/4,size.height*88/100));
	bg_menu_list->addChild(score);

	CCMenuItemImage* pPlayItem = CCMenuItemImage::create(
		"images/mainmenu/720x_port_hdpi/btn_play_ok.png",
		"images/mainmenu/720x_port_hdpi/btn_play_ok.png",
		this,
		menu_selector(ScoreScene::menuCallback));
	pPlayItem->setTag(202); //设置"Play"按钮tag，回调时使用
	pPlayItem->setPosition(ccp(400,150));

	CCSize playSize = pPlayItem->getContentSize();

	CCLabelTTF* pPlayLabel = CCLabelTTF::create("Play","fonts/Verdana Bold.ttf",70);
	pPlayLabel->setPosition(ccp(playSize.width/2, playSize.height/2));
	pPlayItem->addChild(pPlayLabel);

    CCMenu* pMenu = CCMenu::create(pPlayItem, NULL);
    pMenu->setPosition(CCPointZero);
	
    this->addChild(pMenu);
}
*/
void ScoreScene::menuCallback(CCObject* pSender)
{
	/*CCNode* p = (CCNode*)pSender;
	switch(p->getTag())
	{
	case 201: //"OK"
		{
			if(CCUserDefault::sharedUserDefault()->getBoolForKey("isEffectEnabled", false))
				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
			CCSprite* p = (CCSprite*)(this->getChildByTag(100));
			p->runAction(CCSequence::create(
				CCSplitRows::create(1.2f,30),
				CCCallFunc::create(this, callfunc_selector(ScoreScene::chartsCallback)),
				NULL));
			break;
		}
	case 202: //"Play"
		{*/
			if(CCUserDefault::sharedUserDefault()->getBoolForKey("isEffectEnabled", false))
				SimpleAudioEngine()->playEffect("sounds/Click.ogg");
			CCScene *pScene = InGameScene::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);
			//break;
		//}
	//}
}

