#include <iostream>
#include <stack>

using namespace std;

class Tree {
public:
    Tree* Right;
    Tree* Left;
    int data;
};

void inorder (Tree *r) {
    stack<Tree*> s;
    s.push(r);
    bool cont;
    while(r) {
        if(r->Left) {
            s.push(r->Left);
            r = r->Left;
        } else {
            cont = false;
            while(!s.empty()) {
                r = s.top();
                s.pop();
                cout << r->data << ",";
                if(r->Right) {
                    s.push(r->Right);
                    r = r->Right;
                    cont = true;
                    break;
                }
            } 
            if(!cont) {
                r = NULL;
            }
        }
    }
}


void treeCost (int *a, int l) {
    stack<Tree*> s;
    int i = l-1;
    while ( i >= 0) {
        if( !a[i]) {
           s.push(NULL);
        } else {
            Tree *t = new Tree();
            t->Left = s.top();
            s.pop();
            t->Right = s.top();
            s.pop();
            t->data = a[i];
            s.push(t);
        }
        i--;
    }
    return s.top();
}

int main() {
    Tree* t = new Tree();

    t->Left = new Tree();
    t->Right = NULL;
    t->data = 1;

    t->Left->Left = new Tree();
    t->Left->Right = NULL;
    t->Left->data = 2;

    t->Left->Left->Left = new Tree();
    t->Left->Left->Right = new Tree();
    t->Left->Left->data = 3;

    t->Left->Left->Left->Left = NULL;
    t->Left->Left->Left->Right = NULL;
    t->Left->Left->Left->data = 4;

    t->Left->Left->Right->Left = NULL;
    t->Left->Left->Right->Right = NULL;
    t->Left->Left->Right->data = 5;

    inorder(t);

}
