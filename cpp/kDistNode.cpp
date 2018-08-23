#include<iostream>
using namespace std;

class Tree {
    public:
        int n;
        Tree* left;
        Tree* right;
        Tree():n(0),left(NULL),right(NULL) {
        }
        Tree(int x):n(x), left(NULL), right(NULL) {
        }
};

void printKdistDown(Tree *r, int k) {
    if (r == NULL) return;
    if (k == 0) cout << r->n << " ";
    printKdistDown(r->left, k-1);
    printKdistDown(r->right, k-1);
}

int printKdist(Tree *r, Tree *t, int k) {
    if ( r == NULL) return -1;
    if (r == t) {
        printKdistDown(r, k);
        return 0;
    }
    int dl = printKdist(r->left, t, k);
    if (dl != -1) {
        //First time will be hit after printKdistDown call above
        if (dl + 1 == k) cout << r->n << " ";
        else printKdistDown(r->right, k - dl - 2);
        return dl + 1;
    }

    int dr = printKdist(r->right, t, k);
    if (dr != -1) {
       if (dr + 1 == k) cout << r->n << " ";
       else printKdistDown(r->left, k - dr - 2);
       return dr + 1;
    }
    return -1;
}

int main () {
    Tree* t = new Tree(4);
    t->left = new Tree(2);
    t->left->right = new Tree(1);
    t->left->right->right = new Tree(1);
    t->left->right->left = new Tree(0);
    t->right = new Tree(6);
    t->right->left = new Tree(5);
    t->right->right = new Tree(8);
    printKdist(t, t->left->right, 2);
}
