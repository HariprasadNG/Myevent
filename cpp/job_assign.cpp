#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int optJob(vector<vector<int>> &jb, int sp, vector<int> &compJobs) {
    int opt = numeric_limits<int>::max();;
    if (sp == jb.size()) return 0;
    for (int i = 0; i < jb.size(); i++) {
        if (find(compJobs.begin(), compJobs.end(), i)!= compJobs.end()) continue;
        compJobs.push_back(i);
        int x = jb[sp][i] + optJob(jb, sp+1, compJobs);
        compJobs.pop_back();
        opt = min(x, opt);
    }
    return opt;
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        int p;
        cin >> p;
        vector<vector<int>> v;
        int x = 0;
        while(x != p) {
            int tp = p;
            vector<int> temp;
            v.push_back(temp);
            while (tp--) {
                int t;
                cin >> t;
                v[x].push_back(t);
            }
            x++;
        }

        vector<int> compJobs;
        cout << optJob(v, 0, compJobs) << endl;
    }
}
