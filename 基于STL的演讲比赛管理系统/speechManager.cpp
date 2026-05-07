#include "speechManager.h"

//构造函数
speechManager::speechManager()
{
    //初始化属性
    this->initSpeech();
    //初始化12名选手
    this->initSpeaker();
}

//展示菜单
void speechManager::show_Manu()
{
    cout << "********************************************" << endl;
        cout << "*************  欢迎参加演讲比赛 ************" << endl;
        cout << "*************  1.开始演讲比赛  *************" << endl;
        cout << "*************  2.查看往届记录  *************" << endl;
        cout << "*************  3.清空比赛记录  *************" << endl;
        cout << "*************  0.退出比赛程序  *************" << endl;
        cout << "********************************************" << endl;
        cout << endl;
}
//退出程序
void speechManager::exit_System()
{
    cout << "欢迎下次使用"<< endl;
    
    system("read"); 
    exit(0);
}

//初始化属性
void speechManager::initSpeech()
{
    //确保容器为空
    this->v1.clear();
    this->v2.clear();
    this->vVectory.clear();
    this->m_speaker.clear();
    
    //初始化比赛轮数
    this->m_Index = 1;
}

//初始化创建选手12名选手
void speechManager::initSpeaker()
{
    //创建选手名
    string nameSeed = "ABCDEFGHIJKL";
    for(int i = 0;i < nameSeed.size();i++)
    {
        string name = "选手";
        name += nameSeed[i];
        
        Speaker sp;
        sp.m_Name = name;
        
        //记录选手的每轮得分
        for(int j = 0;j < 2;j++)
        {
            sp.m_Score[j] = 0;
        }
        
        //把选手编号放进v1容器里
        this->v1.push_back(10001 + i);
        
        //把选手名和编号放进map容器里
        this->m_speaker.insert(make_pair(10001+i,sp));
    }
}

//比赛，控制比赛中的全部流程
void speechManager::creatSpeech()
{
    //第一轮比赛
    //1.抽签
    this->speechDraw();
    //2.比赛
    this->speechContest();
    //3.显示晋级结果
    
    //第二轮比赛
    //1.抽签
    //2.比赛
    //3.显示最终结果
    //4.保存成绩结果到文件中
    cout << "请按回车键返回主菜单..." << endl;
    cin.ignore();//清空缓冲区
    cin.get();//等待用户输入空格
   
}

//抽签
void speechManager::speechDraw()
{
    cout << "这是第" << this->m_Index << "轮比赛"<<endl;
    cout << "-------------------------" << endl;
    cout << "12名比赛选手的抽签顺序：" ;
    
    if(this->m_Index == 1)
    {//第一轮
        random_device rd;
        mt19937 g(rd());
        shuffle(v1.begin(),v1.end(),g);
        
        
        for(vector<int>::iterator it = v1.begin();it!= v1.end();it++)
        {
            cout << (*it) << " ";
        }
        cout << endl;
        
    }
    else
    {     //第二轮
        random_device rd;
        mt19937 g(rd());
        shuffle(v2.begin(),v2.end(),g);
        cout << "6名比赛选手的抽签顺序：" ;
        
        for(vector<int>::iterator it = v2.begin();it!= v2.end();it++)
        {
            cout << (*it) << " ";
        }
        cout << endl;
        
        cout << "-------------------------" << endl;
        cout << endl;

    }

}

//比赛
void speechManager::speechContest()
{
    //创建临时容器，存放一组的成员 double是选手分数 int是选手编号
    multimap<double,int,greater<double>> groupScore;
    
    //记录人员数
    int num = 0;
    
    //创建比赛人员容器
    vector <int>v_Src;
    if(this->m_Index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }
    
    //遍历所有选手
    for(vector<int>::iterator it = v_Src.begin();it != v_Src.end(); it++)
    {
        num++;
        
        //评委打分 deque容器
        deque<double> d;
        for(int i = 0;i < 10; i++)
        {
                        double score = (rand()%401 + 600)/10.f;
            d.push_back(score);
        }
        sort(d.begin(),d.end(),greater<double>());
        
        //去除最低、高分
        d.pop_back();
        d.pop_front();
        
        //求平均分
        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum /(double)d.size();
        
        //将平均分放进map容器
        this->m_speaker[*it].m_Score[this->m_Index - 1] = avg;
      
//       //测试每个人的平均分
//        cout << "编号：" << *it << " 姓名：" << this->m_speaker[*it].m_Name << " 成绩" << avg << " ";
        
        //每6个人为一组，用临时容器存储，作用是自动把成绩由高到低排出
        groupScore.insert(make_pair(avg,(*it)));
        if(num % 6 == 0)
        {
            cout <<"第" << num/6 << "小组的比赛名次" << endl;
            for(multimap<double,int,greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++)
            {
                cout << "编号：" << (*it).second<< " 姓名：" <<this->m_speaker[it->second].m_Name << "成绩:" << this->m_speaker[it->second].m_Score[this->m_Index - 1] << endl;
            }
            
            //选出前三，放到下一轮的容器
            int count = 0;
            for(multimap<double,int,greater<double>>::iterator it = groupScore.begin();it != groupScore.end()&&count < 3;it++,count++)
            {
                if(this->m_Index == 1)
                {
                    v2.push_back(it->first);
                }
                else
                {
                    vVectory.push_back(it->first);
                }
            }
            groupScore.clear();
        }
    }
    cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << endl;
    cin.ignore();
    cin.get();
}

//析构函数
speechManager::~speechManager(){}
