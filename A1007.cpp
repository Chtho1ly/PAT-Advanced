//https://pintia.cn/problem-sets/994805342720868352/problems/994805514284679168
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int sum = 0;
    int beg;
    int end;
};

int main()
{
    int num;
    cin >> num;
    vector<int> tab(num);
    vector<node> dp(num);
    for (int i = 0; i < num; i++)
        cin >> tab[i];
    dp[0].sum = tab[0];
    dp[0].beg = tab[0];
    dp[0].end = tab[0];
    for (int i = 1; i < num; i++)
    {
        dp[i].end = tab[i];
        if (dp[i - 1].sum > 0)
        {
            dp[i].sum = dp[i - 1].sum + tab[i];
            dp[i].beg = dp[i - 1].beg;
        }
        else
        {
            dp[i].sum = tab[i];
            dp[i].beg = tab[i];
        }
    }
    auto ans = max_element(dp.begin(), dp.end(), [](node a, node b) { return a.sum < b.sum; });
    if (ans->sum >= 0)
        cout << ans->sum << " " << ans->beg << " " << ans->end << endl;
    else
        cout << 0 << " " << tab.front() << " " << tab.back() << endl;
    return 0;
}