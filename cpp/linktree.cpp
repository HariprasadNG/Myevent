#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    Node* Left, Right, Next;
}

int main () {
    queue<Node*> q;
    Node* T;
    q.push(T);
    while(!q.empty()) {
        Node *c  = q.front();
        int curlevel = q.size() - 1;
        q.pop();
        if (c->Left) q.push(c->Left);
        if (c->Right) q.push(c->Right);
        while(curlevel) {
            c->Next = q.front();
            c = q.front();
            if (c->Left) q.push(c->Left);
            if (c->Right) q.push(c->Right);
            q.pop();
            curlevel--;
        }
        c->Next = NULL;
    }
}
