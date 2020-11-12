//https://pintia.cn/problem-sets/994805342720868352/problems/994805482919673856
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> tab;
vector<bool> unvisited;
vector<int> level;

int DFS(int cur)
{
    for (auto i : tab[cur])
    {
        if (unvisited[i])
        {
            unvisited[i] = false;
            level[i] = level[cur] + 1;
            DFS(i);
        }
    }
    return 0;
}

int main()
{
    int n;
    cin >> n;
    //建立邻接表
    tab.insert(tab.begin(), n + 1, vector<int>(0));
    for (int i = 0; i < n - 1; i++)
    {
        int beg, end;
        cin >> beg >> end;
        tab[beg].push_back(end);
        tab[end].push_back(beg);
    }
    //使用DFS检查图是否连通
    level.insert(level.begin(), n + 1, 0);
    unvisited.insert(unvisited.begin(), n + 1, true);
    int componentCnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (unvisited[i])
        {
            unvisited[i] = false;
            componentCnt++;
            DFS(i);
        }
    }
    //统计连通分量数量，若有多个连通分量，则图不是树，报错
    if (componentCnt > 1)
    {
        cout << "Error: " << componentCnt << " components" << endl;
        return 0;
    }
    else
    {
        //使用DFS统计从每个叶子节点出发树的高度
        vector<int> heigestRootV = {1};
        int maxDepth = *max_element(level.begin(), level.end());
        for (int i = 2; i <= n; i++)
        {
            fill(level.begin(), level.end(), 0);
            fill(unvisited.begin(), unvisited.end(), true);
            unvisited[i] = false;
            DFS(i);
            auto newMaxDepth = *max_element(level.begin(), level.end());
            if (newMaxDepth > maxDepth)
            {
                maxDepth = newMaxDepth;
                heigestRootV.clear();
                heigestRootV.push_back(i);
            }
            else if (maxDepth == newMaxDepth)
                heigestRootV.push_back(i);
        }
        for (auto i : heigestRootV)
            cout << i << endl;
        return 0;
    }
}