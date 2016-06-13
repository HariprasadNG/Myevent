#include<iostream>
#include<map>
#include<string>
#include<stdlib.h>

using namespace std;

class Trie {
public:
    char val;
    bool fixed;
    Trie* pos[2];
    Trie(){
        val = '\0';
        fixed = false;
        pos[0] = nullptr;
        pos[1] = nullptr;
    }
};

Trie* ConstructTrie(map<char,string> ip) {
    Trie *t = new Trie();
    for (auto x: ip){
        Trie *c = t;
        for (auto y:x.second) {
            if(c->pos[y -'0']==nullptr) {
                c->pos[y -'0'] = new Trie();
            }
            c = c->pos[y - '0'];
            if(c->fixed && c->val != x.first) {
                cout << "No unique decoding possible" << endl;
                exit(-1);
            }
        }
        c->fixed = true;
        c->val = x.first;
    }

    return t;
}

char decode(char* &s, Trie* t) {
    while(*s && t) {
        if(t->fixed) return t->val;
        t = t->pos[*s - '0'];
        s++;
    }
    if(t && t->fixed) return t->val;
    cout << "Not a valid sequence" << endl;
    exit(-2);
}

int main () {
    map<char, string> ip;
    ip['a'] = "01";
    ip['d'] = "001";
    ip['e'] = "100";
    ip['f'] = "101";
    ip['b'] = "111";
    ip['c'] = "000";
    ip['h'] = "110";

    Trie* t = ConstructTrie(ip);
    char *s = "011110100001001100101110111101001";
    while(*s) {
        cout << decode(s,t);
    }
    cout << endl;
}
