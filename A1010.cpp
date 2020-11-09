//https://pintia.cn/problem-sets/994805342720868352/problems/994805507225665536
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<char, int> dict;

long long s_to_int(string s, long long radix)
{
    long long sum = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        char c = s[i];
        sum *= radix;
        sum += dict[c];
    }
    return sum;
}

int main()
{
    string refS, newS;
    for (char i = '0'; i <= '9'; i++)
        dict[i] = i - '0';
    for (char i = 'a'; i <= 'z'; i++)
        dict[i] = i - 'a' + 10;
    int tag;
    long long r;
    cin >> refS >> newS >> tag >> r;
    if (tag == 2)
        swap(refS, newS);
    long long ref = s_to_int(refS, r);
    long long left = dict[*max_element(newS.begin(), newS.end(), [](char a, char b) { return dict[a] < dict[b]; })] + 1;
    long long right = ref + 1;
    while (left <= right)
    {
        long long mid = (left + right) / 2;
        long long ans = s_to_int(newS, mid);
        if (ans == ref)
        {
            cout << mid << endl;
            return 0;
        }
        else if (ans > ref || ans < 0)
            right = mid - 1;
        else if (ans < ref)
            left = mid + 1;
    }
    cout << "Impossible" << endl;
    return 0;
}