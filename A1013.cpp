//https://pintia.cn/problem-sets/994805342720868352/problems/994805500414115840
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct road
{
    int beg;
    int end;
    bool valid = true;
};

int cityNum;
int roadNum;
int checkNum;
vector<int> cityV;
vector<road> roadV;
vector<int> checkV;
vector<int> toUpdate(1001);

int find_Parent(int leaf)
{
    int root = leaf;
    int cnt = 0;
    while (cityV[root] != root)
    {
        toUpdate[cnt] = root;
        cnt++;
        root = cityV[root];
    }
    for (int i = 0; i < cnt; i++)
        cityV[toUpdate[i]] = root;
    return root;
}

void merge(int a, int b)
{
    cityV[a] = b;
    return;
}

int root_Count()
{
    int cnt = -1;
    for (int i = 1; i <= cityNum; i++)
    {
        if (cityV[i] == i)
            cnt++;
    }
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> cityNum >> roadNum >> checkNum;
    cityV.insert(cityV.begin(), cityNum + 1, 0);
    roadV.insert(roadV.begin(), roadNum, road());
    checkV.insert(checkV.begin(), checkNum, 0);
    //输入数据
    for (int i = 0; i < roadNum; i++)
        cin >> roadV[i].beg >> roadV[i].end;
    for (int i = 0; i < checkNum; i++)
        cin >> checkV[i];
    for (int i = 0; i < checkNum; i++)
    {
        int checkCity = checkV[i];
        vector<road>::iterator invalidRoad;
        invalidRoad = find_if(roadV.begin(), roadV.end(), [checkCity](road a) { return a.valid && (a.beg == checkCity || a.end == checkCity); });
        //被占领城市相邻道路置为无效
        while (invalidRoad != roadV.end())
        {
            invalidRoad->valid = false;
            invalidRoad = find_if(roadV.begin(), roadV.end(), [checkCity](road a) { return a.valid && (a.beg == checkCity || a.end == checkCity); });
        }
        //初始化所有城市的根为自身
        for (int j = 1; j <= cityNum; j++)
            cityV[j] = j;
        //使用并查集合并所有城市
        for (vector<road>::iterator cur = roadV.begin(); cur < roadV.end(); cur++)
        {
            if (cur->valid)
            {
                int aRoot = find_Parent(cur->beg);
                int bRoot = find_Parent(cur->end);
                if (aRoot != bRoot)
                    merge(aRoot, bRoot);
            }
        }
        int cnt = root_Count() - 1;
        cout << cnt << endl;
        //所有道路置为有效
        for (int j = 0; j <= roadNum; j++)
            roadV[j].valid = true;
    }
    return 0;
}