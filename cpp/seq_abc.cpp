#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>
using namespace std;

class Node {
public:
    vector<Node*> next;
    char c;
    Node(char ch) {
        c = ch;
        next.empty();
    }
};

vector<Node*> allAs;
vector<Node*> allBs;
vector<Node*> allCs;

void makeGraph(string s) {
    for (auto c:s) {
        if (c != 'a' && allAs.empty())continue;
        if (c == 'a') {
            Node* na = new Node(c);
            for (auto A:allAs) {
                A->next.push_back(na);
            }
            allAs.push_back(na);
        } else if (c == 'b') {
            Node* nb = new Node(c);
            for (auto A:allAs) {
                A->next.push_back(nb);
            }
            for (auto B:allBs) {
                B->next.push_back(nb);
            }
            allBs.push_back(nb);
        } else if (c == 'c') {
            Node* nc = new Node(c);
            for (auto B:allBs) {
                B->next.push_back(nc);
            }
            for (auto C:allCs) {
                C->next.push_back(nc);
            }
            allCs.push_back(nc);
        }
    }
}

void ClearGraph () {
    for (auto X: allAs) {
        delete X;
    }
    allAs.clear();
    for (auto X: allBs) {
        delete X;
    }
    allBs.clear();
    for (auto X: allCs) {
        delete X;
    }
    allCs.clear();
}

int countPaths(string s) {
    ClearGraph();
    makeGraph(s);
    string v;
    if (allAs.empty()) return 0;
    int count = 0;
    stack<pair<Node*, int> > st;
    for (int ii = 0; ii < allAs.size(); ii++) {
        st.push({allAs[ii], 0});
        string res;
        while (!st.empty()) {
            Node *n = st.top().first;
            int i = st.top().second;
            if(i == 0)res += n->c;
            if (i == n->next.size()) {
                if ( n->c == 'c') {
                    count++;
                    //cout << res << endl;
                }
                st.pop();
                res = res.substr(0, st.size());
                continue;
            }
            st.pop();
            st.push({n, i+1});
            st.push({n->next[i], 0});
        }
    }
    return count;
}


typedef unsigned long long ull;
typedef long long int lli;
ull nChoosek( ull n, ull k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    lli result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

ull possiblities(int n) {
    ull temp = 0;
    for(int i = 1; i <= n; i++) {
        temp += nChoosek(n, i);
    }
    return temp;
}

int count (char c, string s) {
    int count = 0;
    for(auto x: s) {
        if (x > c) {
           return count;
        } else if ( x == c) {
            count++;
        }
    }
    return count;
}

ull count_paths (string s) {
    int as = count('a', s);
    int bs = count('b', s);
    int cs = count('c', s);
    
    if (as == 0 ||
        bs == 0 ||
        cs == 0) return 0;

    return possiblities(as)*possiblities(bs)*possiblities(cs);
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        string s;
        cin >> s;
        cout << countPaths(s) << endl;
    }
}
