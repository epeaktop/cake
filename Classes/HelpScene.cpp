﻿//  HelpScene.cpp
//  jiangxf @2017.03.23
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "HelpScene.h"
#include "SimpleAudioEngine.h"
#include "PopupLayer.h"
#include "UserData.h"
#include "Cover.h"
#include "Tools.h"
#include "Sign.h"

// #每个游戏都会不一样游戏场景头文件
#include "InGameScene.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

using namespace cocos2d;
using namespace CocosDenshion;
const int BT_OK = 12345;
const int BUY_HP_BUTTON = 12346;
const int SIGN_BUTTON = 12347;

const int NUMBER_LAYER = 5;
const float NUMBER_POS_Y = -20.0f;
const float NUMBER_POS_X = 35.0f;



Scene *HelpScene::scene()
{
    auto *scene = Scene::create();

    HelpScene *layer = HelpScene::create();
    layer->setTag(3389);
    scene->addChild(layer);

	
    return scene;
}

void HelpScene::showSliver()
{
    if (sliver_ == nullptr)
    {
        sliver_ = Sprite::create("gui/icon_sliver.png");
        addChild(sliver_, 5);
    }
    
    Size size = Director::getInstance()->getWinSize();
    sliver_->setPosition(size.width*0.9, size.height* 0.95);
    
    if (!sliverNumber_)
    {
        sliverNumber_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        sliver_->addChild(sliverNumber_);
        auto paopao = Sprite::create("gui/font_line.png");
        paopao->setPosition(sliver_->getPosition()-Vec2(0, 57));
        addChild(paopao, 4);
    }
    
    int i = UserData::getInstance()->getSliver();
    sliverNumber_->setString(TI()->_itos(i));
    sliverNumber_->setPosition(NUMBER_POS_X, NUMBER_POS_Y);
    
    //TI()->shakeNode(sliverNumber_);
}
void HelpScene::update(float delta)
{
    showSliver();
}

void HelpScene::showHp()
{
   if (hp_ == nullptr)
    {
        hp_ = Sprite::create("gui/icon_hp.png");
        addChild(hp_, NUMBER_LAYER);
    }
    
    hp_->setPosition(TI()->getWidth()*0.1, TI()->getHeigh()*0.95);
    
    if (hpNumber_ == nullptr)
    {
		hpNumber_ = Label::createWithSystemFont("", "Arial", 29);
        hp_->addChild(hpNumber_);
        auto paopao = Sprite::create("gui/font_line.png");
        paopao->setPosition(hp_->getPosition()-Vec2(0, 57));
        addChild(paopao, 4);
    }

    
    auto t = time(nullptr) -  UserData::getInstance()->getLastTime() ;
    int m = t/1800;
    if(m > 0)
    {
        USER()->setLastTime(time(nullptr));
    	UserData::getInstance()->addHp(m);
    }
    
    if (UserData::getInstance()->getHp() > 6)
    {
        UserData::getInstance()->setHp(6);
    }
    
    hpNumber_->setPosition(NUMBER_POS_X, NUMBER_POS_Y);
    hpNumber_->setString(TI()->_itos(UserData::getInstance()->getHp())+"/6");
    hpNumber_->enableShadow();
    TI()->shakeNode(hpNumber_);
    
}

void HelpScene::showQuit()
{
    if (quit_ == nullptr)
    {
        quit_ = Sprite::create("gui/icon_quit.png");
        addChild(quit_, NUMBER_LAYER);
    }
	quit_->setPosition(TI()->getWidth()* 0.9, TI()->getHeigh()* 0.8);
}

void HelpScene::showStar()
{
    if (star_ == nullptr)
    {
        star_ = Sprite::create("gui/icon_star.png");
        addChild(star_, NUMBER_LAYER);
    }
    
    star_->setPosition(TI()->getWidth()* 0.1, TI()->getHeigh()* 0.8);
    if(starNumber_ == nullptr)
    {
        starNumber_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        star_->addChild(starNumber_);
        auto paopao = Sprite::create("gui/font_line.png");
        paopao->setPosition(star_->getPosition()-Vec2(0, 57));
        addChild(paopao, 4);
    }
    
    starNumber_->setPosition(NUMBER_POS_X,NUMBER_POS_Y);
    starNumber_->setString(TI()->_itos(getStarNumbers()));
}

int HelpScene::getStarNumbers()
{
    return starNum_;
}

bool HelpScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    showSliver();
    showHp();
    showQuit();
    
    TextureCache::getInstance()->removeUnusedTextures();

    this->setKeypadEnabled(true);

    Size size = Director::getInstance()->getWinSize();
    bjSprite =  Sprite::create("map_1.png");

    bjSprite->setAnchorPoint(Vec2::ZERO);
    this->addChild(bjSprite, 1);

    auto charMap = Label::createWithCharMap("scoreNumber.png", 54, 64, '0');
    charMap->setPosition(Point(size. width/2,size.height*0.4));
  
    this->addChild(charMap,3);
    
    helpLayer = Layer::create();
    helpLayer->setAnchorPoint(Vec2::ZERO);
    helpLayer->setPosition(Vec2::ZERO);
    Vector<MenuItem*> itemArray;
 	

    for (int i = 1; i <= 500; i++)
    {
        MenuItemImage* item = nullptr;
        Sprite* sp = nullptr;
        if (i <= UserData::getInstance()->getLevel())
        {
            item = MenuItemImage::create("lv.png", "lv.png");
            item->setCallback(CC_CALLBACK_1(HelpScene::menuBackCallback,this));
            if (i == UserData::getInstance()->getLevel())
            {
                auto cur_sp = Sprite::create("cur_pos.png");
                cur_sp->setPosition(60, 160);
                item->addChild(cur_sp);
                auto moveto = MoveTo::create(0.3,Vec2(60,150));
                auto moveto2 = MoveTo::create(0.5,Vec2(60,180));
                auto m3 = MoveTo::create(0.5,Vec2(60,160));
                auto seq = Sequence::create(moveto,moveto2,m3, NULL);
                auto rf = RepeatForever::create(seq);
                cur_sp->runAction(rf);
                
                if (i > 12)
                {
                    int tmp = i;
                    int a = tmp % 12;
                    int b = tmp / 12;
                    helpLayer->setPosition(0, - (b * size.height) + (a * TI()->getHeigh())/12 - TI()->getHeigh()/2);
                }
            }
            else
            {
                int score = UserData::getInstance()->getScore(i);
                if (score < 10000 && i > 5)
                {
                    starNum_ += 1;
                    sp = Sprite::create("popup_star_bg1.png");
                }
                else if(score >= 10000 && score < 30000 && i > 5)
                {
                     starNum_ += 2;
                    sp = Sprite::create("popup_star_bg2.png");
                }
                else
                {
                     starNum_ += 3;
                    sp = Sprite::create("popup_star_bg3.png");
                }
            }
        }
        else
        {
            item = MenuItemImage::create("lock_lv.png", "lock_lv.png");
            item->setCallback(CC_CALLBACK_1(HelpScene::lockBackCallback,this));
        }
        
        item->setTag(i);
        itemArray.pushBack(item);
        
        auto charMap = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        charMap->setPosition(Vec2(60,90));
        charMap->setString(TI()->_itos(i));
        
        if(sp!=nullptr)
        {
        	sp->setPosition(60, 120);
        	item->addChild(sp);
        	sp->setScale(0.6, 0.6);
        }
        
        item->addChild(charMap);
        
        switch (i % 3)
        {
            case 0:
                item->setPosition(size.width/2, i * 100);
                break;
            case 1:
                item->setPosition(size.width/2 + 100, i * 100);
                break;
            case 2:
                item->setPosition(size.width/2 - 100, i * 100);
                break;
            default:
                break;
        }
        
    }
    
    auto menu_ = Menu::createWithArray(itemArray);
    menu_->setAnchorPoint(Vec2::ZERO);
    menu_->setPosition(Vec2::ZERO);
    helpLayer->addChild(menu_);
    helpLayer->setContentSize(Size(720,500*120));
    addChild(helpLayer,2);
    
    y_min = 0;
    y_max = size.height*10;

    this->setTouchEnabled(true);
    enableMove = false;
	
    schedule(schedule_selector(HelpScene::undateState));   //增加定时器调用
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(HelpScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelpScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelpScene::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    showStar();
    Sign* _sign = Sign::create("sign.png");
    if (_sign->todayYetGot())
    {
        _sign->setCallbackFunc(this, callfuncN_selector(HelpScene::buttonCallback));
        _sign->addButton("start_bt.png", "start_bt.png", Vec2(720/2, 260), SIGN_BUTTON);
        addChild(_sign, 2000);
    }
    
    scheduleUpdate();
    return true;
}

void HelpScene::onExit()
{
    Layer::onExit();
}

void HelpScene::menuBackCallback(Ref *pSender)
{
    auto obj = (MenuItemImage*)pSender;
    int level = obj->getTag();
    
    if (USER()->getHp() < 1)
    {
        PopupLayer *pl = PopupLayer::create("game_start.png");
        pl->setTitle("HP is not enough", 46);
        pl->setCallbackFunc(this, callfuncN_selector(HelpScene::buttonCallback));
        pl->addButton("buy_hp.png", "buy_hp.png", Vec2(720/2, 300), BUY_HP_BUTTON);
        this->addChild(pl, 2000);
        return;
    }
    
    PopupLayer *pl = PopupLayer::create("game_start.png");
    pl->setTitle("", 30);
    pl->setContentText("", 33, 80, 150);
    pl->setCallbackFunc(this, callfuncN_selector(HelpScene::buttonCallback));
    pl->level_ = level;
    pl->addButton("start_bt.png", "start_bt.png", Vec2(720/2, 300), BT_OK);
    UserData::getInstance()->setSelLevel(level);
    this->addChild(pl, 2000);
    
}

void HelpScene::lockBackCallback(Ref *pSender)
{
    
}
void HelpScene::buttonCallback(Node *pNode)
{
    if (BT_OK == pNode->getTag())
    {
        auto s = InGameScene::scene();
       
        auto transition = TransitionTurnOffTiles::create(0.5, s);
        
        Director::getInstance()->replaceScene(transition);
    }
    
    if (BUY_HP_BUTTON == pNode->getTag())
    {
        if (USER()->getSliver() < 3)
        {
            return;
        }
        
        USER()->addSliver(-3);
        USER()->setHp(6);
        showHp();
        showSliver();
    }
}

bool HelpScene::touchQuit(Vec2 v)
{
	Vec2 v1(TI()->getWidth()* 0.9 - 100, TI()->getHeigh()* 0.8 - 100);
	Vec2 v2(TI()->getWidth()* 0.9 + 100, TI()->getHeigh()* 0.8 + 100);
	return TI()->isInScope(v, v1, v2);
}
bool HelpScene::onTouchBegan(CCTouch *touch, CCEvent *event)
{
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
    y_begin = touchPoint.y;
    y_batch_location_begin = helpLayer->getPosition().y;
    enableMove = false;

	if (touchQuit(touchPoint))
	{
		Director::getInstance()->replaceScene(Cover::scene());
	}

    return true;
}

void HelpScene::onTouchEnded(CCTouch *touch, CCEvent *event)
{
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
    y_end = touchPoint.y;

    CCSize winSize = Director::sharedDirector()->getWinSize();

    ActionInterval  *actionTo;

    if (y_batch_location_begin + y_end - y_begin < y_min) //拉到最上面了
    {

    }
    else if (y_batch_location_begin + y_end - y_begin > y_min) //拉到最下面了
    {
        actionTo = MoveTo::create(0, CCPointMake(0, y_min));
        helpLayer->runAction(actionTo);
    }
    else  //中间
    {
        enableMove = true;
    }
}

void HelpScene::onTouchMoved(Touch *touch, Event *event)
{
    Vec2 touchPoint = touch->getLocationInView();
    touchPoint = Director::sharedDirector()->convertToGL(touchPoint);

    helpLayer->setPosition(ccp(0, y_batch_location_begin + touchPoint.y - y_begin));
}

//定时器，定时调用
void HelpScene::undateState(float dt)
{
    if (!enableMove)
    {
        moveSpeed = helpLayer->getPosition().y - y_last;
        y_last = helpLayer->getPosition().y;
    }
    else
    {
        moveSpeed = moveSpeed * 9 / 10;

        if (moveSpeed > 2 || moveSpeed < -2)
        {
            helpLayer->setPosition(ccpAdd(helpLayer->getPosition(), ccp(0, moveSpeed)));

            if (helpLayer->getPosition().y < y_min)
            {
                ActionInterval  *actionTo = MoveTo::create(0, CCPointMake(0, y_min));
                helpLayer->runAction(actionTo);
                enableMove = false;
            }
            else if (helpLayer->getPosition().y > y_max)
            {
                ActionInterval  *actionTo = MoveTo::create(0, CCPointMake(0, y_max));
                helpLayer->runAction(actionTo);
                enableMove = false;
            }
        }
    }
}


