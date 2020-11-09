//https://pintia.cn/problem-sets/994805342720868352/problems/994805521431773184
#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int generation;
    vector<int> children;
};

vector<node> blood(200);
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
    for (int i = 0; i < nonLeaf; i++)
    {
        int parent;
        int childNum;
        cin >> parent >> childNum;
        for (int j = 0; j < childNum; j++)
        {
            int child;
            cin >> child;
            blood[parent].children.push_back(child);
        }
    }
    vector<int> waiting;
    waiting.push_back(1);
    while (!waiting.empty())
    {
        int parent = waiting.front();
        waiting.erase(waiting.begin());
        if (blood[parent].generation >= int(noChildCount.size()))
            noChildCount.push_back(0);
        if (blood[parent].children.size() == 0)
            noChildCount[blood[parent].generation]++;
        for (vector<int>::iterator i = blood[parent].children.begin(); i < blood[parent].children.end(); i++)
        {
            waiting.push_back(*i);
            blood[*i].generation = blood[parent].generation + 1;
        }
    }
    for (size_t i = 0; i < noChildCount.size(); i++)
    {
        cout << noChildCount[i];
        if (i != noChildCount.size() - 1)
            cout << " ";
    }
    cout << endl;
    return 0;
}