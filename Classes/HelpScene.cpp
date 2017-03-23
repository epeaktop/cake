//  HelpScene.cpp
//  jiangxf @2017.03.23
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "HelpScene.h"
#include "SimpleAudioEngine.h"
#include "PopupLayer.h"
#include "UserData.h"

// #每个游戏都会不一样游戏场景头文件
#include "InGameScene.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

using namespace cocos2d;
using namespace CocosDenshion;

Scene *HelpScene::scene()
{
    auto *scene = Scene::create();

    HelpScene *layer = HelpScene::create();

    scene->addChild(layer);


    return scene;
}

bool HelpScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    TextureCache::getInstance()->removeUnusedTextures();

    this->setKeypadEnabled(true);

    Size size = Director::getInstance()->getWinSize();
    bjSprite =  Sprite::create("map_1.png");

    bjSprite->setAnchorPoint(Vec2::ZERO);
    this->addChild(bjSprite, 1);

    auto charMap = Label::createWithCharMap("scoreNumber.png", 54, 64, '0');
    charMap->setPosition(Point(size.width/2,size.height*0.4));
  
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
                
                if (i > 9)
                {
                    float a = i/15;
                    helpLayer->setPosition(0, - (a * size.height));
                }
            }
            else
            {
                int score = UserData::getInstance()->getScore(i);
                if (score < 1000)
                {
                    sp = Sprite::create("popup_star_bg1.png");
                }
                else if(score >= 1000 && score < 3000)
                {
                    sp = Sprite::create("popup_star_bg2.png");
                }
                else
                {
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
        std::stringstream ss;
        ss.str("");
        ss << i;
        charMap->setString(ss.str());
        
        
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

    return true;
}

void HelpScene::onExit()
{
    Layer::onExit();
}

const int BT_OK = 12345;

void HelpScene::menuBackCallback(Ref *pSender)
{
    auto obj = (MenuItemImage*)pSender;
    int level = obj->getTag();
    log("menuBackCallback: = %d!~~", level);

    PopupLayer *pl = PopupLayer::create("game_start.png");
    pl->setContentSize(Size(720, 1280));
    pl->setTitle("", 30);
    pl->setContentText("", 33, 80, 150);
    pl->setCallbackFunc(this, callfuncN_selector(HelpScene::buttonCallback));
    pl->level_ = level;
    pl->addButton("start_bt.png", "start_bt.png", Vec2(720/2, 450), BT_OK);
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
}

bool HelpScene::onTouchBegan(CCTouch *touch, CCEvent *event)
{
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
    y_begin = touchPoint.y;
    y_batch_location_begin = helpLayer->getPosition().y;
    enableMove = false;
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


