#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Defines.h"
#include "Diamond.h"
#include "AnimHelp.h"
#include "SpriteFrameAnimation.h"
#include "GameData.h"
#include "GatherLayer.h"
using namespace cocos2d;
using namespace std;



class InGameScene : public Layer
{
public:
	InGameScene();
	virtual ~InGameScene();
    
    virtual bool init();

    void initScoreTarget(TargetData &ret);


    static Scene* scene();

    CREATE_FUNC(InGameScene);
	
public:
	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    HEARTBEAT(InGameScene, showWinHeartbeat)
    int isObstacle(int i, int j);
    
private:
	virtual void update(float delta);

	void playJumpScore(int count);
	void playJumpScoreUpdate(float delta);

	void updatePaused(float delta);

	void updateTime(float delta);

	void addFirstDiamond();
	void addDiamond(float delta);


	bool handleSelectedDiamond();
	void removeSelectedDiamond();
	void addRemovedDiamond(float delta);

	void playDiamondExplosion(const CCPoint pos);
	void removeExplosionCallback(Node* sender);

	void playReadyGo();
	void readyCallback(Node* sender);
	void goCallback(Node* sender);

	void addEndCallback(Node *pSender);

	void menuPauseCallback(CCObject* pSender);

	void addFireballCallback();
	
	void addRemovedDiamondCallback(Node *pSender);
    
    int getDiamondType();
    void dealHp();
    void DrawLine();
    Vec2 getPositionByRowAndLine(int row, int line);

    bool isNearby(int line, int row, int _type);
    void drawBg();
    vector<Diamond* > getNearItem(int line, int row);
    void showTime();
    void showWin();
    void showFail();
    void bombPos(int line, int row);
    void bombAllBombs();
    void playMoveAnim(float dt);
    
    void moveCallback(Node *pSender);
    
    Vec2 getRandomPosition();
    float getAnimTime();
    void showMoveNumber();
    
    void setupTag(Diamond* _obj, int line, int row);
    
    void buttonCallback(Node* _obj);
    void playSound(string name);
    void initGatherLayer(TargetDataEx target);

    void updateGatherNumber(int num1, int num2, int num3);

    bool isGatherMode()
    {
        return (InGameScene::level % 2 != 0);
    }
    
    void updateGatherNumber();

  
    string getItemIconName(int type);
    void createItemDiamond(int count);
    void removedOneLine(int line);
    void removedOneRow(int _row);
    void removeOneColor(int type);
    void trigerItem();
    void doRefresh();
    
    string getImageName(int type);
    Vec2 getCreatePos(int i, int j);
    
    bool touchRefreshItem(Vec2 location);
    bool touchColorItem(Vec2 location);
    bool touchMoveItem(Vec2 location);
    
public:
    vector<Sequence* > animList_;
    vector<int > posList_;
	static bool isPaused;
	static unsigned int background;
	static unsigned int bomb;

	static void reset();

	static const unsigned int randomDrop[8];

	static unsigned int level; //难度级别
	static const char* strMode[3];
	static const unsigned int baseScore[3];
	static const unsigned int limitTime[3]; //一共三个级别，不同级别门槛时间
	static const unsigned int limitScore[3]; //一共三个级别，不同级别门槛分数
	static const unsigned int limitFireball[3];
	static const unsigned int limitCrazy[3];

private:
	
	Layer *m_pPause;

    const int m_nDiamondRowMax = 7;
    const int m_nDiamondLineMax = 9;
	
    int m_nDiamondRow, m_nDiamondLine; //addDiamond(float ft)方法使用

	unsigned int m_nMagicCount;
	ProgressTimer *m_pMagicProgress;

	int m_nTempScore;
	int m_nScore;
	Label* m_pScoreLable; //记录给用户得分板的Label

	int m_nTime;
    
	Label* m_pMoveLable;
    Label* m_pTargetLable;
	
    Sprite* m_pTimerBar;
	bool m_bIsReadyGoEnd;

	__Array* m_pRemovedDiamond; //记录将要被删除的宝石指针

	SpriteBatchNode* m_pDiamondBatchNode; //所有宝石用BatchNode管理，避免帧率下降
	Diamond* m_pDiamond[9][7]; //记录各个位置宝石的指针

	
	bool m_bError;

	bool m_bFireballMode;
	int m_nFireballline, m_nFireballRow; //播放火球动画时使用

	unsigned int m_nTimeCount;
	unsigned int m_nCrazyCount;
	bool m_bIsCrazyMode;

	__Dictionary *m_pEffectDict;
    int m_startType; // 手放上去选择的第一个type
    int m_moveStatus;
    /**
     * 这局游戏可以移动的步数
     */
    int moves_number_;
    
    __Array *m_lineObjs;  // 存放画在屏幕上的线的数组
    Vec2 last_position;
    Vec2 cur_position;
    SpriteFrameAnimation* sf = nullptr;
    GatherLayer* gl_ = nullptr;
    Label * moveItemNum_ = nullptr;
    Label * refreshItemNum_ = nullptr;
    Label * colorItemNum_ = nullptr;
    Label * bombItemNum_ = nullptr;
    Label * digItemNum_ = nullptr;
    
    bool isRecsue_ = false;
    int egg_num_ = 0;

    void registEvent();
    
};

#define CREATE_LABEL(moveItemNum, x, y) do { moveItemNum##_ = Label::createWithCharMap("gui/white_font.png", 25, 29, '0'); \
moveItemNum##_->setString(TI()->_itos(UserData::getInstance()->get##moveItemNum())); \
moveItemNum##_->setPosition(x, y); \
moveItemNum##_->setScale(0.6); \
addChild(moveItemNum##_, 2000);} while(0)

#endif
