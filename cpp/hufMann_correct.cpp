#include <iostream>
#include <vector>
#include <functional>
#include <queue>
using namespace std;
typedef unsigned int uint;

class tree {
    public:
        uint f;
        char c;
        tree* left;
        tree* right;
        tree():f(0),c(0),left(0),right(0){};
};
auto cmp = [](tree* l, tree* r)->bool {return l->f > r->f;};
using hufmanQ = priority_queue<tree*, vector<tree*>,  decltype(cmp)>;

void ht (hufmanQ &pq)  {
    if(pq.size() <= 1)return;
    tree *l = pq.top();
    pq.pop();
    tree *r = pq.top();
    pq.pop();
    tree *p = new tree();
    p->f = l->f + r->f;
    p->left = l;
    p->right = r;
    pq.push(p);
    ht(pq);
}

void print(tree* r, string &s) {
    if (r == NULL)return;
    if (r->left == NULL && r->right == NULL) {
        cout << s << " ";
    } 
    if (r->left) {
        s.push_back('0');
        print(r->left,s);
        s.pop_back();
    }
    if (r->right) {
        s.push_back('1');
        print(r->right, s);
        s.pop_back();
    }
    delete r;
    return;

}

int main () {
    int T;
    cin >> T;
    while(T--) {
        string val;
        cin >> val;
        hufmanQ pq(cmp);
        for (uint i = 0; i < val.size(); i++) {
            tree *t = new tree();
            cin >> t->f;
            t->c = val[i];
            pq.push(t);
        }
        ht(pq);
        string s = "";
        print(pq.top(),s);
        cout << endl;
    }
}
