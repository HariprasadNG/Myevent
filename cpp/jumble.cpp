#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;

vector<string> il = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

class Trie {
    public:
        Trie* c[256];
        int valid;
        Trie() {
            valid = -1;
            for (int i = 0; i < 256; i++) c[i] = NULL;
        }
};

Trie* g_root = new Trie();
void AddWord(string s, int x) {
    Trie *cl = g_root;
    for (auto c:s) {
        if (cl->c[c] == NULL) {
            cl->c[c] = new Trie();
        }
        cl = cl->c[c];
    }
    cl->valid = x;
}
void RemoveWord(string s) {
    Trie *cl = g_root;
    for (auto c:s) {
        if (cl->c[c]) {
            cl = cl->c[c];
        } else {
            return;
        }
    }
    cl->valid = -1;
}

class ip {
    public:
        char c;
        int count;
        ip (char _c, int _count) {
            c = _c;
            count = _count;
        }
        ip() {
            c = 0;
            count = 0;
        }
};

bool Done (vector<ip> &i) {
    bool b_result = true;
    for (auto x: i) {
        if (x.count > 0) {
            b_result = false;
            for (int j = 0 ; j < x.count; j++) {
                cout << x.c;
            }
        }
    }
    cout << endl;
    return b_result;;
}

void addAllToTrie() {
   for (int i = 0; i < 10; i++) {
       AddWord(il[i], i);
   }
}
vector<int> result;
int compute (vector<ip> &input, Trie *root) {
    if (root->valid != -1) {
        result.push_back(root->valid);
        return root->valid;
    }
retry:
    for (int i = 0; i < input.size();) {
        if (input[i].count > 0 && root->c[input[i].c]) {
            input[i].count--;
            char xx = input[i].c;
            int x = compute(input, root->c[input[i].c]);
            if ( x != -1 && root != g_root) {
                return x;
            }
            if (x == -1) input[i].count++;
            if (x == -1 || input[i].count == 0)i++;
        } else {
            i++;
        }
    }
    if (g_root == root && !Done(input)) {
        if (result.size() == 0) return -1;
        int x = result[result.size() - 1];
        result.pop_back();
        cout << x << "Not possible" << endl;
        for (auto temp:result) {
            cout << temp << " ";
        }
        cout << endl;
        addAllToTrie();
        RemoveWord(il[x]);
        for (auto c: il[x]){
            input[c].count++;
        }
        goto retry;
    }
    return root->valid;
}

vector<string> compute2(vector<ip> &i) {
    vector<string> s;
    while (!Done(i)) {
        for (auto x: il) {
            bool found = true;
            for (auto c : x) {
                if (i[c].count == 0) {
                    found = false;
                    break;
                }
            }
            if (found) {
                for (auto c: x) {
                    i[c].count--;
                }
                s.push_back(x);
                vector<string> recomp = compute2(i);
                if (!Done(i)) {
                    for (auto c: x) {
                        i[c].count++;
                    }
                   for (auto st : recomp) {
                    for (auto c: st) {
                        i[c].count++;
                    }
                   }

                } else {
                    for (auto st: recomp) {
                        s.push_back(st);
                    }
                    return s;
                }
                
            }
        }
    }
    return s;
}

vector<ip> convert (string s) {
    vector<ip> x(256);
    for (auto t: s) {
        x[t].count++;
        x[t].c = t;
    }
    return x;
}
void printI(vector<ip> &i) {
   for (auto y:result) {
       cout << y << " ";
   }
    cout << endl;
    for (auto x:i) {
        if(x.count > 0)cout << x.c << ":(" << x.count << ")";
    }
    cout << endl;
}

int main () {
   addAllToTrie();
   string s = "zeroonetwothreefourfivesixeightnineoneone";
   vector<ip> i = convert(s);
   compute(i, g_root);
   for (auto x: result) {
       cout << x << " ";
   }
   return 0;
}
