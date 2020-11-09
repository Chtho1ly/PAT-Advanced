//https://pintia.cn/problem-sets/994805342720868352/problems/994805511923286016
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int num;
    cin >> num;
    queue<int> toList;
    while (num--)
    {
        int t;
        cin >> t;
        toList.push(t);
    }
    int floor = 0;
    int time = 0;
    while (!toList.empty())
    {
        if (toList.front() > floor)
        {
            floor++;
            time += 6;
        }
        else if (toList.front() == floor)
        {
            time += 5;
            toList.pop();
        }
        else if (toList.front() < floor)
        {
            floor--;
            time += 4;
        }
    }
    cout << time << endl;
    return 0;
}