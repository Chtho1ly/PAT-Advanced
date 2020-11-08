//https://pintia.cn/problem-sets/994805342720868352/problems/994805528788582400
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    long long a, b;
    cin >> a >> b;
    a = a + b;
    string s = to_string(a);
    if (a < 0)
    {
        s.erase(s.begin());
        cout << "-";
    }
    size_t j = (3 - s.size() % 3) % 3;
    for (size_t i = 0; i < s.size(); i++, j++)
    {
        if (j % 3 == 0 && j != 0 && i != s.size() - 1)
            cout << ',';
        cout << s[i];
    }
    cout << endl;
    return 0;
}