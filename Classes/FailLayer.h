#ifndef FAIL_LAYER_H_
#define FAIL_LAYER_H_

#include "cocos2d.h"
#include <iostream>
using namespace std;

USING_NS_CC;

class FailLayer: public Layer
{
public:


    CREATE_FUNC(FailLayer);
    
    virtual bool init();

    void setScore(int _score)
    {
        score_ = _score;
    }
    int getScore();

private:
    int score_;
};



#endif
