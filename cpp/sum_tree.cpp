#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;

class Tree {
    public:
        Tree *l;
        Tree *r;
        int d;
        Tree(int x):d(x),l(NULL),r(NULL){};
};

bool isLeaf(Tree *t) {
    if (t == NULL) return false;
    return (t->l == NULL) && (t->r == NULL);
}
void SumTree(Tree* t) {
    if (t == NULL) return;
    if (t->l) SumTree(t->l);
    if (t->r) SumTree(t->r);
    if (t->l == NULL && t->r == NULL)return;
    t->d = (t->l?t->l->d:0)*(isLeaf(t->l)?1:2) + (t->r?t->r->d:0)*(isLeaf(t->r)?1:2);
    return;
}

void PrintTree (Tree *t ) {
    if (t == NULL)return;
    PrintTree(t->l);
    cout << t->d << " ";
    PrintTree(t->r);
}

int main () {
    Tree *r = new Tree(1);;
    r->l = new Tree(2);
    r->l->l = new Tree(2);
    r->r = new Tree(3);
    r->r->l = new Tree(4);
    r->r->r = new Tree(5);
    SumTree(r);
    PrintTree(r);
    cout << endl;
}
