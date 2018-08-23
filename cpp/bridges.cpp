#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
class Node {
    public:
        int st, et, id, p, low;
        Node():st(-1), et(-1), p(-1), low(100000) {

        }
};

void DFS_Bridge(vector<vector<int> > &E, vector<Node> &N, int s, int &t, vector<pair<int,int>> &B, int p = -1) {
    N[s].p = p;
    N[s].st = t++;
    for (unsigned int i = 0; i < N.size(); i++ ) {
        if (E[s][i] && N[i].st > -1 && N[s].p != i) {
            //Back Edge update the low to the node which is reachable from this nodes
            //so all the edges below this backedge dest cant be articulation points and
            //all the edges below this cant be bridges.
            N[s].low = min(N[s].low, N[i].st);
        } else if(E[s][i] && N[i].st == -1) {
           DFS_Bridge(E, N, i, t, B, s);
           N[s].low = min(N[s].low, N[i].low);
           if (N[s].low > N[s].st) {
              //This is node is above the backedge destination node
              //so the edge from this node to the backedge destination
              //is a bridge so removing that will make graph as 2 components.
              B.push_back({s, i});
           }
        }
    }
    N[s].et = t++;
}

int main () {
    int n, e;
    cin >> n >> e;
    vector<Node> N(n);
    for (int i = 0; i < n; i++) {
        N[i].id = i + 1;
    }
    vector<vector<int> > E(n, vector<int>(n, 0));
    while (e--) {
       int s, d;
       cin >> s >> d;
       E[s-1][d-1] = 1;
       E[d-1][s-1] = 1;
    }
    vector<pair<int,int>> B;
    int t = 0;
    DFS_Bridge(E, N, 0, t, B);
    cout << "**********************" << endl;
    for (auto x: B) {
        cout << x.first + 1 << " " << x.second + 1 << endl;
    }
    cout << "**********************" << endl;
}
