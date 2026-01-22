#include <bits/stdc++.h>
using namespace std;

int countx=0;
void printSchedule(const vector<vector<vector<int>>>& sched, int m, int n) {
    for (int d = 0; d < m; d++) {
        cout << "Day " << (d + 1) << ":" << endl;
        for (int s = 0; s < n; s++) {
            cout << "S" << (s + 1) << ":";
            for (int task : sched[d][s]) {
                cout << " A" << task;
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "---------------------" << endl;
}

void dfsSchedule(int id, int currentDay, vector<int>& caps, vector<vector<vector<int>>>& scheduleLog,vector<int>& seq, vector<int>& prompt, int n, int k, int m) {
    if (id == seq.size()) {
        // printSchedule(scheduleLog, m, n);
        countx++;
        return;
    }
    if (currentDay > m) {
        return;
    }

    int taskId = seq[id];
    int cost = prompt[taskId];
    bool today = false;
    for (int s = 0; s < n; s++) {
        if (caps[s] >= cost) {
            caps[s] -= cost;
            scheduleLog[currentDay - 1][s].push_back(taskId);
            dfsSchedule(id + 1, currentDay, caps, scheduleLog, seq, prompt, n, k, m);
            scheduleLog[currentDay - 1][s].pop_back();
            caps[s] += cost;
            
            today = true;
        }
    }
    if (currentDay < m) {
        vector<int> next(n, k);
        dfsSchedule(id, currentDay + 1, next, scheduleLog, seq, prompt, n, k, m);
    }
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

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <input-filename> <number-of-days>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    int m = atoi(argv[2]);
    int n = 0, k = 0;
    vector<vector<int>> dep(200);
    vector<int> prompt(200, 0);
    vector<int> ids;

    string token;
    while (infile >> token) {
        if (token == "%") {
            string dummy;
            getline(infile, dummy);
        }
        else if (token == "N") {
            infile >> n;
        }
        else if (token == "K") {
            infile >> k;
        }
        else if (token == "A") {
            int id, p;
            infile >> id >> p;
            ids.push_back(id);
            prompt[id] = p;

            vector<int> inp;
            int b;
            while (infile >> b && b != 0) {
                inp.push_back(b);
            }
            dep[id] = inp;
        }
    }
    infile.close();

    vector<vector<int>> res;
    permutation(ids, 0, ids.size() - 1, res, n, k, dep);

    for (int i = 0; i < res.size(); i++)
    {
      vector<vector<vector<int>>> scheduleLog(m, vector<vector<int>>(n));
      vector<int> initialCaps(n, k);
      dfsSchedule(0, 1, initialCaps, scheduleLog, res[i], prompt, n, k, m);
    }
    cout<<countx<<endl;
    return 0;
}