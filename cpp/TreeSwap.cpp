#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Tree {
    public:
        int d;
        int l;
        int r;
        Tree(int x):d(x),l(-1),r(-1){};
};

void inorder (vector<Tree*> &v, int node) {
    if (v.size() <= 0) return;
    if (node == -1) return;
    inorder(v, v[node - 1]->l);
    cout << v[node-1]->d << " ";
    inorder(v, v[node - 1]->r);

}

void swapNodesLevel(vector<Tree*> &v, int cl) {
    queue<pair<int,int>> q;
    q.push(make_pair(1,1));
    while(!q.empty()) {
        int n = q.front().first;
        int l = q.front().second;
        q.pop();
        if (v[n-1]->l != -1) q.push(make_pair(v[n-1]->l, l+1));
        if (v[n-1]->r != -1) q.push(make_pair(v[n-1]->r, l+1));
        if ( l%cl == 0) {
            cout << "Swapping for node " << v[n-1]->d << endl;
            int temp = v[n-1]->l;
            v[n-1]->l = v[n-1]->r;
            v[n-1]->r = temp;
        }
    }
}

int main () {
    int n;
    cin >> n;
    if (n == 0) return 0;
    vector<Tree*> v;
    int i = 1;
    while (n) {
        v.push_back(new Tree(i++));
        int left, right;
        cin >> left;
        cin >> right;
        v[i-2]->l = left;
        v[i-2]->r = right;
        n--;
    }
    int t;
    cin >> t;
    vector<int> swaps;
    while (t) {
        int node;
        cin >> node;
        swaps.push_back(node);
        t--;
        
    }
    for (auto x:swaps) {
    //for (int i = swaps.size() - 1; i >= 0; i--) {
        swapNodesLevel(v, x);
        //cout << "Swapping " << swaps[i] << endl;
        //swapNodesLevel(v, swaps[i]);
        inorder(v, 1);
        cout << endl;
    }
}
