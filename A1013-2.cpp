//https://pintia.cn/problem-sets/994805342720868352/problems/994805500414115840
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int cityNum;
int roadNum;
int checkNum;
vector<vector<int>> cityV;
vector<bool> visited;
vector<int> checkV;

void dfs(int cur)
{
    visited[cur] = true;
    for (size_t i = 0; i < cityV[cur].size(); i++)
    {
        if (!visited[cityV[cur][i]])
            dfs(cityV[cur][i]);
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> cityNum >> roadNum >> checkNum;
    cityV.insert(cityV.begin(), cityNum + 1, {});
    checkV.insert(checkV.begin(), checkNum, 0);
    visited.insert(visited.begin(), cityNum, false);
    //输入数据
    for (int i = 0; i < roadNum; i++)
    {
        int a, b;
        cin >> a >> b;
        cityV[a].push_back(b);
        cityV[b].push_back(a);
    }
    for (int i = 0; i < checkNum; i++)
        cin >> checkV[i];
    for (int i = 0; i < checkNum; i++)
    {
        int checkCity = checkV[i];
        //被占领城市相邻道路置为已访问
        for (int j = 1; j <= cityNum; j++)
            visited[j] = false;
        visited[checkCity] = true;
        //使用dfs合并所有城市
        int cnt = -1;
        for (int j = 1; j <= cityNum; j++)
        {
            if (!visited[j])
            {
                dfs(j);
                cnt++;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}