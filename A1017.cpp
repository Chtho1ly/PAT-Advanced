//https://pintia.cn/problem-sets/994805342720868352/problems/994805491530579968
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#define INF 0x3fffff

using namespace std;

struct window
{
    int clientNth = -1;   //正在服务的客户序号，无客户时为-1
    int finishTime = INF; //完成时刻，无客户时为INF
    bool operator<(window &w)
    {
        return finishTime < w.finishTime;
    }
};

struct client
{
    int nth;      //客户序号
    int comeTime; //客户到来时刻
    int needTime; //客户业务需要时间
    bool operator<(client &c)
    {
        return comeTime < c.comeTime;
    }
};

int main()
{
    int N, K;
    cin >> N >> K;
    vector<window> windowV(K); //窗口信息
    deque<client> clientV;     //客户信息
    vector<int> waitTime;      //客户等待的时间，单位为秒
    //输入客户信息并筛选在关门前到达的客户
    for (int i = 0; i < N; i++)
    {
        client t;
        int h, m, s;
        scanf("%d:%d:%d", &h, &m, &s);
        cin >> t.needTime;
        t.needTime *= 60;
        t.comeTime = s + 60 * (m + 60 * h);
        if (t.comeTime <= 60 * 60 * 17)
        {
            clientV.push_back(t);
        }
    }
    //将客户按到达先后排序
    sort(clientV.begin(), clientV.end());
    //将客户编号
    for (size_t i = 0; i < clientV.size(); i++)
        clientV[i].nth = i;
    //按到达时刻顺序对客户进行处理
    int time = 60 * 60 * 8;
    while (true)
    {
        while (!clientV.empty() && clientV.front().comeTime <= time)
        { //若有客户已到达
            client curClient = clientV.front();
            auto windowEmpty = find_if(windowV.begin(), windowV.end(), [](window w) { return w.clientNth == -1; });
            //若无空闲窗口，时间推进
            if (windowEmpty == windowV.end())
                break;
            else
            { //若有空闲窗口，接待客户，记录客户等待的时间
                windowEmpty->clientNth = curClient.nth;
                windowEmpty->finishTime = time + curClient.needTime;
                waitTime.push_back(time - curClient.comeTime);
                clientV.pop_front();
            }
        }

        //若有窗口空闲，则时间推进至有窗口完成服务或有客户到达
        if (find_if(windowV.begin(), windowV.end(), [](window w) { return w.clientNth == -1; }) != windowV.end())
        {
            time = min_element(windowV.begin(), windowV.end())->finishTime;
            if (!clientV.empty())
                time = min(time, clientV.front().comeTime);
        }
        //否则，时间推进至有窗口完成服务
        else
            time = min_element(windowV.begin(), windowV.end())->finishTime;
        //处理服务结束的窗口
        for (auto &w : windowV)
        {
            if (w.finishTime <= time)
            {
                w.clientNth = -1;
                w.finishTime = INF;
            }
        }
        if (clientV.empty() && find_if(windowV.begin(), windowV.end(), [](window w) { return w.clientNth != -1; }) == windowV.end())
            break;
    }
    double avg;
    for (auto i : waitTime)
        avg += i;
    printf("%.1lf\n", avg / waitTime.size() / 60);
    return 0;
}