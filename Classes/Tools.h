#ifndef __tool_game_data_H__
#define __tool_game_data_H__
#include <iostream>
#include <vector>

using namespace std;

/**
 * @@ �Լ�����ĺ�����,�������boost��,������c++17,��ƽ̨!!
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


private:
    static Tools* instance_;
        
};

#define TI Tools::getInstance

#endif  // __HELLOWORLD_SCENE_H__
