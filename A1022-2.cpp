#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
void query(unordered_map<string, set<int>> &m, const string &s)
{                                                           //进行查询
    if (m.find(s) == m.cend())                              //如果在m中查找不到s
        printf("Not Found\n");                              //输出没有找到
    else                                                    //如果找到了
        for (auto i = m[s].cbegin(); i != m[s].cend(); ++i) //按增序输出对应的id
            printf("%07d\n", *i);
}
int main()
{
    int N;
    scanf("%d", &N);
    unordered_map<string, set<int>> title, author, key, publisher, year;
    string s;
    while (N--)
    {
        int id;
        scanf("%d", &id);
        getchar(); //接收后面的换行，否则会出现读取错误数据的情况
        getline(cin, s);
        title[s].insert(id);
        getline(cin, s);
        author[s].insert(id);
        while (cin >> s)
        { //读取关键词
            key[s].insert(id);
            char c = getchar(); //读取关键词后的字符
            if (c == '\n')      //如果是换行符，读取关键词结束
                break;
        }
        getline(cin, s);
        publisher[s].insert(id);
        getline(cin, s);
        year[s].insert(id);
    }
    scanf("%d", &N);
    while (N--)
    {
        int m;
        scanf("%d: ", &m); //读取查询类型
        getline(cin, s);   //读取要查询的字符串
        printf("%d: %s\n", m, s.c_str());
        if (m == 1) //进行查询
            query(title, s);
        else if (m == 2)
            query(author, s);
        else if (m == 3)
            query(key, s);
        else if (m == 4)
            query(publisher, s);
        else if (m == 5)
            query(year, s);
    }
    return 0;
}