//https://pintia.cn/problem-sets/994805342720868352/problems/994805487143337984
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, base;
    cin >> n >> base;
    vector<int> decimals;
    if (n == 0)
        decimals.push_back(0);
    while (n != 0)
    {
        decimals.push_back(n % base);
        n /= base;
    }
    bool palindromic = true;
    for (size_t i = 0; i < decimals.size(); i++)
    {
        if (decimals[i] != decimals[decimals.size() - i - 1])
        {
            palindromic = false;
            break;
        }
    }
    if (palindromic)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    for (auto i = decimals.rbegin(); i < decimals.rend(); i++)
    {
        if (i != decimals.rbegin())
            cout << " ";
        cout << *i;
    }
    cout << endl;
    return 0;
}