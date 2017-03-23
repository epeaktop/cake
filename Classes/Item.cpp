#include "Item.h"
#include "cocos2d.h"
#include <sstream>

USING_NS_CC;

using namespace std;
string Item::getSaveName()
{
    stringstream _ss;
    _ss.str("");
    _ss << "item_num_" << id_;
    
    return _ss.str();
}

void Item::save()
{
    UserDefault::getInstance()->setIntegerForKey(getSaveName().c_str(), number_);
}

void Item::load()
{
    number_ = cocos2d::UserDefault::getInstance()->getIntegerForKey(getSaveName().c_str(), 0);
}










