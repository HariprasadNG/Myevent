#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>
#include<queue>

using namespace std;
typedef unsigned int uint;

class Tree {
    public:
        int d;
        Tree* l;
        Tree* r;
        Tree():d(0),l(NULL), r(NULL) {};
        Tree(int x):d(x),l(NULL), r(NULL) {};
};

Tree* constructTree(vector<int> a) {    
    if (a.size() == 0) return NULL;
    Tree *t = new Tree(a[0]);
    queue<Tree*> q;
    q.push(t);
    for (int i = 1; i < a.size();) {
        Tree *l = new Tree(a[i++]);
        Tree *r = NULL;
        if ( i < a.size()) {
            r = new Tree(a[i++]);
        }
        Tree *root = q.front();
        q.pop();
        root->l = l;
        root->r = r;
        q.push(l);
        q.push(r);
    }
    return t;
}

int main () {
    vector<int> a = {1,2,3,4,5,6,7};
    Tree* t = constructTree(a);

}
