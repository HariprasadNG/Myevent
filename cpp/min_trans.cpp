#include <iostream>
#include <string.h>
#include <set>
#include <map>

using namespace std;

int main () {
    int mat[1024][1024];
    memset(mat, 0, sizeof(mat));
    int p; int t;
    cin >> p;
    cin >> t;
    for (int i = 0 ; i < t; i++) {
        int f, t, a;
        cin >> f;
        cin >> t;
        cin >> a;
        mat[f][t] += a;
        mat[t][f] += a * -1;
    }
    
    multimap<int, int> G;
    multimap<int, int> R;

    for (int i = 0; i < p; i++) {
        int t = 0;
        for (int j = 0; j < p; j++) {
            t += mat[i][j];
        }
        if (t > 0) {
            G.emplace(t, i);
        }
        if (t < 0) {
            R.emplace(t*-1, i);
        }
    }

    for (auto x:R) {
        auto y = G.upper_bound(x.first);
        if ( y == G.end()) {
            int amount = x.first;    
            while (G.size() > 0 && amount >= G.rbegin()->first) {
                 amount -= G.rbegin()->first;
                 cout << G.rbegin()->second << "->" << x.second << ":" << G.rbegin()->first << endl;
                 G.erase(next(G.rbegin()).base());
            }
        } else {
         
            cout << y->second << "->" << x.second << ":" << x.first << endl;
            if (y->first == x.first) {
                G.erase(y);
            } else {
                int a = y->first - x.first;
                int p = y->second;
                G.erase(y);
                G.emplace(a,p);
            }
       }
    }
}
