#ifndef __tool_game_data_H__
#define __tool_game_data_H__
#include <iostream>
#include <vector>

#include <cocos2d.h>
using namespace std;

USING_NS_CC;
/**
 * @@ 自己定义的函数库,避免包含boost库,尽量用c++17,跨平台!!
 * @@ jiangxf @2016.12.15
 */

class Tools
{
public:
    static Tools* getInstance();
    
    vector<string> split(const string &s, char delim);
    int string2number(string str);
    int _stoi(string s);
    string _itos(int s);
    float getWidth();
    float getHeigh();
	bool isInScope(Vec2 v, Vec2 v1, Vec2 v2);
    
    
    int getYear();
    int getMonth();
    int getDay();
    
private:
    static Tools* instance_;
        
};

#define TI Tools::getInstance
	
#endif  // __HELLOWORLD_SCENE_H__
