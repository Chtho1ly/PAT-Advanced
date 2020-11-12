//https://pintia.cn/problem-sets/994805342720868352/problems/994805474338127872
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct grade
{
    string id;
    int score;
    int block;
    int nthLocal;
    int nthTotal;
    bool operator<(grade &g)
    {
        if (score != g.score)
            return score > g.score;
        else
            return id < g.id;
    };
};

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<grade> grades;
    for (int block = 1; block <= n; block++)
    {
        int cnt;
        cin >> cnt;
        vector<grade> localGrades;
        while (cnt--)
        {
            grade t;
            cin >> t.id >> t.score;
            t.block = block;
            localGrades.push_back(t);
        }
        sort(localGrades.begin(), localGrades.end());
        localGrades.front().nthLocal = 1;
        for (auto i = localGrades.begin() + 1; i < localGrades.end(); i++)
        {
            if (i->score == (i - 1)->score)
                i->nthLocal = (i - 1)->nthLocal;
            else
                i->nthLocal = i - localGrades.begin() + 1;
        }
        grades.insert(grades.begin(), localGrades.begin(), localGrades.end());
    }
    sort(grades.begin(), grades.end());
    grades.front().nthTotal = 1;
    for (auto i = grades.begin() + 1; i < grades.end(); i++)
    {
        if (i->score == (i - 1)->score)
            i->nthTotal = (i - 1)->nthTotal;
        else
            i->nthTotal = i - grades.begin() + 1;
    }
    cout << grades.size() << endl;
    for(auto i:grades)
        cout << i.id << " " << i.nthTotal << " " << i.block << " " << i.nthLocal << endl;
    return 0;
}