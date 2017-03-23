//
//  GameSetting.hpp
//  paopaolong
//
//  Created by jiangxf on 16/9/17.
//
//

#ifndef GameSetting_hpp
#define GameSetting_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GameSetting
{
    
public:
    GameSetting():isSoundOn_(true)
    {
        int a = UserDefault::getInstance()->getIntegerForKey("sound", 0);
        if (1 == a) {
            isSoundOn_ = false;
        }
    }
public:
    
    static GameSetting* getInstance()
    {
        if (!instance_)
        {
            instance_ = new GameSetting;

            return instance_;
        }
        
        return instance_;
        
    }
    
    void setSound(bool val)
    {
        if (val)
        {
            UserDefault::getInstance()->setIntegerForKey("sound", 0);
        }
        else
        {
            UserDefault::getInstance()->setIntegerForKey("sound", 1);
        }
        isSoundOn_ = val;
    }
    
    bool getSound()
    {
        return isSoundOn_;
    }
public:
    
    static GameSetting* instance_;
    bool isSoundOn_;
};




#endif /* GameSetting_hpp */


