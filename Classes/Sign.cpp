

#include "Sign.h"
#include "UserData.h"
#define TTF_FONT_NAME  "FZDHTJW.TTF"
#include "NDKHelper.h"
#include "Tools.h"
#include "HelpScene.h"

Sign::Sign():
    m__pMenu(NULL)
    , m_contentPadding(0)
    , m_contentPaddingTop(0)
    , m_callbackListener(NULL)
    , m_callback(NULL)
    , m__sfBackGround(NULL)
    , m__s9BackGround(NULL)
    , m__ltContentText(NULL)
    , m__ltTitle(NULL)
	, level_(1)
{

}

Sign::~Sign()
{
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}

const int CLOSE_TAG = 10240;
const int GIFT1_TAG = 10241;
const int GIFT2_TAG = 10242;

const int RESH_BTN  = 10243;
const int ADD_BTN   = 10244;
const int CLR_BTN   = 10245;

const int RESH_PRICE = 15;
const int ADD_PRICE = 30;
const int CLR_PRICE = 10;

const float item1_pos_x = 200;
const float item2_pos_x = 350;
const float item3_pos_x = 500;

const float item1_pos_y = 500;
const float item2_pos_y = 500;
const float item3_pos_y = 500;



void Sign::createButton(const char * name, const int tag , float x, float y)
{
    auto refresh_button = MenuItemImage::create(name, name);
    refresh_button->setPosition(x, y);
    refresh_button->setCallback(CC_CALLBACK_1(Sign::buttonCallback,this));
    refresh_button->setTag(tag);
    getMenuButton()->addChild(refresh_button);

}

const int off_y = 440;
const int off_x = 155;

Vec2 Sign::getPosByDay(int i)
{
    i -= 1;
    
    int row  = i % 5;
    int line = i / 5;
    
    float x = row * 100  + off_x;
    float y = 1280 - line * 95 - off_y;
    
    return Vec2(x, y);
	
}


void Sign::showHadSigned()
{
    int day = TI()->getDay();
    for(int i = 1 ; i <= day; i++)
    {
        if(UserDefault::getInstance()->getIntegerForKey(saveString(i).c_str(),0) == 0)
        {
            continue;
        }
        
        Vec2 pos = getPosByDay(i);
        auto sp = Sprite::create("fit.png");
        
        sp->setPosition(pos);
    	addChild(sp,2);
        signCount_++;
    }
}


bool Sign::init()
{
    bool bRef = true;
    do
    {
        CC_BREAK_IF(!Layer::init());
        setContentSize(Size(720, 1280));
		
        Menu* menu = Menu::create();
        menu->setPosition(Vec2::ZERO);
        menu->setAnchorPoint(Vec2::ZERO);
        setMenuButton(menu);

        auto a = MenuItemImage::create("button_close.png", "button_close.png");
    	a->setCallback(CC_CALLBACK_1(Sign::buttonCallback,this));
        a->setTag(CLOSE_TAG);
        a->setPosition(670, 1280 - 320);
		getMenuButton()->addChild(a);
       
        showHadSigned();
        
	}
    while (0);
    
    registEvent();
    return bRef;
}

void Sign::registEvent()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true); // 不向下传递
    
    listener->onTouchBegan = CC_CALLBACK_2(Sign::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Sign::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(Sign::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


string Sign::saveString(int day)
{
	stringstream ss;
	ss.str("");

    struct tm *tm;
    time_t timep;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    time(&timep);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    timep = tv.tv_sec;
#endif
    
    tm = localtime(&timep);
    int year = tm->tm_year + 1900;//年
    int month = tm->tm_mon + 1;//月
   
	ss <<"sign"<< year << month << day;
	return ss.str();
}

bool Sign::todayYetGot()
{
    return !UserDefault::getInstance()->getIntegerForKey(saveString(TI()->getDay()).c_str(), 0);
}

void Sign::setGot()
{
    UserDefault::getInstance()->setIntegerForKey(saveString(TI()->getDay()).c_str(), 1);
}

void Sign::showGotItemAnim()
{
    auto sp = Sprite::create("gui/icon_sliver.png");
    addChild(sp, 3);
    sp->setPosition(TI()->getWidth()/2, TI()->getHeigh()/2);
    
    auto _moveto = MoveTo::create(0.3f, Vec2(TI()->getWidth()*0.9, TI()->getHeigh()*0.95));
    auto _fadein = FadeIn::create(0.2);
    auto _fadeout = FadeOut::create(0.2);
    auto _seq = Sequence::create(_fadein, _moveto, _fadeout, NULL);

    sp->runAction(_seq);

}

void Sign::giveItem()
{
    int ret = 0;
    
    if (signCount_ < 5)
    {
        ret = 5;
    }
    else
    {
        ret = 10;
    }
    
    if (signCount_ == 5)
    {
        ret += 50;
    }
    
    if (signCount_ == 10)
    {
        ret += 200;
    }
    
    if (signCount_ == 15)
    {
        ret += 300;
    }
    
    if (signCount_ == 20)
    {
        ret += 500;
    }
    
    USER()->addSliver(ret);
    
    auto s = HelpScene::scene();
    HelpScene* l = (HelpScene*)s->getChildByTag(3389);
    if (l!= nullptr)
    {
        l->showSliver();
    }
}

bool Sign::onTouchBegan(Touch *pTouch, Event *pEvent)
{

	return true;
}

void Sign::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void Sign::onTouchEnded(Touch *pTouch, Event *pEvent)
{

}
bool Sign::TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	log("Sign touch");
	return true;
}


Sign* Sign::create(const char *backgroundImage)
{
	Sign* ml = Sign::create();
	ml->setSpriteBackGround(Sprite::create(backgroundImage));
	ml->setSprite9BackGround(ui::Scale9Sprite::create(backgroundImage));
	return ml;
}


void Sign::setTitle(const char*title, int fontsize)
{
	auto ltfTitle = Label::createWithSystemFont(title, "Arial", fontsize);
	setLabelTitle(ltfTitle);
}

void Sign::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
	auto ltf = Label::createWithSystemFont(text, "Arial", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}


void Sign::setCallbackFunc(cocos2d::Ref *target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}


bool Sign::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

	// 创建图片菜单按钮
	auto menuImage = MenuItemImage::create(normalImage, selectedImage);
	menuImage->setCallback(CC_CALLBACK_1(Sign::buttonCallback,this));
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);

	// 添加文字说明并设置位置
    Size imenu = menuImage->getContentSize();
    auto ttf = Label::createWithSystemFont(title, "Arial", 20);
    ttf->setColor(Color3B(0, 0, 0));
    ttf->setPosition(Vec2(imenu.width / 2, imenu.height / 2));
    menuImage->addChild(ttf);

    getMenuButton()->addChild(menuImage);
    return true;
}
void Sign::showOpenBoxAnimi(int flag)
{
    auto a = ParticleSystemQuad::create("yanhua02.plist");
    a->setPosition(720/2, 1280 - 575);
    
    auto b = FadeOut::create(0.2);
    auto box1 = getMenuButton()->getChildByTag(GIFT1_TAG);
    auto box2 = getMenuButton()->getChildByTag(GIFT2_TAG);
    auto c = FadeOut::create(0.2);
    box1->runAction(b);
    box2->runAction(c);
    
    
    int ret = rand() % 2;
    
    Sprite* sp = nullptr;
    if(ret == 0)
    {
        sp = Sprite::create("gui/item_move.png");
        UserData::getInstance()->addMoveItemNum(1);
    }
    
    if(ret == 1)
    {
        sp = Sprite::create("icon_sliver_box.png");
        UserData::getInstance()->addSliver(10);
    }
    
    addChild(sp);
    sp->setPosition(720/2, 1280 - 575);
    auto fi = FadeIn::create(0.5);
    sp->runAction(fi);
    addChild(a);
    
}
bool Sign::addButton(const char *normalImage, const char *selectedImage, Vec2 pos, int tag)
{
    // 创建图片菜单按钮
    auto menuImage = MenuItemImage::create(normalImage, selectedImage);
    menuImage->setCallback(CC_CALLBACK_1(Sign::buttonCallback, this));
    menuImage->setTag(tag);
    menuImage->setPosition(pos);
    
    getMenuButton()->addChild(menuImage);
    
    return true;
}



int Sign::getPrice(int itemId)
{
    switch (itemId)
    {
        case ADD_BTN:
            return ADD_PRICE;
        case RESH_BTN:
            return RESH_PRICE;
        case CLR_BTN:
            return CLR_PRICE;
        default:
            break;
    }
    return 100;
}

int Sign::getMoney()
{
    return UserData::getInstance()->getSliver();
}

bool Sign::subMoney(int a)
{
    if (a <= 0)
    {
        return false;
    }
    
    UserData::getInstance()->addSliver(-a);
    return true;
}

void Sign::addItem(int itemId)
{
    switch (itemId)
    {
        case ADD_BTN:
            UserData::getInstance()->addMoveItemNum(1);
            break;
        case RESH_BTN:
            UserData::getInstance()->addRefreshItemNum(1);
            break;
        case CLR_BTN:
            UserData::getInstance()->addcolorItemNum(1);
        default:
            break;
    }
}



void Sign::showGotItemAnim(int itemId)
{
    
    Vec2 pos;
    switch (itemId)
    {
        case ADD_BTN:
            pos = Vec2(item2_pos_x,item2_pos_y) - Vec2(0, 50);
            break;
        case RESH_BTN:
            pos = Vec2(item1_pos_x,item1_pos_y) - Vec2(0, 50);
            break;
        case CLR_BTN:
            pos = Vec2(item3_pos_x, item3_pos_y) - Vec2(0, 50);
            break;
        default:
            break;
    }
    auto sp = Sprite::create("fit.png");
    sp->setPosition(pos);
    addChild(sp, 100);
    auto fi = FadeIn::create(0.5f);
    sp->runAction(fi);
}

void Sign::buyItem(int itemId)
{
    auto price = getPrice(itemId);
    if (getMoney() < price)
    {
        return;
    }
   
    if(subMoney(price) == false )
    {
        return;
    }
    
    addItem(itemId);
    
    showGotItemAnim(itemId);
}

void Sign::buttonCallback(cocos2d::Ref *pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    
    if (12347 == node->getTag())
    {
        if(todayYetGot())
        {
            setGot();
            showGotItemAnim();
            giveItem();
            showHadSigned();
            return;
        }
        
    }
    
    if (m_callback && m_callbackListener)
    {
        node->setUserData((void*)&level_);
        (m_callbackListener->*m_callback)(node);
    }
    
    removeFromParentAndCleanup(true);
}


void Sign::onEnter()
{
    Layer::onEnter();

    Size winSize = Director::getInstance()->getWinSize();
    Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

    Size contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(Size::ZERO))
    {
        getSpriteBackGround()->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    }
    else
    {
        ui::Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        this->addChild(background, 0);
        contentSize = getContentSize();
    }


    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());

    Vector < Node* > array = getMenuButton()->getChildren();
    // 显示对话框标题
    if (getLabelTitle())
    {
        getLabelTitle()->setPosition(Vec2(pCenter) + Vec2(0, contentSize.height / 2 -300));
        getLabelTitle()->setColor(Color3B(255,10,10));
        getLabelTitle()->enableOutline(Color4B(0,0,0,255), 1);
        
        addChild(getLabelTitle());
    }

    // 显示文本内容
    if (getLabelContentText())
    {
        auto ltf = getLabelContentText();
        ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
 
        ltf->setHorizontalAlignment(TextHAlignment::LEFT);
        this->addChild(ltf);
    }

    Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
                           ScaleTo::create(0.06, 1.05),
                           ScaleTo::create(0.08, 0.95),
                           ScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupLayer);

}


void Sign::onExit()
{
    log("popup on exit.");
    Layer::onExit();
}
