//https://pintia.cn/problem-sets/994805342720868352/problems/994805516654460928
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct check
{
    string id;
    int hIn, mIn, sIn;
    int hOut, mOut, sOut;
};

bool lockCmp(check a, check b)
{
    if (a.hIn < b.hIn)
        return true;
    else if (a.hIn == b.hIn)
    {
        if (a.mIn < b.mIn)
            return true;
        else if (a.mIn == b.mIn)
        {
            if (a.sIn < b.sIn)
                return true;
        }
    }
    return false;
}

bool unlockCmp(check a, check b)
{
    if (a.hOut < b.hOut)
        return true;
    else if (a.hOut == b.hOut)
    {
        if (a.mOut < b.mOut)
            return true;
        else if (a.mOut == b.mOut)
        {
            if (a.sOut < b.sOut)
                return true;
        }
    }
    return false;
}

int main()
{
    int num;
    cin >> num;
    vector<check> table;
    for (int i = 0; i < num; i++)
    {
        check t;
        cin >> t.id;
        scanf("%d:%d:%d", &t.hIn, &t.mIn, &t.sIn);
        getchar();
        scanf("%d:%d:%d", &t.hOut, &t.mOut, &t.sOut);
        getchar();
        table.push_back(t);
    }
    string lock = min_element(table.begin(), table.end(), lockCmp)->id;
    string unlock = max_element(table.begin(), table.end(), unlockCmp)->id;
    cout << lock << " " << unlock << endl;
    return 0;
}