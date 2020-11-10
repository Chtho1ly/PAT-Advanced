//https://pintia.cn/problem-sets/994805342720868352/problems/994805493648703488
#include <algorithm>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct record
{
    int month;
    int day;
    int hour;
    int minute;
    int mode; //1代表上线，0代表下线
    bool operator<(record &b)
    {
        if (month != b.month)
            return month < b.month;
        else if (day != b.day)
            return day < b.day;
        else if (hour != b.hour)
            return hour < b.hour;
        else
            return minute < b.minute;
    };
    record operator++(int)
    {
        minute++;
        if (minute >= 60)
        {
            hour++;
            minute = 0;
            if (hour >= 24)
            {
                day++;
                hour = 0;
                /*
                if (day >= 31)
                {
                    month++;
                    day = 1;
                    if (month >= 13)
                    {
                        month = 1;
                    }
                }
                */
            }
        }
        return *this;
    };
};

map<int, double> costTab;

struct calling
{
    record beg;
    record end;
    int len()
    {
        int m, h, d;
        m = end.minute - beg.minute;
        h = end.hour - beg.hour;
        d = end.day - beg.day;
        return m + 60 * (h + 24 * d);
    }
    double cost() //通话花费
    {
        double sum = 0;
        for (record cur = beg; cur < end; cur++)
        {
            sum += costTab[cur.hour];
        }
        return sum / 100;
    }
};

struct user
{
    string name;
    vector<record> records;
    vector<calling> callings;

    double totalCost()
    {
        double sum = 0;
        for (auto i : callings)
            sum += i.cost();
        return sum;
    }
};

int main()
{
    //初始化收费标准
    for (int i = 0; i < 24; i++)
        cin >> costTab[i];
    vector<user> userV;
    int callNum;
    cin >> callNum;
    //输入通话事件
    while (callNum--)
    {
        record t;
        string id;
        string modeS;
        cin >> id;
        scanf("%d:%d:%d:%d", &t.month, &t.day, &t.hour, &t.minute);
        cin >> modeS;
        if (modeS == "on-line")
            t.mode = 1;
        else
            t.mode = 0;
        auto userP = find_if(userV.begin(), userV.end(), [id](user a) { return a.name == id; });
        if (userP == userV.end())
        { //用户尚未注册
            userV.push_back(user());
            userV.back().name = id;
            userV.back().records.push_back(t);
        }
        else //用户已注册
            userP->records.push_back(t);
    }
    //所有用户事件按时间排序
    for (auto &i : userV)
        sort(i.records.begin(), i.records.end());
    //将事件整理为完整的通话记录
    for (auto &i : userV)
    {
        for (auto j = i.records.begin(); j < i.records.end() - 1; j++)
        {
            if (j->mode == 1 && (j + 1)->mode == 0)
            { //存在成对的接通和挂断事件，将该通话压入callings
                calling t;
                t.beg = *j;
                t.end = *(j + 1);
                i.callings.push_back(t);
                j++;
            }
        }
    }
    //将用户按姓名排序
    sort(userV.begin(), userV.end(), [](user a, user b) { return a.name < b.name; });
    for (auto i : userV)
    {
        if (!i.callings.empty())
        {
            printf("%s %02d\n", i.name.c_str(), i.records.front().month);
            for (auto j : i.callings)
            {
                printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.02lf\n", j.beg.day, j.beg.hour, j.beg.minute, j.end.day, j.end.hour, j.end.minute, j.len(), j.cost());
            }
            printf("Total amount: $%.02lf\n", i.totalCost());
        }
    }
    return 0;
}