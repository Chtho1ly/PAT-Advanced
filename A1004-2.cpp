//https://pintia.cn/problem-sets/994805342720868352/problems/994805521431773184
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> blood(200);
vector<int> noChildCount;

int main()
{
    ios::sync_with_stdio(false);
    int total;
    int nonLeaf;
    cin >> total;
    if (total == 0)
        return 0;
    cin >> nonLeaf;
    //输入数据
    for (int i = 0; i < nonLeaf; i++)
    {
        int parent;
        int childNum;
        cin >> parent >> childNum;
        for (int j = 0; j < childNum; j++)
        {
            int child;
            cin >> child;
            blood[parent].push_back(child);
        }
    }
    vector<int> waiting;
    waiting.push_back(1);
    bool space = false; //标志是否输出空格
    while (!waiting.empty())
    {
        int s = waiting.size(), ans = 0;
        while (s--)
        {
            auto t = waiting.front();
            waiting.erase(waiting.begin());
            if (blood[t].empty())
            { //是叶子结点
                ++ans;
            }
            for (auto i : blood[t])
            {
                waiting.push_back(i);
            }
        }
        cout << (space ? " " : "") << ans;
        space = true;
    }
    return 0;
}