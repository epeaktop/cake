#ifndef __gather_data_H__
#define __gather_data_H__


#include <cocos2d.h>
#include <iostream>
using namespace cocos2d;
using namespace std;

class GatherLayer : public Layer
{
public:
    GatherLayer(string name1, string name2, string name3, Vec2 pos1, Vec2 pos2, Vec2 pos3);
   

    //CREATE_FUNC(GatherLayer);
    virtual bool init();

    void setString(int num1, int num2, int num3);
    

private:
    Sprite* item1_ = nullptr;
    Sprite* item2_ = nullptr;
    Sprite* item3_ = nullptr;

    string name1_;
    string name2_;
    string name3_;

    Label* label1_ = nullptr;
    Label* label2_ = nullptr;
    Label* label3_ = nullptr;

    Vec2 pos1_;
    Vec2 pos2_;
    Vec2 pos3_;
};

#endif  // __HELLOWORLD_SCENE_H__
