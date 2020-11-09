//https://pintia.cn/problem-sets/994805342720868352/problems/994805519074574336
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int sum = 0;
    string zidian[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (size_t i = 0; i < s.size(); i++)
        sum += s[i] - '0';
    s = to_string(sum);
    bool flag = false;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (flag)
            cout << " ";
        flag = true;
        cout << zidian[s[i] - '0'];
    }
    cout << endl;
    return 0;
}
