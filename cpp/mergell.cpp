#include<stdio.h>
#include<iostream>

using namespace std;

typedef struct _Node {
    int data;
    struct _Node* next;
} Node;

Node* merge (Node* l1, Node* l2) {
    if (l1 == NULL & l2 == NULL) {
        return NULL;
    }
    if (l1 == NULL) {
        return l2;
    }
    if(l2 == NULL) {
        return l1;
    }
    
    Node *head = l1->data < l2->data ? l1:l2;
    Node *tail = head;
    if (head == l1) l1 = l1->next;
    else l2 = l2->next;
    while (l1 && l2) {
        if (l1->data < l2->data) {
            Node *temp = l1->next;
            tail->next =  l1;
            l1 = temp;
        } else {
            Node *temp = l2->next;
            tail->next = l2;
            l2 = temp;
        }
        tail = tail->next;
    }

    if (l1 != NULL) tail->next = l1;
    else tail->next = l2;
    return head;
}

void print(Node* l) {
    while (l) {
        cout << l->data << ", ";
        l = l->next;
    }

    cout << endl;
}

int main () {
    Node *l1 = new Node;
    l1->data = 1;
    l1->next = new Node;
    l1->next->data=10;
    l1->next->next = new Node;
    l1->next->next->data = 11;
    l1->next->next->next = NULL;

    Node *l2 = new Node;
    l2->data = 5;
    l2->next = new Node;
    l2->next->data=6;
    l2->next->next = new Node;
    l2->next->next->data = 17;
    l2->next->next->next = NULL;

    print(merge(l1, l2));
}
