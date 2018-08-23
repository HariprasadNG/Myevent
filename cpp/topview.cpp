#include<iostream>
#include<queue>
#include<utility>
using namespace std;

class Tree {
    public:
        int n;
        Tree *l, *r;
        Tree(int x):n(x),l(NULL), r(NULL) {};
        Tree():n(0),l(NULL), r(NULL) {};
};

bool check (int &l, int &r, int c) {
    bool ret = (l >= c || r <= c);
    if (l >= c) l--;
    if (r <= c) r++;
    return ret;
}

//This has problem since it prints 11 which is below 1 
//and this will not print 1 So need to impliment same 
//using level order traversal principal.
void PrintTopView(Tree* r, int &lc, int &rc, int c) {
    if (r == NULL) return;
    if (check(lc, rc, c) ) {
        cout << r->n << " ";
    }
    PrintTopView(r->l, lc, rc, c-1);
    PrintTopView(r->r, lc, rc, c+1);
}

void LevelPrintTopView(Tree *r) {
    if (r == NULL) return;
    queue<pair<Tree*, int>> q;
    q.push(make_pair(r, 0));
    int lr = 0, rr = 0;
    while (!q.empty()) {
        Tree* n = q.front().first;
        int c  = q.front().second;
        q.pop();
        if (check(lr, rr, c)) {
            cout << n->n << " ";
        }
        if (n->l) {
            q.push(make_pair(n->l, c-1));
        }
        if (n->r) {
            q.push(make_pair(n->r, c+1));
        }
    }
}
int main () {
    Tree *t = new Tree(0);
    t->l = new Tree(-1);
    t->r = new Tree(1);
    t->l->l = new Tree(-2);
    t->l->r = new Tree(-11);
    t->l->r->l = new Tree(-21);
    t->l->r->l->l = new Tree(-30);
    t->l->r->r = new Tree(-10);
    t->l->r->r->r = new Tree(11);
    int lc = 0, rc = 0;
    PrintTopView(t, lc, rc, 0);
    cout << endl;
    LevelPrintTopView(t);
    cout << endl;
}
