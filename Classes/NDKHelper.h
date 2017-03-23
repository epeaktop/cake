//
//  NDKHelper.h
//  jiangxf create on 2014.5.11
//

#ifndef __EasyNDK_for_cocos2dx__NDKHelper__
#define __EasyNDK_for_cocos2dx__NDKHelper__

#include <iostream>
#include "cocos2d.h"
#include <string>
#include <vector>
USING_NS_CC;
using namespace std;

extern "C"
{
    void callJava(string methodName, string methodParams);
}

#endif /* defined(__EasyNDK_for_cocos2dx__NDKHelper__) */
