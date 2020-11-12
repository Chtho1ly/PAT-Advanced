//https://pintia.cn/problem-sets/994805342720868352/problems/994805476473028608
#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long

using namespace std;

bool is_Palindromic(vector<int> s)
{
    for (size_t i = 0; i < s.size() / 2 + 1; i++)
        if (s[i] != s[s.size() - i - 1])
            return false;
    return true;
}

int main()
{
    string n;
    ll k;
    cin >> n >> k;
    vector<int> num;
    for (auto i = n.begin(); i < n.end(); i++)
        num.push_back(*i - '0');
    int cnt;
    for (cnt = 0; cnt < k; cnt++)
    {
        if (is_Palindromic(num))
        {
            break;
        }
        else
        {
            int carry = 0;
            vector<int> newNum(num);
            for (int i = num.size() - 1; i >= 0; i--)
            {
                newNum[i] = num[i] + num[num.size() - i - 1] + carry;
                carry = newNum[i] / 10;
                newNum[i] %= 10;
            }
            if (carry != 0)
                newNum.insert(newNum.begin(), carry);
            num = newNum;
        }
    }
    for (auto i : num)
        cout << i;
    cout << endl
         << cnt << endl;
}