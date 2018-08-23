#include<iostream>

class Node {
    public:
        bool v;
        Node* l;
        Node* r;
};


void UpdateTopUp(Node *root, Node *x, bool &update = false) {
    if  (root == NULL) return;
    if ( x == root && 
         x->l == NULL && 
         x->r == NULL) {
        x->v = !x->v;
        update = true;
        return;
    };

    UpdateTopUp(root->l, x, update);

    if (update) {
        if (x->v != x->l->v && x->r->v) {
            x->v = x->l->v && x->r->v;
            update = true;
        } else {
            update = false;
        }
        return ;
    }

    UpdateTopUp(root->r, x, update); 
    
    if (update) {
        if (x->v != x->l->v && x->r->v) {
            x->v = x->l->v && x->r->v;
            update = true;
        } else {
            update = false;
        }
        return;
    }

}

void main () {
    Node *root = new Node();
    root->v = 1;
}
