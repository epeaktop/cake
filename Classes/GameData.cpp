#include "GameData.h"
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include "Tools.h"



using namespace std;

GameData* GameData::instance_ = nullptr;

int tagets[] = {
    1000, 2000, 3000, 3500, 4000,
    4500, 5000, 5500, 6000, 15000,// 10
    16000, 17000, 18000, 19000, 20000,
    21000, 22000, 23000, 24000, 25000, //20
    26000, 27000, 28000, 29000, 30000,
    31000, 32000, 33000, 33000, 34000,// 30
    35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 32000, // 40
   35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 32000,// 50
    35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 32000, // 60
    35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 32000, // 70
    35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 32000, // 80
    35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 32000, // 90
    35000, 36000, 37000, 32000, 32000,
    35000, 36000, 37000, 32000, 42000, // 100

};

int moves[] = {
    5, 15, 15, 20, 30,
    30, 35, 30, 30, 40, // 10
    30, 35, 30, 30, 40,
    30, 35, 30, 30, 40, // 20
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 50,  //30
    30, 35, 30, 30, 45,
    30, 35, 30, 30, 30, // 40
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 30, // 50
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 30, // 60
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 30, // 70
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 30,  // 80
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 30, // 90
    30, 35, 30, 30, 30,
    30, 35, 30, 30, 30  // 100
};

string itemTargets[] = 
{
    "003 006 002 000 000 000 000 000 000 000",
    "010 010 010 000 000 000 000 000 000 000", // 10
    "010 005 010 000 000 000 000 000 000 000",
    "022 020 020 000 000 000 000 000 000 000", // 20
    "023 020 020 000 000 000 000 000 000 000",
    "024 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "030 006 002 000 000 000 000 000 000 000",
    "021 020 020 000 000 000 000 000 000 000",  // 60
    "022 020 020 000 000 000 000 000 000 000",
    "023 020 020 000 000 000 000 000 000 000",  // 70
    "023 020 020 000 000 000 000 000 000 000",
    "024 020 020 000 000 000 000 000 000 000",  // 80
    "024 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 100
    "009 026 002 000 000 000 000 000 000 000",
    "020 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "040 006 002 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 200
    "030 006 002 000 000 000 000 000 000 000",
    "030 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 026 002 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 300
    "003 006 022 000 000 000 000 000 000 000",
    "010 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 006 032 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 400
    "003 006 032 000 000 000 000 000 000 000",
    "010 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 016 022 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 500
    "003 033 002 000 000 000 000 000 000 000",
    "010 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "013 016 052 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 600
    "003 006 002 000 000 000 000 000 000 000",
    "010 010 030 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 006 032 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 700
    "003 006 032 000 000 000 000 000 000 000",
    "010 010 030 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 006 002 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 800
    "003 006 022 000 000 000 000 000 000 000",
    "010 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 006 022 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 900
    "003 006 022 000 000 000 000 000 000 000",
    "010 010 010 000 000 000 000 000 000 000", // 10
    "025 005 030 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 20
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000", // 30
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 40
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 50
    "003 006 022 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 60
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 70
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 80
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000",  // 90
    "020 020 020 000 000 000 000 000 000 000",
    "020 020 020 000 000 000 000 000 000 000"  // 1000
};

string viewConfig[] =
{
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "egg.png item2.png item3.png", // 10
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "egg.png item2.png item3.png", // 20
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "egg.png item2.png item3.png", // 30
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "egg.png item2.png item3.png", // 40
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "egg.png item2.png item3.png", // 50
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "egg.png item2.png item3.png", // 60
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png", // 70
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png", // 80
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png", // 90
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png",
    "item1.png item2.png item3.png", // 100
    

};

string obstacleConfigure[] =
{
    "6:3,3,1 3,2,1 3,4,1 3,5,1 3,6,1 4,3,1 4,2,1 4,4,1, 4,5,1 4,6,1",
    "7:3,3,1 3,2,1 3,4,1",
    "8:3,3,1 3,2,1 3,4,1 2,3,1",
};


string addConf[] =
{
    "9:3,3,1,1 3,2,1,1",
    "10:3,3,1,1 3,2,1,1 3,4,1,1",
    "11:3,3,1,1 3,2,1,1 3,4,1,1 2,3,1,1",
};

string GameData::getAddi(int level)
{
    stringstream _ss;
    _ss.str("");
    _ss << level << ":";
    int sz = sizeof(addConf)/sizeof(addConf[0]);
    for(int i = 0; i < sz; i++)
    {
        if (strstr(addConf[i].c_str(),_ss.str().c_str()))
        {
            vector<string> ret = TI()->split(addConf[i],':');
            CCASSERT(ret.size() == 2, "obstacle configure error");
            return ret[1];
        }
    }
    
    return "";

}

string GameData::getObstacle(int level)
{
    stringstream _ss;
    _ss.str("");
    _ss << level << ":";
    int sz = sizeof(obstacleConfigure)/sizeof(obstacleConfigure[0]);
    for(int i = 0; i < sz; i++)
    {
        if (strstr(obstacleConfigure[i].c_str(),_ss.str().c_str()))
        {
            vector<string> ret = TI()->split(obstacleConfigure[i],':');
            CCASSERT(ret.size() == 2, "obstacle configure error");
            return ret[1];
        }
    }
    
    return "";
}

vector<AdditionData> GameData::getAddition(int level)
{
    vector<AdditionData> ret;
    string conStr = getAddi(level);
    if (conStr == "")
    {
        return ret;
    }
    
    vector<string> ss = TI()->split(conStr, ' ');
    for(auto item : ss)
    {
        vector<string> data = TI()->split(item,',');
        CCASSERT(data.size() == 4, "addition config error !");
        AdditionData obs;
        obs.i = TI()->_stoi(data[0]);
        obs.j = TI()->_stoi(data[1]);
        obs.type = TI()->_stoi(data[2]);
        obs.hp = TI()->_stoi(data[3]);
        ret.push_back(obs);
    }
    return ret;
}


vector<obsData> GameData::getObs(int level)
{
	
    vector<obsData> ret;
    string conStr = getObstacle(level);
    if (conStr == "")
    {
        return ret;
    }
    
    vector<string> ss = TI()->split(conStr, ' ');
    for(auto item : ss)
    {
        vector<string> data = TI()->split(item,',');
        CCASSERT(data.size() == 3, "obstacle config error");
        obsData obs;
        obs.i = TI()->_stoi(data[0]);
        obs.j = TI()->_stoi(data[1]);
        obs.type = TI()->_stoi(data[2]);
        ret.push_back(obs);
    }
    return ret;
}



int GameData::isWin(int level)
{
    if (level < 1 || level > MAX_LEVEL)
    {
        return 0;
    }

    string confData = itemTargets[level - 1];
    vector<string> dataVector = TI()->split(confData, ' ');

    int _num1 = TI()->string2number(dataVector[0]);
    int _num2 = TI()->string2number(dataVector[1]);
    int _num3 = TI()->string2number(dataVector[2]);
    int _num4 = TI()->string2number(dataVector[3]);
    int _num5 = TI()->string2number(dataVector[4]);

    if (num1 >= _num1&& num2 >=_num2 && num3 >= _num3)
    {
        return 1;
    }

    return 0;
}

int GameData::isWin(int level, int score)
{
    if (level < 1 || level > MAX_LEVEL)
    {
        return 0;
    }


    int targetScore = tagets[level - 1];
    if (score > (targetScore * 2) )
    {
        return 3;
    }
    else if (score > (targetScore*3/2))
    {
        return 2;
    }
    else if (score >= targetScore)
    {
        return 1;
    }
    
    
    return 0;
}

GameData*  GameData::getInstance()
{
    if (nullptr == instance_)
    {
        instance_ = new GameData;
    }
    return instance_;
}

TargetData GameData::getTarget(int level)
{
    TargetData ret;
    if (level < 1 || level > MAX_LEVEL)
    {
        ret.movesNum = 30;
        ret.targetScore = 100000;
        return ret;
    }
    
    ret.movesNum = moves[level-1];
    ret.targetScore = tagets[level-1];
    return ret;
}

TargetDataEx GameData::getTargetEx(int level)
{
    
    TargetDataEx ret;
    if (level < 1 || level > MAX_LEVEL)
    {
        return ret;
    }

    string confData = itemTargets[level - 1];
    vector<string> dataVector = TI()->split(confData, ' ');

    int _num1 = TI()->string2number(dataVector[0]);
    int _num2 = TI()->string2number(dataVector[1]);
    int _num3 = TI()->string2number(dataVector[2]);
    int _num4 = TI()->string2number(dataVector[3]);
    int _num5 = TI()->string2number(dataVector[4]);

    ret.num1_ = _num1;
    ret.num2_ = _num2;
    ret.num3_ = _num3;
    ret.num4_ = _num4;
    ret.num5_ = _num5;
    ret.movesNum = moves[level - 1];

    return ret;
}


ViewData GameData::getViewData(int level)
{
	
    string confData = viewConfig[level - 1];
    vector<string> dataVector = TI()->split(confData, ' ');
    
    ViewData data;
    data.name1 = dataVector[0];
    data.name2 = dataVector[1];
    data.name3 = dataVector[2];
    
    return data;
}

