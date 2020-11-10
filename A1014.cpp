//https://pintia.cn/problem-sets/994805342720868352/problems/994805498207911936
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(void)
{
    int N, M, K, Q;
    //窗口数，队伍长，顾客数，询问数
    cin >> N >> M >> K >> Q;
    vector<queue<int>> lines(N);         //每个窗口前排队顾客编号
    vector<int> needTime(K + 1);         //第k位顾客所需时间
    vector<int> finishAfterTime(N);      //窗口完成当前业务所需时间
    vector<int> finishedTime(K + 1, -1); //顾客开始业务时刻
    vector<int> query(Q);
    for (int i = 1; i <= K; i++)
        cin >> needTime[i];
    for (int i = 0; i < Q; i++)
        cin >> query[i];
    int customNth = 1;
    int time = 0;
    while (true)
    {
        //向每个窗口压入顾客
        auto notFullLine = min_element(lines.begin(), lines.end(), [](queue<int> a, queue<int> b) { return a.size() < b.size(); });
        while (notFullLine->size() < M && customNth <= K)
        {
            notFullLine->push(customNth);
            if (notFullLine->size() == 1)
            {
                finishAfterTime[notFullLine - lines.begin()] = needTime[customNth];
                finishedTime[customNth] = time + needTime[customNth];
            }
            customNth++;
            notFullLine = min_element(lines.begin(), lines.end(), [](queue<int> a, queue<int> b) { return a.size() < b.size(); });
        }
        //耗时最短顾客完成业务
        int timePassed = *min_element(finishAfterTime.begin(), finishAfterTime.end());
        time += timePassed;
        for (auto &t : finishAfterTime)
            t -= timePassed;
        //完成业务的顾客弹出
        size_t finishedWindow = find_if(finishAfterTime.begin(), finishAfterTime.end(), [](int a) { return a == 0; }) - finishAfterTime.begin();
        while (finishedWindow != finishAfterTime.size())
        {
            if (!lines[finishedWindow].empty())
                lines[finishedWindow].pop();
            //若有顾客等待且处于营业时间，接待下一位顾客
            if (!lines[finishedWindow].empty() && time < (17 - 8) * 60)
            {
                finishAfterTime[finishedWindow] = needTime[lines[finishedWindow].front()];
                finishedTime[lines[finishedWindow].front()] = time + needTime[lines[finishedWindow].front()];
            }
            else if (customNth > K)
            {
                lines.erase(lines.begin() + finishedWindow);
                finishAfterTime.erase(finishAfterTime.begin() + finishedWindow);
            }
            finishedWindow = find_if(finishAfterTime.begin(), finishAfterTime.end(), [](int a) { return a = 0; }) - finishAfterTime.begin();
        }
        if (lines.empty())
            break;
    }
    for (auto i : query)
    {
        if (finishedTime[i] != -1)
            printf("%02d:%02d\n", finishedTime[i] / 60 + 8, finishedTime[i] % 60);
        else
            cout << "Sorry" << endl;
    }
    return 0;
}