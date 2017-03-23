

#include "FailLayer.h"
#include "HelpScene.h"
#include "UserData.h"


#define BUTTON_IMG "button.png"
#define BG_IMG "gui/game_fail.png"

string Number2String(int number)
{
    stringstream _ss;
    _ss.str("");
    _ss << number;
    return _ss.str();
}


bool FailLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    
    auto bg = Sprite::create(BG_IMG);
    addChild(bg);


    auto scoreLable = Label::createWithCharMap("gui/white_font.png", 25, 29, '0');
    scoreLable->retain();
    auto number = UserData::getInstance()->getScore();
    scoreLable->setString(Number2String(number));
    scoreLable->setPosition(Vec2(0, 200));
    addChild(scoreLable, 30000);
    
    auto moveItem = MenuItemImage::create(BUTTON_IMG, BUTTON_IMG,
        [this](Ref* obj)->void { 
            auto s = HelpScene::scene();
            auto t = TransitionFade::create(0.5, s);
            Director::getInstance()->replaceScene(t);
    });
    auto pQuitLabel = Label::create("Quit","fonts/Verdana Bold.ttf",45);
    pQuitLabel->setPosition(0, -100);
 	addChild(pQuitLabel,30000);
    moveItem->setPosition(0, -100);
    
    auto _menu = Menu::create(moveItem, NULL);
    
    _menu->setPosition(Vec2::ZERO);
    addChild(_menu, 200);

    return true;
}


