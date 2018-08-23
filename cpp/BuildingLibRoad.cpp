#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
typedef long long int llint;
llint BFS(vector<vector<llint>> &v, vector<llint> &d, llint s) {
    queue<llint> q;
    q.push(s);
    llint r = 0;
    while(!q.empty()) {
        s = q.front();
        q.pop();
        for (auto x: v[s]) {
            if (d[x] == -1) {
                q.push(x);
                d[x] = 1;
                r++;
            }
        }
    }
    return r;
}
llint connectedCompCost (vector<vector<llint>> &v, llint cl, llint cr) {
    vector<llint> d;
    for (llint i = 0; i < v.size(); i++) {
        d.push_back(-1);
    }
    llint c = 0;
    while(true) {
        bool find = false;
        llint id = 0;
        for (;id < d.size(); id++) {
            if (d[id] == -1) {
                d[id] = 0;
                find = true;
                break;
            }
        }
        if (!find) break;
        c += cr * BFS(v, d, id) + cl;
    }
    return c;
}

int main () {
    llint T;
    cin >> T;
    while(T--) {
        llint n, m, cl, cr;
        cin >> n >> m >> cl >> cr;
        vector<vector<llint>> v(n);
        while(m--) {
            llint s, e;
            cin >> s >> e;
            v[s-1].push_back(e-1);
            v[e-1].push_back(s-1);
        }

        if (cl > cr) {
            cout << connectedCompCost(v, cl, cr) << endl;
        } else {
            cout << cl * n << endl;
        }
    }
}
