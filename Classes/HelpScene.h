﻿//
//  HelpScene.h
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_HelpScene_h
#define xzdd_HelpScene_h

#include "cocos2d.h"





using namespace cocos2d;

class HelpScene : public Layer
{

    Sprite * bjSprite;
    
private:
	float y_begin;//触摸开始时y位置
	float y_batch_location_begin;//触摸开始时成就batch位置
	float y_end;//触摸结束时y位置
    float y_max;
    float y_min;
    
    float moveSpeed;            //移动速度    
    bool enableMove;            //允许自动移动
    float y_last;               //上一帧 y的位置
    
public:

	virtual bool init();
    virtual void onExit();
	static Scene* scene();
    Layer* helpLayer;

	virtual void menuBackCallback(Ref* pSender);
    virtual void lockBackCallback(Ref* pSender);

	CREATE_FUNC(HelpScene);
    
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
    void buttonCallback(Node *pNode);
    void undateState(float dt);
};


#endif
