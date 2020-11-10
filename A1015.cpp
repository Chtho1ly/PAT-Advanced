//https://pintia.cn/problem-sets/994805342720868352/problems/994805495863296000
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

bool is_Prime(long long num)
{
    if (num == 1 || num == 0)
        return false;
    for (long long i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int main()
{
    while (true)
    {
        long long a, radix;
        cin >> a;
        if (a < 0)
            break;
        cin >> radix;
        if (is_Prime(a))
        {
            string bS;
            while (a != 0)
            {
                bS.push_back(a % radix + '0');
                a /= radix;
            }
            long long b = 0;
            for (auto i : bS)
            {
                b *= radix;
                b += i - '0';
            }
            if (is_Prime(b))
            {
                cout << "Yes" << endl;
                continue;
            }
        }
        cout << "No" << endl;
    }
    return 0;
}