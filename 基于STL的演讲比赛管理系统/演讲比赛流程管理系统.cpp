#include <iostream>
using namespace std;
#include "speechManager.h"

int main(int argc, const char * argv[]) {
    //创建管理类对象
    speechManager sm;

    int choice = 0;
    
    while(true)
    {
        sm.show_Manu();
        
        cout << "请输入你选择的数字: " << endl;
        cin >> choice;
        cin.get();
        
        switch(choice)
        { 
              
            case 1:
                //开始演讲比赛
                sm.creatSpeech();
                break;
            case 2:
                //查看往届记录
                sm.showRecord();
                break;
            case 3://清空比赛记录
                break;
            case 0://退出比赛程序
                sm.exit_System();
                break;
            default:
                system("clear");
                break;
        }
            
        
    }
   
    return 0;
 }
