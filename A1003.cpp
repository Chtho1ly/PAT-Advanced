#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
#define INF 0x3fffffff
using namespace std;

struct node
{
    int destination; //道路终点
    int len;         //道路长度
    node(int a, int b)
    {
        destination = a;
        len = b;
    }
};

vector<vector<node>> table; //邻接表
vector<vector<int>> pre;    //前驱
vector<int> teamNum;        //个城市队伍数量
vector<int> L;              //路程
vector<bool> visted;        //城市是否已被访问
vector<int> num;            //由起点到达城市路径数量
int maxTeam = -1;
vector<vector<int>> finalPath;

int djs(int origin, int cityNum)
{
    L[origin] = 0;
    num[origin] = 1;
    for (int j = 0; j < cityNum; j++)
    {
        int newCity = -1;                 //目前图中距起点最近的城市
        int min = INF;                    //目前图中距起点最近的城市到起点的距离
        for (int i = 0; i < cityNum; i++) //获取最近的城市
        {
            if (!visted[i] && L[i] < min)
            {
                newCity = i;
                min = L[i];
            }
        }

        if (newCity == -1) //无未访问可到达城市，无法到达终点
            return -1;
        visted[newCity] = true;
        //更新新城市所有的邻居
        for (unsigned long long i = 0; i < table[newCity].size(); i++)
        {
            if (L[table[newCity][i].destination] >= L[newCity] + table[newCity][i].len)
            {
                //若由起点经过新城市访问他的邻居的距离 等于 原来起点到邻居的距离，为邻居添加前驱
                if (L[table[newCity][i].destination] == L[newCity] + table[newCity][i].len)
                {
                    num[table[newCity][i].destination] += num[newCity];
                    pre[table[newCity][i].destination].push_back(newCity);
                }
                //若由起点经过新城市访问他的邻居的距离 小于 原来起点到邻居的距离，更新起点到邻居的距离和邻居前驱
                else
                {
                    num[table[newCity][i].destination] = num[newCity];
                    pre[table[newCity][i].destination].clear();
                    pre[table[newCity][i].destination].push_back(newCity);
                    L[table[newCity][i].destination] = L[newCity] + table[newCity][i].len;
                }
            }
        }
    }
    return 0;
}

void get_finalTeam(int cur, int tempTeam, vector<int> tempPath)
{
    tempTeam += teamNum[cur];
    tempPath.push_back(cur);
    if (pre[cur].size() == 0)
    {
        finalPath.push_back(tempPath);
        if (tempTeam > maxTeam)
        {
            maxTeam = tempTeam;
        }
        tempPath.pop_back();
        return;
    }
    for (int i : pre[cur])
    {
        get_finalTeam(i, tempTeam, tempPath);
    }
    tempPath.pop_back();
    return;
}

int main()
{
    int cityNum, roadNum, origin, target;
    cin >> cityNum >> roadNum >> origin >> target;
    for (int i = 0; i < cityNum; i++)
    {
        int temp;
        scanf("%d", &temp);
        teamNum.push_back(temp);
    }
    table.insert(table.begin(), cityNum, {});
    pre.insert(pre.begin(), cityNum, {});
    num.insert(num.begin(), cityNum, 0);
    for (int i = 0; i < roadNum; i++)
    {
        int tempS, tempD, tempL;
        scanf("%d %d %d", &tempS, &tempD, &tempL);
        table[tempS].push_back(node(tempD, tempL));
        table[tempD].push_back(node(tempS, tempL));
    }

    //将邻接表中的道路按目的地排序，意义不明
    /*
    for (auto &i : table)
    {
        sort(i.begin(), i.end(), [](node a, node b) { return a.destination < b.destination; });
    }
    */

    L.insert(L.begin(), cityNum, INF);
    visted.insert(visted.begin(), cityNum, false);
    djs(origin, cityNum);
    /*
    for (int i = 0; i < cityNum; i++)
    {
        cout << i << " " << L[i] << " " << num[i] << " (";
        for (auto j : pre[i])
            cout << j << " ";
        cout << ")" << endl;
    }
    */
    if (L[target] == INF)
    {
        cout << "can't arrive";
    }
    else
    {
        get_finalTeam(target, 0, {});
        cout << finalPath.size() << " " << maxTeam << endl;
        /*
        for (auto i : finalPath)
        {
            for (auto j = i.rbegin(); j != i.rend(); j++)
                cout << *j << " ";
            cout << endl;
        }
        */
    }

    return 0;
}