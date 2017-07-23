#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Trie {
public:
    vector<string> matches;
    Trie* Next[256];
};

Trie* t[256];

void FreeTrie(Trie* x[256]) {
    for (int i = 0; i < 256; i++){
        if(x[i]) {
            FreeTrie(x[i]->Next);
            delete x[i];
            x[i] = NULL;
        }
    }
}

void ConstructTrie() {
    FreeTrie(t);
    int l;
    cin >> l;
    while(l) {
        string s;
        cin >> s;
        Trie **x = t;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c >= 'A' && c <= 'Z') {
                if (!x[c]) {
                   x[c] = new Trie();
                }
                x[c]->matches.push_back(s);
                x = x[c]->Next; 
            }
        }
        l--;
    }
}

vector<string> search (string s) {
    Trie **x  = t;
    Trie *r = NULL;
    for (int i = 0; i < s.size(); i++) {
        r = x[s[i]];
        if (r) {
            x = r->Next;
        } else {
            break;
        }
    }
    if (r) return r->matches;
    else return vector<string>();
}

int main() {
    int T;
    cin >> T;
    while(T) {
        ConstructTrie();
        string test;
        cin >> test;
        vector<string> r = search(test);
        if ( r.size() == 0) {
            cout <<  "No match found";
        } else {
            for (auto x:r) {
                cout << x << " ";
            }
        }
        cout << endl;
        T--;
    }
}
