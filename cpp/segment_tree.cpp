#include <iostream>
#include <vector>
#include <limits>
#define LEFT(x) (2*x + 1)
#define RIGHT(x) (2*x + 2)
using namespace std;

void buildSegTree(vector<int> &tree, vector<int> ip, int n, int s, int e) {
    if ( s > e) return;
    if ( s == e) {
        if( ((int)tree.size() - 1) < n) {
            tree.resize( n +1);
        }
        tree[n] = ip[e];
        return;
    }

    buildSegTree(tree, ip, LEFT(n), s, (s + e) >> 1);
    buildSegTree(tree, ip, RIGHT(n), ((s + e) >> 1)+1, e);

    tree[n] = max(tree[LEFT(n)], tree[RIGHT(n)]);
}

void updateTree(int idx, vector<int> ip, vector<int> tree, int off, int s, int e) {
    if ( s > e) return;
    if (s == e) {
        tree[s]=ip[idx];
        return;
    }
    if (ip[idx] > tree[off]) {
        tree[off] = ip[idx];
    }

    if (idx >= RIGHT(off)) {
        updateTree(idx, ip, tree, RIGHT(off), RIGHT(off), e);
    } else {
        updateTree(idx,ip,tree, LEFT(off), s, LEFT(off));
    }
}

int queryTree(vector<int> &tree, int l, int r, int s, int e, int n) {
    if ( s < l && r > e) {
        return numeric_limits<int>::min();
    } else if ( l >= s && r <= e) {
        return tree[n];
    }

    int lq = numeric_limits<int>::min(), rq = numeric_limits<int>::min();
    lq = queryTree(tree, l, LEFT(n), s, LEFT(n),LEFT(n));
    rq = queryTree(tree, RIGHT(n), e, RIGHT(n), e, RIGHT(n));
    return max(lq,rq);
}
int main () {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> ip;
        vector<int> tree;
        while (n--) {
            int x;
            cin >> x;
            ip.push_back(x);
        }
        buildSegTree(tree, ip, 0, 0, ip.size()-1);
        int q;
        cin >> q;
        while(q--) {
           int l, r;
           cin >> l >> r;
           cout << queryTree(tree, l, r, 0, ip.size() - 1, 0);
        }
    }
}
