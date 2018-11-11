#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;

class Trie {
    public:
        map<char, Trie*> next;
        bool Valid;
        string word;

    Trie ():Valid(false) {
        
    }
    ~Trie() {
        for (auto x : next) {
            if (x.second) {
                delete x.second;
            }
        }
        next.clear();
    }

};

class Dictonary {
    private:
        Trie *root;
    public:
        void addWord(string s) {
            Trie *cl = root;
            for (auto c: s) {
                auto it  = cl->next.find(c);
                if (it == cl->next.end()) {
                    cl->next.emplace(pair<char, Trie*>(c, new Trie()));
                    it = cl->next.find(c);
                }
                cl = it->second;
            }
            cl->word = s;
            cl->Valid = true;
        }
        bool validWord(string s) {
            Trie *cl = root;
            for (auto c: s) {
                auto it = cl->next.find(c);
                if (it == cl->next.end()) {
                    return false;
                }
                cl = it->second;
            }
            return cl->Valid;
        }

        Trie* getTrie () {
            return root;
        }

        Dictonary() {
            root = new Trie();;
        }
        ~Dictonary() {
            if (root) {
                delete root;
                root = NULL;
            }
        }
};

class CharMap {
    public:
        char c;
        int count;
        CharMap():c(0), count(0) {
            
        }
};

vector<CharMap> stringToCharMap(string ip) {
    vector<CharMap> cmp(255);
    for (auto c:ip) {
        cmp[c].c = c;
        cmp[c].count++;
    }
    return cmp;
};

bool Done (vector<CharMap> &ip) {


    for (auto x: ip) {
        if (x.count) return false;
    }
    return true;
}

bool construct (vector<CharMap> &ip, Dictonary &d, Trie* cl, vector<string> &res) {
    if (Done(ip)) return true;
    for (char c = 'a'; c <= 'z'; c++) {
        if (ip[c].count <= 0) {
            continue;
        }
        auto it = cl->next.find(c);
        if (it != cl->next.end()) {
            ip[c].count--;
            if (it->second->Valid) {
                res.push_back(it->second->word);
                if (construct(ip, d, d.getTrie(), res)) {
                    return true;
                } else {
                    ip[c].count++;
                    res.pop_back();
                }
            } else {
                if( construct(ip, d, it->second, res) ) {
                    return true;
                } else {
                    ip[c].count++;
                }
            }
        }
    }
    
    return false;
}

int main () {
    Dictonary x;
    x.addWord("one");
    x.addWord("two");
    x.addWord("three");
    x.addWord("four");
    x.addWord("five");
    x.addWord("six");
    x.addWord("seven");
    x.addWord("eight");
    x.addWord("nine");
    x.addWord("zero");
    string ip = "onetwothreefourfivesixseveneightninezero";
    cin >> ip;
    vector<CharMap> cm = stringToCharMap(ip);
    vector<string> result;
    construct(cm, x, x.getTrie(), result);
    for (auto r: result) {
        cout << r << endl;
    }
    return 1;
}