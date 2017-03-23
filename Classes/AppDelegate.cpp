#include "AppDelegate.h"
#include "StartScene.h"
#include "Cover.h"
USING_NS_CC;
AppDelegate::AppDelegate()
{
}
AppDelegate::~AppDelegate()
{
}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}
bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview)
    {
        glview = GLViewImpl::create("fruitpop");
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(720 , 1280, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

    if (! UserDefault::getInstance()->getBoolForKey("isExisted"))
    {
        UserDefault::getInstance()->setBoolForKey("isExisted", true);
        UserDefault::getInstance()->setBoolForKey("isMusicEnabled", true);
        UserDefault::getInstance()->setBoolForKey("isEffectEnabled", true);
        UserDefault::getInstance()->setIntegerForKey("level", 1);
    }
#ifdef WIN32
   Scene *pScene = StartScene::scene();
   director->runWithScene(pScene);
#else
    auto scene = Cover::scene();
    director->runWithScene(scene);
#endif    
    return true;
}
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
