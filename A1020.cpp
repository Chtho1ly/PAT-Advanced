//https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solution/
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct node
{
    int left = -1;
    int right = -1;
};

deque<int> inorderV;
deque<int> postorderV;
map<int, node> tree;

int root_of_Subtree(deque<int>::iterator beg, deque<int>::iterator end)
{
    int root = inorderV.back();
    inorderV.pop_back();
    deque<int>::iterator split = find(beg, end, root);
    if (split < end - 1)
        tree[root].right = root_of_Subtree(split + 1, end);
    if (split > beg)
        tree[root].left = root_of_Subtree(beg, split);
    return root;
}

int main()
{
    int n;
    cin >> n;
    inorderV.insert(inorderV.begin(), n, 0);
    postorderV.insert(inorderV.begin(), n, 0);
    for (int i = 0; i < n; i++)
        cin >> inorderV[i];
    for (int i = 0; i < n; i++)
        cin >> postorderV[i];
    int root = root_of_Subtree(postorderV.begin(), postorderV.end());
    queue<int> bfs;
    bfs.push(root);
    while (!bfs.empty())
    {
        int cur = bfs.front();
        bfs.pop();
        if (cur != root)
            cout << " ";
        cout << cur;
        if (tree[cur].left != -1)
            bfs.push(tree[cur].left);
        if (tree[cur].right != -1)
            bfs.push(tree[cur].right);
    }
    cout << endl;
    return 0;
}