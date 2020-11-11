//https://pintia.cn/problem-sets/994805342720868352/problems/994805489282433024
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#define INF 0x3fffff

using namespace std;

struct road
{
    int destination;
    int cost;
    bool operator<(road &r)
    {
        return cost < r.cost;
    }
};

struct node
{
    vector<road> neighbors;
    int bikeNum = 0;
    bool visted = false;
    int distance = INF;
    vector<int> pre;
    bool operator<(node &n)
    {
        if (visted != n.visted)
            return visted < n.visted;
        else
            return distance < n.distance;
    }
};

struct path
{
    vector<int> nodes;
    int leaveNum;
    int backNum;
    bool operator<(path &p)
    {
        if (leaveNum < p.leaveNum)
            return leaveNum < p.leaveNum;
        else
            return backNum < p.backNum;
    }
};

int C, N, S, M; //容量，node数量，终点序号，road数量
vector<node> nodeV;

vector<path> paths;
path curPath;

void DFS(int curNode)
{
    curPath.nodes.push_back(curNode);
    //若到达起点，将路径加入paths
    if (curNode == 0)
    {
        int carry = 0; //当前携带自行车数量
        //计算出发时携带自行车数量
        for (auto i = curPath.nodes.rbegin() + 1; i < curPath.nodes.rend(); i++)
        {
            //若当前节点自行车数量过多，拿走冗余自行车
            if (nodeV[*i].bikeNum > C / 2)
                carry += nodeV[*i].bikeNum - C / 2;
            //若当前节点自行车数量过少，补充自行车
            else if (nodeV[*i].bikeNum < C / 2)
            {
                int need = C / 2 - nodeV[*i].bikeNum; //需要自行车数量
                //若当前携带自行车足够补充，不需要额外携带
                if (carry >= need)
                    carry -= need;
                //若当前携带自行车不够补充，出发时需额外携带
                else
                {
                    curPath.leaveNum += need - carry;
                    carry = 0;
                }
            }
        }
        //调整完所有节点后身上携带的自行车数量就是返回时携带的数量
        curPath.backNum = carry;
        paths.push_back(curPath);
        curPath.leaveNum = 0;
        curPath.backNum = 0;
        curPath.nodes.pop_back();
        return;
    }
    //若未到达起点，尝试当前节点所有前驱
    for (auto nextNode : nodeV[curNode].pre)
        DFS(nextNode);
    curPath.nodes.pop_back();
    return;
}

int main()
{
    //输入数据规模
    cin >> C >> N >> S >> M;
    nodeV.insert(nodeV.begin(), N + 1, node());
    //输入各节点自行车数量
    for (int i = 1; i <= N; i++)
        cin >> nodeV[i].bikeNum;
    //输入道路信息
    for (int i = 0; i < M; i++)
    {
        int beg, end, cost;
        cin >> beg >> end >> cost;
        road begT, endT;
        begT.destination = end;
        begT.cost = cost;
        nodeV[beg].neighbors.push_back(begT);
        endT.destination = beg;
        endT.cost = cost;
        nodeV[end].neighbors.push_back(endT);
    }
    //使用dijkstra求最短路
    nodeV[0].distance = 0;
    for (int i = 0; i <= N; i++)
    {
        //访问最近的城市
        auto curNode = min_element(nodeV.begin(), nodeV.end());
        curNode->visted = true;
        //更新邻居的距离
        for (auto roadToNeighbor : curNode->neighbors)
        {
            //若当前访问节点的邻居未被访问，则尝试更新其distance
            if (!nodeV[roadToNeighbor.destination].visted)
            {
                //若通过当前节点访问邻居使其distance变小，则更新邻居前驱为当前节点
                if (nodeV[roadToNeighbor.destination].distance > curNode->distance + roadToNeighbor.cost)
                {
                    nodeV[roadToNeighbor.destination].distance = curNode->distance + roadToNeighbor.cost;
                    nodeV[roadToNeighbor.destination].pre.clear();
                    nodeV[roadToNeighbor.destination].pre.push_back(curNode - nodeV.begin());
                }
                //若通过当前节点访问邻居与其原距离相同，则将当前节点添加到邻居的前驱
                else if (nodeV[roadToNeighbor.destination].distance == curNode->distance + roadToNeighbor.cost)
                    nodeV[roadToNeighbor.destination].pre.push_back(curNode - nodeV.begin());
            }
        }
    }
    //使用DFS搜索满足路径最短、带走自行车最少，带回自行车最少的路径
    DFS(S);
    auto finalPath = min_element(paths.begin(), paths.end());
    cout << finalPath->leaveNum << " ";
    for (auto i = finalPath->nodes.rbegin(); i < finalPath->nodes.rend(); i++)
    {
        cout << *i;
        if (i != finalPath->nodes.rend() - 1)
            cout << "->";
    }
    cout << " " << finalPath->backNum << endl;
    return 0;
}