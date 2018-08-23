#include<iostream>

using namespace std;

class Node {
    public:
        int n;
        Node* next;
        Node(int i) {
            n = i;
            next = NULL;
        };
        Node () {
            n = 0;
            next = NULL;
        }
};

Node* ReversList(Node *n1) {
    if (n1 == NULL) return n1;
    if (n1->next == NULL) return n1;
    Node *rh = NULL;
    while (n1) {
        Node *t = n1->next;
        n1->next = rh;
        rh = n1;
        n1 = t;
    }
    return rh;
}

Node* Add(Node* n1, Node* n2) {
    if (n1 == NULL && n2 == NULL) return NULL;
    Node* rn1 = ReversList(n1);
    Node* rn2 = ReversList(n2);
    int c = 0;
    Node *head = new Node();
    Node *t = head;
    Node *tail = NULL;
    while (rn1 || rn2) {
       int d = (rn1 ? rn1->n:0) +  (rn2 ? rn2->n : 0) + c;
       c = d/10;
       d = d % 10;
       if(rn1) rn1 = rn1->next;
       if(rn2) rn2 = rn2->next;
       t->n = d;
       t->next = new Node();
       tail = t;
       t = t->next;
    }
    if (c) t->n = c;
    else {
        delete t;
        tail->next = NULL;
    }
   
    n1 = ReversList(rn1);
    n2 = ReversList(rn2);
    return ReversList(head);
}

int main() {
    Node *n1 = new Node(9);
    n1->next = new Node(8);
    n1->next->next = new Node(7);
    Node *n2 = new Node(9);
    n2->next = new Node(9);
    int c = 0;
    Node *r = Add(n1, n2);
    if (c) {
        Node *x = new Node();
        x->n = c;
        x->next = r;
        r = x;
    }
    while (r) {
        cout << r->n;
        r = r->next;
    }
    cout << endl;
}
