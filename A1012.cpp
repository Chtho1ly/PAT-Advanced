//https://pintia.cn/problem-sets/994805342720868352/problems/994805502658068480
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct student
{
    string id;
    double average;
    double c;
    double math;
    double english;
    int aNth;
    int cNth;
    int mNth;
    int eNth;
    student(string m, double i, double j, double k) : id(m), average((i + j + k) / 3), c(i), math(j), english(k){};
};

int main()
{
    int studentNum;
    int checkNum;
    cin >> studentNum >> checkNum;
    vector<student> tab;
    vector<string> checkList(checkNum);
    for (int i = 0; i < studentNum; i++)
    {
        string id;
        double c, m, e;
        cin >> id >> c >> m >> e;
        tab.push_back(student(id, c, m, e));
    }
    for (int i = 0; i < checkNum; i++)
        cin >> checkList[i];

    sort(tab.begin(), tab.end(), [](student a, student b) { return a.average > b.average; });
    for (int i = 0; i < studentNum; i++)
    {
        if (i != 0 && tab[i].average == tab[i - 1].average)
            tab[i].aNth = tab[i - 1].aNth;
        else
            tab[i].aNth = i + 1;
    }
    sort(tab.begin(), tab.end(), [](student a, student b) { return a.c > b.c; });
    for (int i = 0; i < studentNum; i++)
        if (i != 0 && tab[i].c == tab[i - 1].c)
            tab[i].cNth = tab[i - 1].cNth;
        else
            tab[i].cNth = i + 1;
    sort(tab.begin(), tab.end(), [](student a, student b) { return a.math > b.math; });
    for (int i = 0; i < studentNum; i++)
        if (i != 0 && tab[i].math == tab[i - 1].math)
            tab[i].mNth = tab[i - 1].mNth;
        else
            tab[i].mNth = i + 1;
    sort(tab.begin(), tab.end(), [](student a, student b) { return a.english > b.english; });
    for (int i = 0; i < studentNum; i++)
        if (i != 0 && tab[i].english == tab[i - 1].english)
            tab[i].eNth = tab[i - 1].eNth;
        else
            tab[i].eNth = i + 1;
    char dict[4] = {'A', 'C', 'M', 'E'};
    for (int i = 0; i < checkNum; i++)
    {
        string id = checkList[i];
        vector<student>::iterator checkStudent = find_if(tab.begin(), tab.end(), [id](student a) { return a.id == id; });
        if (checkStudent != tab.end())
        {
            vector<int> grade(4);
            grade[0] = checkStudent->aNth;
            grade[1] = checkStudent->cNth;
            grade[2] = checkStudent->mNth;
            grade[3] = checkStudent->eNth;
            int best = min_element(grade.begin(), grade.end()) - grade.begin();
            cout << grade[best] << " " << dict[best] << endl;
        }
        else
            cout << "N/A" << endl;
    }
    return 0;
}