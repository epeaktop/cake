#ifndef __tool_game_data_H__
#define __tool_game_data_H__
#include <iostream>
#include <vector>

using namespace std;

/**
 * @@ �Լ�����ĺ�����,�������boost��,������c++17,��ƽ̨!!
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
