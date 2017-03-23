#include "Cover.h"
#include "NDKHelper.h"
#include "HelpScene.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

using  namespace std;

bool Cover::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();


    auto *game_bg = Sprite::create("cover-bg.png");
    game_bg->setPosition(Vec2(size.width / 2, size.height / 2));
    addChild(game_bg, -1);

    log("Cover::init");
    auto *new_button = MenuItemImage::create("new.png", "new.png", this, menu_selector(Cover::newCallback));

    new_button->setPosition(Vec2(size.width / 2 , size.height / 2));
    sound_ = MenuItemImage::create("sound.png", "sound.png", this, menu_selector(Cover::soundCallBack));
    sound2_ = MenuItemImage::create("no-sound.png", "no-sound.png", this, menu_selector(Cover::soundCallBack));
    sound_->setPosition(Vec2(74,1280-49));
    sound2_->setPosition(Vec2(74,1280-49));
    
    showSoundButton();
    
    Menu *pMenu = Menu::create(new_button,sound_, sound2_, NULL);
    pMenu->setPosition(Vec2::ZERO);
    
    addChild(pMenu, 100);


    return true;

}

void Cover::onExit()
{
    Layer::onExit();
    log("Cover::onExit");

}

void Cover::onEnter()
{
    Layer::onEnter();
    log("Cover::onEnter");
    callJava("showAds","");
}



void Cover::newCallback(Ref *pSender)
{
    callJava("showAds","");
    SimpleAudioEngine::getInstance()->playEffect("sounds/Click.ogg");
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    Director::getInstance()->pushScene(HelpScene::scene());
    
}
void Cover::exitCallback(Ref *pSender)
{
    log("exitCallback!");
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void Cover::resumeCallback(Ref *pSender)
{

}
#include "GameSetting.h"
void Cover::soundCallBack(Ref *pSender)
{
    if (isSoundOn_)
    {
        isSoundOn_ = false;
        GameSetting::getInstance()->setSound(false);
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        
    }
    else
    {
        isSoundOn_ = true;
        GameSetting::getInstance()->setSound(true);
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgm.mp3", true);
    }

    showSoundButton();

}

Scene *Cover::scene()
{
    Scene *scene = Scene::create();
    Cover *layer = Cover::create();
    scene->addChild(layer);

    return scene;
}

void Cover::showSoundButton()
{
    if (GameSetting::getInstance()->isSoundOn_)
    {
        sound_->setVisible(true);
        sound2_->setVisible(false);
    }
    else
    {
        sound2_->setVisible(true);
        sound_->setVisible(false);
    }
}

void Cover::showEffect(Point point, int cur_type_)
{
    
}

void Cover::update(float dt)
{

}
#pragma clang diagnostic pop



