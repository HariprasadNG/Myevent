#include<iostream>
#include<vector>
#include<stack>
#include<utility>
#include<deque>
#include<queue>
#include<algorithm>
using namespace std;
class Node {
    public:
        int st, et;
        int id;
        int low;
        bool AP;
        int p;
        Node():st(-1),et(-1),low(100000),AP(false),p(-1) {

        };
};

void DFS_Articulation(
        vector<vector<int> > &E, 
        vector<Node> &N, 
        int s, 
        int &t, 
        int p = -1) {
    N[s].st = t;
    N[s].p = p;
    int child = 0; //Required to identify root as AP or not
    for (int i = 0; i < E.size(); i++) {
        if (i != s && E[s][i] && N[i].st > -1) && N[s].p != i) {
            //This is a back edge update the node to which it  points in DFS tree
            //Since all the below nodes are no articulation points.
            N[s].low = min(N[s].low, N[i].st);
        } else if (i != s && E[s][i] && N[i].st == -1) {
            child++;
            t++;
            DFS_Articulation(E, N, i, t, s);
            N[s].low = min(N[s].low, N[i].low);
            // p == -1 means root of the DFS tree child > 0 means 
            // there is no deep connection between childs other then 
            // via root so root is AP
            if (N[s].p == -1 && child > 1) {
                N[s].AP = true;
            }
            else if (N[s].p != -1 && N[s].st <= N[s].low) {
                N[s].AP = true;
            }
        }
    }
    N[s].et= ++t;
}

int main() {
    stack<Node> ap;
    int n;
    int e;
    cin >> n >> e;
    vector<vector<int> > E(n, vector<int>(n));
    vector<Node> N(n);
    for (int i = 0; i < n; i++) {
        N[i].id = i + 1;
    }
    while (e--) {
        int s, d;
        cin >> s >> d;
        E[s-1][d-1] = 1;
        E[d-1][s-1] = 1;
    }
    int t = 0;
    DFS_Articulation(E, N, 0, t);
    cout << "*********************" << endl;
    for (auto x: N) {
        if (x.AP) {
            cout << x.id << " " ;
        }
    }
    cout << endl << "*********************" << endl;
}
