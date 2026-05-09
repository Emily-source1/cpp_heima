#include "speechManager.h"

//构造函数
speechManager::speechManager()
{
    //初始化属性
    this->initSpeech();
    //初始化12名选手
    this->initSpeaker();
    //加载记录
    this->loadRecord();
    //清空记录容器
    this->m_Record.clear();
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
    this->showScore();
    
    //第二轮比赛
    this->m_Index++;
    //1.抽签
    this->speechDraw();
    //2.比赛
    this->speechContest();
    //3.显示最终结果
    this->showScore();
    //4.保存成绩结果到文件中
    this->saveRecord();
    
    //初始化属性
    this->initSpeech();
    //初始化12名选手
    this->initSpeaker();
    //加载记录
    this->loadRecord();
    
    system("clear");
    cout << "请按回车键继续" << endl;
    cin.get();
    cout << "本届比赛已完毕" << endl;
}

//抽签
void speechManager::speechDraw()
{
    cout << "这是第" << this->m_Index << "轮比赛选手正在抽签"<<endl;
    cout << "-------------------------" << endl;
    cout << "抽签后演讲顺序如下：" ;
    
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

    }
    
    cout << "-------------------------" << endl;
    cout << endl;
    
    cout << "请按回车键继续" << endl;
    cin.get();

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
                    v2.push_back(it->second);
                }
                else
                {
                    vVectory.push_back(it->second);
                }
            }
            groupScore.clear();
        }
    }
    cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << endl;
    
    cout << "请按回车键继续" << endl;
    cin.get();
}

//显示分数
void speechManager::showScore()
{
    cout << "第" << this->m_Index << "轮晋级选手分数如下" << endl;
    
    //设置此轮容器
    vector<int> v;
    if(this->m_Index == 1)
    {
        v =v2;
    }
    else
    {
        v = vVectory;
    }
    
    //打印
    for(vector<int>::iterator it = v.begin();it != v.end();it++)
    {
       cout << "编号：" << *it << " 姓名：" << this->m_speaker[*it].m_Name << " 成绩" << this->m_speaker[*it].m_Score[this->m_Index-1] <<endl;
    }
    
    cout << "按回车键返回主菜单" <<endl;
    cin.get();
    system("clear");

}

//保存记录
void speechManager::saveRecord()
{
    //创建对象
    ofstream ofs;
    
    //打开文件
    ofs.open("speaker.csv",ios::out | ios::app);
    
    //写入数据
    for(vector<int>::iterator it = vVectory.begin();it != vVectory.end();it++)
    {
        ofs << *it << "," << this->m_speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;
    
    //关闭文件
    ofs.close();
    cout << "记录已经保存" << endl;
    
    //有记录了，文件不为空
    this->fileIsEmpty = false;
}

//加载记录
void speechManager::loadRecord()
{
    ifstream ifs;
    ifs.open("speaker.csv",ios::in);
    
    //文件不存在
    if(!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        this->fileIsEmpty = true;
        return;
    }
    //文件为空
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        cout << "文件为空"  << endl;
        ifs.close();
        this->fileIsEmpty = true;
        return;
    }
    //文件存在
    
    ifs.putback(ch);
    this->fileIsEmpty = false;
    
    string data;
    //把.csv文件的内容放进data里
    int index = 0;
    while(ifs >> data)
    {
        
//        cout << data << endl;
        int pos = -1;
        int start = 0;
        vector<string> v;
        while(true)
        {
            //10011,83.6125,10012,82.7375,10002,80.725,
            //把data里的数据拿出来，放进临时容器v里
            pos = (int)data.find(",",start);
            if(pos == -1)
            {
                break;
            }
            string tem = data.substr(start,pos-start);
            v.push_back(tem);
            start = pos + 1;
        }
        
        this->m_Record.insert(make_pair(index,v));
        index++;
    }
    ifs.close();
    
//    for(map<int,vector<string>>::iterator it = m_Record.begin();it != m_Record.end();it++)
//    {
//        cout << "第" << it->first << "届冠军" <<" 编号" << it->second[0] << " 姓名" << it->second[1] << endl;
//    }
}


//显示分数
void speechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        cout << "文件为空或文件不存在" << endl;
    }
    else
    {
        for(int i = 0;i < this->m_Record.size();i++)
        {
            cout << "第" << i + 1 << "届冠军" <<" 编号" << this->m_Record[i][0]  << " 成绩" << this->m_Record[i][1]  << " ";
            cout << "第" << i + 1 << "届亚军" <<" 编号" << this->m_Record[i][2]  << " 成绩" << this->m_Record[i][3]  << " ";
            cout << "第" << i + 1 << "届季军" <<" 编号" << this->m_Record[i][4]  << " 成绩" << this->m_Record[i][5]  << endl;
        }
    }
    
    system("clear");
    cout << "按回车键继续" << endl;
    cin.get();
}

//清空记录
void speechManager::clearRecord()
{
    cout << "确认清空记录吗?" << endl;
    cout << "1、确认 " << endl;
    cout << "2、返回 " << endl;
    
    int choice;
    cin >> choice;
    
    if(choice == 1)
    {
        ofstream ofs;
        ofs.open("speaker.csv",ios::trunc);
        ofs.close();
        
        //初始化属性
        this->initSpeech();
        //初始化12名选手
        this->initSpeaker();
        //加载记录
        this->loadRecord();
        
        cout << "清空成功！" << endl;
        
        system("clear");
        cout << "按回车键继续" << endl;
        cin.get();
        
    }
}

//析构函数
speechManager::~speechManager(){}
