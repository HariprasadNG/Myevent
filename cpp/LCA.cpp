#include <iostream>

using namespace std;

class Tree {
    public:
        Tree *l, *r;
        int d;
        Tree():l(NULL), r(NULL), d(-1){

        }
};


Tree* LCA(Tree *r, int a, int b) {
    if (r == NULL)return NULL;
    if (a == -1 && b == -1) return NULL;
    
    if (r->d == a) {
        return r;
    } else if ( r->d == b) {
        return r;
    }
    Tree *x = LCA(r->l, a, b);
    Tree *y = LCA(r->r, a, b);
    if (x && y) return r; //One node is found on left the other one on right so r is LCA.
    if (x || y) {
        //Only one node is found so the other should be below that so that is the LCA
        return x?x:y ;
    }
    //Both the nodes are not present in eithe left or right hence NULL
    return NULL;
}



int main () {
    Tree *t = new Tree();
    t->l = new Tree();
    t->r = new Tree();
    t->d = 0;

    t->l->l = new Tree();
    t->l->r = new Tree();
    t->l->d = 1;

    t->r->l = new Tree();
    t->r->r = new Tree();
    t->r->d = 2;

    t->l->l->d = 3;
    t->l->r->d = 4;

    t->r->l->d = 5;
    t->r->r->d = 6;

    t->l->r->l = new Tree();
    t->l->r->l->d = 7;

    //Assumption both the nodes are present
    //if one node may not be present make search for the other node
    //from current Node if found current node is LCA
    //else NULL;
    //
    //x = LCA(t, 7, 10);
    //if (x && x->d == 7) return Search(x, 10)
    //if (x && x->d == 10) return Search(x, 7)
    //return x;
    //
    
/*
 *            / ---0--- \
 *        /1\           /2\
 *     3/     \4     5/    \6
 *           7/
 * */

    cout << LCA(t, 7, 6)->d << endl; //0
    cout << LCA(t, 3, 7)->d << endl; //1
    cout << LCA(t, 1, 7)->d << endl; //1
    cout << LCA(t, 7, 4)->d << endl; //4
    cout << LCA(t, 7, 7)->d << endl; //7

}
