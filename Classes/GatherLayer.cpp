#include "GatherLayer.h"
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include "Tools.h"

using namespace std;

GatherLayer::GatherLayer(string name1, string name2, string name3, Vec2 pos1, Vec2 pos2, Vec2 pos3)
{
    name1_ = name1;
    name2_ = name2;
    name3_ = name3;

    pos1_ = pos1;
    pos2_ = pos2;
    pos3_ = pos3;
    init();
    autorelease();
}

bool GatherLayer::init()
{
    if (!Layer::init())
    {
        return false;

    }
    if (!item1_)
    {
        item1_ = Sprite::create(name1_);
        addChild(item1_);
    }   
    if (!item2_)
    {
        item2_ = Sprite::create(name2_);
        addChild(item2_);
    }    
    if (!item3_)
    {
        item3_ = Sprite::create(name3_);
        addChild(item3_);
    }

    if (!label1_)
    {
        label1_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        item1_->addChild(label1_);
    }
    
    if (!label2_)
    {
        label2_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        item2_->addChild(label2_);
    }

    if (!label3_)
    {
        label3_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
        item3_->addChild(label3_);
    }
	
    item1_->setPosition(pos1_);
    item2_->setPosition(pos2_);
    item3_->setPosition(pos3_);
    label1_->setPosition(50,10);
	label2_->setPosition(50,10);
    label3_->setPosition(50,10);
    return true;
}



void GatherLayer::setString(int num1, int num2, int num3)
{
    label1_->setString(TI()->_itos(num1));
    label2_->setString(TI()->_itos(num2));
    label3_->setString(TI()->_itos(num3));
}