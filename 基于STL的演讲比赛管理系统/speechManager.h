#pragma once //防止头文件被重复包含
#include <iostream>
using namespace std;
#include "speaker.h"
#include <vector>
#include <map>
#include <random>
#include <deque>
#include <algorithm>
#include <numeric>
#include <fstream>

//设计演讲管理类
class speechManager
{
public:
    //构造函数
    speechManager();
    
    //展示菜单
    void show_Manu();
   
    //退出程序
    void exit_System();
    
    int m_Index;
    vector<int> v1; //比赛人数 12
    vector<int> v2; //第一轮比赛人数 6
    vector<int> vVectory; //获奖人数 3

    map<int,Speaker> m_speaker; //每个人的名字和对应的编号

    //初始化属性
    void initSpeech();
    
    //初始化创建选手12名选手
    void initSpeaker();
    
    //控制比赛中的全部流程
    void creatSpeech();
    
    //抽签
    void speechDraw();
    
    //比赛
    void speechContest();
    
    //显示分数
    void showScore();
    
    //保存记录
    void saveRecord();
    
    //加载记录
    void loadRecord();
    
    //文件为空的标志
    bool fileIsEmpty;
    
    //往届记录, 第几届和信息
    map<int,vector<string>> m_Record;
    
    //显示分数
    void showRecord();
    
    //清空记录
    void clearRecord();
    
    //析构函数
    ~speechManager();
};


