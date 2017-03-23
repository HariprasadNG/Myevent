#include<iostream>
#include<string>

using namespace std;

class Trie {
public:
    bool valid;
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
            if (!x[c]) {
               x[c] = new Trie();
            }
            if (i == (s.size() - 1)) {
                x[c]->valid = true;
            }
            x = x[c]->Next;
        }
        l--;
    }
}

bool WordBreak (string s, Trie* x[256], string p = "") {
    if(s.size() == 0) {
        cout <<"(" << p << ")";
        return true;
    }
    string r;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if(x[c]) {
            if(!x[c]->valid) {
                x = x[c]->Next;
                continue;
            }
            r += s.substr(0, i+1);
            string temp = p + ((p.size()>0)?" ":"") + r;
            WordBreak(s.substr(i+1), t, temp);
            r.clear();
            x = x[c]->Next;
        } else {
            return false;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while(T) {
        ConstructTrie();
        string test;
        cin >> test;
        WordBreak(test, t);
        cout << endl;
        T--;
    }
}
