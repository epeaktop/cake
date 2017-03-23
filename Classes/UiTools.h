#ifndef __tool_game_data_H__
#define __tool_game_data_H__
#include <iostream>
#include <vector>

using namespace std;

/**
 * @@ 自己定义的函数库,避免包含boost库,尽量用c++17,跨平台!!
 * @@ jiangxf @2016.12.15
 */
class UiTools
{
public:
    static UiTools* getInstance();


private:
    static UiTools* instance_;
        
};

#define TI UiTools::getInstance

#endif  // __HELLOWORLD_SCENE_H__
