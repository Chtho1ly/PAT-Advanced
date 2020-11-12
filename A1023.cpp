//https://pintia.cn/problem-sets/994805342720868352/problems/994805478658260992
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define ll unsigned long long

using namespace std;

int main()
{
    string a, b;
    cin >> a;
    b = a;
    ll carry = 0;
    for (auto i = b.rbegin(); i < b.rend(); i++)
    {
        char num = *i - '0';
        num = num * 2 + carry;
        carry = num / 10;
        *i = num % 10 + '0';
    }
    if (carry > 0)
        b.insert(b.begin(), carry + '0');
    vector<int> cnt(10, 0);
    for (auto i : a)
        cnt[i - '0']++;
    for (auto i : b)
        cnt[i - '0']--;
    if (find_if(cnt.begin(), cnt.end(), [](int a) { return a != 0; }) == cnt.end())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    cout << b << endl;
    return 0;
}