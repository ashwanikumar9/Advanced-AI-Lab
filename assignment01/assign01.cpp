#include <bits/stdc++.h>
using namespace std;
int noOfDays(int k, int n, int tot, vector<int> seq, vector<int> &prompt)
{
    vector<int> vtillnow;
    int days = 0;
    vector<int> stud(n);
    for (int i = 0; i < n; i++)
    {
        stud[i] = k;
    }
    for (int i = 0; i < seq.size(); i++)
    {
        bool change = false;
        for (int j = 0; j < n; j++)
        {
            if (stud[j] > prompt[i])
            {
                stud[j] -= prompt[i];
                change = true;
                break;
            }
        }
        if (!change)
        {
            days++;
            for (int i = 0; i < n; i++)
            {
                stud[i] = k;
            }
        }
    }
    return days;
}
bool checkValid(vector<int> v, int n, int k, int assignNo, vector<vector<int>> &dep)
{
    vector<int> vtillnow;
    for (int i = 0; i < v.size(); i++)
    {
        if (dep[v[i]].size() > 0)
        {
            int c = 0;
            for (int k = 0; k < dep[v[i]].size(); k++)
            {

                for (int j = 0; j < vtillnow.size(); j++)
                {
                    if (vtillnow[j] == dep[v[i]][k])
                    {
                        c++;
                    }
                }
            }
            if (dep[v[i]].size() != c)
                return false;
        }
        vtillnow.push_back(v[i]);
    }
    return true;
}
void permutation(vector<int> &v, int l, int r, vector<vector<int>> &res, int n, int k, vector<vector<int>> &dep)
{
    if (l == r)
    {
        vector<int> vp;
        for (int i = 0; i <= r; i++)
        {
            vp.push_back(v[i]);
        }
        if (checkValid(vp, n, k, r, dep))
        {
            res.push_back(vp);
        }

        return;
    }
    for (int i = l; i <= r; i++)
    {
        swap(v[i], v[l]);
        permutation(v, l + 1, r, res, n, k, dep);
        swap(v[i], v[l]);
    }
}
int main()
{

    int n, k, assignNo;
    cin >> n >> k >> assignNo;
    vector<vector<int>> dep(assignNo + 1);
    vector<int> ids;
    vector<int> prompt(assignNo + 1, 0);
    for (int i = 0; i < assignNo; i++)
    {
        int id;
        char a;
        cin >> a;
        cin >> id;
        ids.push_back(id);
        cin >> prompt[id];
        vector<int> inp;
        int b = -1;
        cin >> b;
        while (b != 0)
        {
            inp.push_back(b);
            cin >> b;
        }
        dep[id] = inp;
    }
    int m;
    cin >> m;
    vector<vector<int>> res;
    int count = 0;
    permutation(ids, 0, ids.size() - 1, res, n, k, dep);
    for (int i = 0; i < res.size(); i++)
    {
        int days = noOfDays(k, n, assignNo, res[i], prompt);

        if (days <= m)
        {
            for (int j = 0; j < res[i].size(); j++)
            {
                cout << res[i][j] << " ";
            }
            cout << days << endl;
        }
    }

    return 0;
}
