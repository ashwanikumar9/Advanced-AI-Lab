#include <bits/stdc++.h>
using namespace std;

int noOfDaysWithoutMeeting(int k, int n, vector<int> seq, vector<int> &prompt, vector<vector<int>> depend)
{
    int days = 0;
    vector<int> stud(n);
    vector<vector<pair<int, int>>> s(n + 1);
    for (int i = 0; i < n; i++)
    {
        stud[i] = k;
    }
    for (int i = 0; i < seq.size(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (stud[j] >= prompt[seq[i]] )
            {
                pair<int, int> pi({seq[i], days});
                stud[j] -= prompt[seq[i]];
                s[j + 1].push_back(pi);
            }
        }
    }
    // for (int i = 0; i < seq.size(); i++)
    // {
    //     bool change = false;
    //     for (int j = 0; j < n; j++)
    //     {
    //         if (stud[j] > prompt[i])
    //         {
    //             stud[j] -= prompt[i];
    //             change = true;
    //             break;
    //         }
    //     }
    //     if (!change)
    //     {
    //         days++;
    //         for (int i = 0; i < n; i++)
    //         {
    //             stud[i] = k;
    //         }
    //     }
    // }
    return days;
}
int noOfDays(int k, int n, vector<int> seq, vector<int> &prompt)
{
    int days = 1;
    vector<int> stud(n, k);
    for (int i = 0; i < seq.size(); )
    {
        bool change = false;
        for (int j = 0; j < n; j++)
        {
            if (stud[j] >= prompt[seq[i]])
            {
                stud[j] -= prompt[seq[i]];
                change = true;
                i++;
                break;
            }
        }
        if (!change)
        {
            for(int i=0; i<n; i++){
                stud[i]=k;
            }
            days++;
        }
    }
// end:
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
    int mindays = INT_MAX;
    permutation(ids, 0, ids.size() - 1, res, n, k, dep);
    for (int i = 0; i < res.size(); i++)
    {
        int days = noOfDays(k, n, res[i], prompt);
        mindays = min(mindays, days);
        if (days <= m)
        {
            for (int j = 0; j < res[i].size(); j++)
            {
                cout << res[i][j] << " ";
            }
            cout << days << endl;
        }
    }
    cout << mindays << endl;

    return 0;
}
