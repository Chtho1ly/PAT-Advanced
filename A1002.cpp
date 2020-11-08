//https://pintia.cn/problem-sets/994805342720868352/problems/994805526272000000
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
    vector<double> s(1001);
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        double a;
        int x;
        cin >> x >> a;
        s[x] += a;
    }
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        double a;
        int x;
        cin >> x >> a;
        s[x] += a;
    }
    vector<double> ans;
    for (int i = 1000; i >= 0; i--)
        if (s[i] != 0)
            ans.push_back(s[i]);
    cout << ans.size();
    for (int i = 1000; i >= 0; i--)
    {
        if (s[i] != 0)
            printf(" %d %.1lf", i, s[i]);
    }
    cout << endl;
    return 0;
}