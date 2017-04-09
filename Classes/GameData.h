#ifndef __game_data_H__
#define __game_data_H__

#define MAX_LEVEL 100

#include <iostream>
using namespace std;

struct TargetData
{
    int targetScore;
    int movesNum;
};

struct TargetDataEx
{
    int num1_;
    int num2_;
    int num3_;
    int num4_;
    int num5_;

    int movesNum;
};

struct ViewData
{
    string name1;
    string name2;
    string name3;
};



struct obsData
{
    int i;
    int j;
    int type;
};

struct AdditionData
{
    int i;
    int j;
    int type;
    int hp;
};

/**
 * 收集鸡蛋过关
 */
#define egg_number 100
/**
 * 打碎冰块过关
 */
#define ice_number 101


class GameData
{
public:
    TargetData getTarget(int level);
    TargetDataEx getTargetEx(int level);
    static GameData* getInstance();
 
    int isWin(int level);
    int isWin(int level, int score);
    
    ViewData getViewData(int level);
    string getObstacle(int level);
    vector<obsData> getObs(int level);
    string getAddi(int level);
    vector<AdditionData> getAddition(int level);

private:
    static GameData* instance_;

public:
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
};

#endif  // __HELLOWORLD_SCENE_H__
