#include<iostream>
#include<set>
#include<string.h>
#include<vector>
using namespace std;

#define V 10

int g[V][V];
set<int> visited;

bool kPath (int s, int k) {
    if (k <= 0) {
        return true;
    }
        
    visited.insert(s);

    for(int i = 0; i < V; i++) {
        if(g[s][i] && visited.find(i) == visited.end()) {
            if (kPath(i, k-g[s][i])) {
                return true;
            }
        }
    }

    visited.erase(s);
    return false;
}


int main() {
    int t;
    cin >> t;
    visited.insert(0);
    while(t) {
        int v, e, k;
        cin >> v;
        cin >> e;
        cin >> k;
        memset(g, 0, sizeof(g));
        visited.clear();
        for (int i = 0; i < e; i++) {
            int s,d,w;
            cin >> s;
            cin >> d;
            cin >> w;
            g[s][d] = w;
            g[d][s] = w;
        }

        cout << kPath(0, k) << endl;
        t--;
    }
}
