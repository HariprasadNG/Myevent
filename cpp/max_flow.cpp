#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
typedef unsigned int uint;

class Node {
    public:
        int c;
        int rc;
        Node():c(0),rc(0) {
        };
};

vector<int> BFS(vector<vector<Node> > &G, int s, int t) {
    queue<int> Q;
    Q.push(s);
    vector<int> R;
    vector<pair<int, int>> P(G.size(), {-1, 0});
    P[s] = {-1, 1};
    while(!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (uint i = 0; i < G[x].size(); i++) {
            if (G[x][i].rc > 0 && P[i].second == 0) {
                P[i].first = x; //Parent;
                P[i].second = 1; //Visited;
                Q.push(i);
                if ( i == t) {
                    //Found some augmenting path
                    int p = t;
                    while (p != s) {
                        R.push_back(p);
                        p = P[p].first;
                    }
                    R.push_back(s);
                    return R;
                }
            }
        }
    }
    return R;
}

int minOverPath(vector<int> P, vector<vector<Node>> &G) {
    int s = P[P.size() - 1];
    P.pop_back();
    int min = 1000000;
    while (P.size()) {
        int t = P[P.size() - 1];
        P.pop_back();
        if (min > G[s][t].rc) {
            min = G[s][t].rc;
        }
        s = t;
    }
    return min;
}

void makeGdash(vector<int> P, vector<vector<Node>> &G, int m) {
    int s = P[P.size() - 1];
    P.pop_back();
    while (P.size()) {
        int t = P[P.size() - 1];
        P.pop_back();
        G[s][t].rc -= m;
        G[t][s].rc += m;
        s = t;
    }
}

int MaxFlow(vector<vector<Node> >&G, int s, int t) {
    int f = 0;
    int al = 0;
    do {
        vector<int> a = BFS(G, s, t); //Find augment path
        al = a.size();
        if (al) {
            int min = minOverPath(a, G); //Find bottleneck in the path
            f += min;
            makeGdash(a, G, min); //Make residual graph
        }
    } while (al); //While there are more augment path repeate.
    return f;
}

int main () {
    int nodes;
    cin >> nodes;
    vector<vector<Node> > G(nodes, vector<Node>(nodes));
    int e;
    cin >> e;
    int s, t;
    while (e) {
        int t1, t2;
        cin >> t1 >> t2;
        cin >> G[t1][t2].c;
        G[t1][t2].rc = G[t1][t2].c;
        e--;
    }

    cin >> s >> t;
    cout << MaxFlow(G, s, t);
    return 0;
}
