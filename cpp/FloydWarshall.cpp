#include<iostream>
#include<vector>

using namespace std;
typedef unsigned int uint;
#define MAX_W 10000

class Node {
    public:
        int p;
        int w;
    Node() {
        p = -1;
        w = MAX_W;
    }
};

void FW (vector<vector<Node> > &G) {
    for (uint rc = 0; rc < G.size(); rc++) { //Intermdeiaty Node
        for (uint i = 0; i < G.size(); i++) {
            for (uint j = 0; j < G.size(); j++) {
                if (i == rc || j == rc){
                    //Skip this column or row
                } else if (G[i][j].w > G[i][rc].w + G[rc][j].w) { //Path from source to Intermediatry Node from Intermediatry Node to destination
                    G[i][j].w = G[i][rc].w + G[rc][j].w;
                    G[i][j].p = rc;
                }
            }
        }
    }
}

void trace(vector<vector<Node>> &G, int s, int d) {
    cout << d << "<-";
    if (s == d) return;
    trace(G, s, G[s][d].p);
}

int main () {
    int nodes;
    cin >> nodes;
    vector<vector<Node> > G(nodes, vector<Node>(nodes));
    int edges;
    cin >> edges;
    while (edges--) {
        int s, d, w;
        cin >> s >> d >> w;
        G[s][d].p = s;
        G[s][d].w = w;
    }
    for (uint i = 0; i < G.size(); i++) {
        G[i][i].w = 0;
        G[i][i].p = i;
    }
    FW(G);
    int T;
    cin >> T;
    while (T--) {
        int s, d;
        cin >> s >> d;
        trace(G, s, d);
        cout << endl;
    }
}
