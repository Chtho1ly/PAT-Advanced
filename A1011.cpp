//https://pintia.cn/problem-sets/994805342720868352/problems/994805504927186944
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

char dict(int a)
{
    if (a == 0)
        return 'W';
    else if (a == 1)
        return 'T';
    else if (a == 2)
        return 'L';
    else
        return 0;
}

int main()
{
    int bet[3];
    double profit[3];
    for (int i = 0; i < 3; i++)
    {
        vector<double> wtl(3);
        cin >> wtl[0] >> wtl[1] >> wtl[2];
        bet[i] = max_element(wtl.begin(), wtl.end()) - wtl.begin();
        profit[i] = wtl[bet[i]];
    }
    cout << dict(bet[0]) << " " << dict(bet[1]) << " " << dict(bet[2]) << " ";
    printf("%.2lf\n", (profit[0] * profit[1] * profit[2] * 0.65 - 1) * 2);
    return 0;
}