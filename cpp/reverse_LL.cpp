#include<iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node() {
        data = -1;
        next = nullptr;
    }
};

Node* Reverse(Node *l) {
    Node *p = nullptr;
    while(l) {
        Node* t = l->next;
        l->next = p;
        p = l;
        l = t;
    }
    return p;
}

void printLL(Node *h) {
    while(h) {
        cout << h->data << "->";
        h = h->next;
    }
    cout << endl;
}

Node* ReverseKnode(Node *l, int k) {
    Node *head = nullptr;
    Node *ptail = nullptr;
    while(l) {
        int tk = k;
        Node *tail = l;
        Node *p = nullptr;
        while(l && tk) {
            Node *tn = l->next;
            l->next = p;
            p = l;
            l = tn;
            tk--;
        }
        if(!head) head = p;
        if(ptail) ptail->next = p;
        ptail = tail;
    }

    return head;
}

int main() {
    Node *head = new Node();
    Node *temp = head;
    int i = 0;
    while( i < 10) {
        temp->data = i;
        i++;
        temp->next = new Node();
        temp = temp->next;
    }

    printLL(head);

    Node* kr = ReverseKnode(head, 4);
    printLL(kr);
}
