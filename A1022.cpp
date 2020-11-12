//https://pintia.cn/problem-sets/994805342720868352/problems/994805480801550336
//谨慎关同步
//注意数据格式，输出int时注意要求位数
#include <algorithm>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<int>> titles;
unordered_map<string, vector<int>> authors;
unordered_map<string, vector<int>> keywords;
unordered_map<string, vector<int>> publishers;
unordered_map<string, vector<int>> years;

vector<int> library;

struct query
{
    int mode;
    string contain;
};

int main()
{
    int n;
    scanf("%d", &n);
    //书籍信息
    for (int i = 0; i < n; i++)
    {
        int id;
        string title;
        string author;
        string word;
        string publisher;
        string year;
        scanf("%d", &id);
        getchar(); //接收后面的换行，否则会出现读取错误数据的情况
        library.push_back(id);
        getline(cin, title);
        getline(cin, author);
        while (cin >> word)
        {
            keywords[word].push_back(id);
            char c = getchar();
            if (c == '\n')
                break;
        }
        getline(cin, publisher);
        getline(cin, year);
        titles[title].push_back(id);
        authors[author].push_back(id);
        publishers[publisher].push_back(id);
        years[year].push_back(id);
    }
    scanf("%d", &n);
    //将所有书按id排序
    for (auto &i : titles)
        sort(i.second.begin(), i.second.end());
    for (auto &i : authors)
        sort(i.second.begin(), i.second.end());
    for (auto &i : keywords)
        sort(i.second.begin(), i.second.end());
    for (auto &i : publishers)
        sort(i.second.begin(), i.second.end());
    for (auto &i : years)
        sort(i.second.begin(), i.second.end());
    //查询请求
    vector<query> queryV;
    for (int i = 0; i < n; i++)
    {
        query t;
        scanf("%d: ", &t.mode);
        getline(cin, t.contain);
        queryV.push_back(t);
    }
    //相应查询
    for (auto q : queryV)
    {
        cout << q.mode << ": " << q.contain << endl;
        switch (q.mode)
        {
        case (1):
        {
            if (titles[q.contain].empty())
                cout << "Not Found" << endl;
            else
            {
                for (auto i : titles[q.contain])
                    printf("%07d\n",i);
            }
            break;
        };
        case (2):
        {
            if (authors[q.contain].empty())
                cout << "Not Found" << endl;
            else
            {
                for (auto i : authors[q.contain])
                    printf("%07d\n",i);
            }
            break;
        };
        case (3):
        {
            if (keywords[q.contain].empty())
                cout << "Not Found" << endl;
            else
            {
                for (auto i : keywords[q.contain])
                    printf("%07d\n",i);
            }
            break;
        };
        case (4):
        {
            if (publishers[q.contain].empty())
                cout << "Not Found" << endl;
            else
            {
                for (auto i : publishers[q.contain])
                    printf("%07d\n",i);
            }
            break;
        };
        case (5):
        {
            if (years[q.contain].empty())
                cout << "Not Found" << endl;
            else
            {
                for (auto i : years[q.contain])
                    printf("%07d\n",i);
            }
            break;
        };
        default:
            break;
        }
    }
    return 0;
}