//https://pintia.cn/problem-sets/994805342720868352/problems/994805509540921344
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node
{
    int x;
    double a;
};

int main()
{
    int num;
    cin >> num;
    vector<double> s1(1001), s2(1001), ans(2002);
    while (num--)
    {
        int x;
        double a;
        cin >> x >> a;
        s1[x] = a;
    }
    cin >> num;
    while (num--)
    {
        int x;
        double a;
        cin >> x >> a;
        s2[x] = a;
    }
    for (int i = 0; i < 1001; i++)
    {
        for (int j = 0; j < 1001; j++)
            ans[i + j] += s1[i] * s2[j];
    }
    vector<node> s;
    for (int i = 0; i < 2002; i++)
    {
        if (ans[i] != 0)
        {
            node t;
            t.a = ans[i];
            t.x = i;
            s.push_back(t);
        }
    }
    reverse(s.begin(), s.end());
    cout << s.size();
    for (size_t i = 0; i < s.size(); i++)
        printf(" %d %.1lf", s[i].x, s[i].a);
    cout << endl;
    return 0;
}