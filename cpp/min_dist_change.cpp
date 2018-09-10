#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>
#include<memory>
#include<queue>
#include<map>
#include<set>
using namespace std;
typedef unsigned int uint;

#define MAX_WAIT 100000

//Helper function to check if there is a link or not
int checkLink(string n1, string n2) {
    if (n1.length() != n2.length())return false;
    int diff = 0;
    for (int i = 0; i < n2.length(); i++) {
        if (n1[i] != n2[i]) diff++;
        if (diff > 1) return false;
    }
    return diff;
}

//Custom Graph based Dijikstra Implimentation
class Node {
    public:
        vector<shared_ptr<Node>> adj;
        int v;
        int w;
        string s;
        Node(string x):s(x){
            v = 0;
            w = MAX_WAIT;
        }
};

vector<vector<shared_ptr<Node>>> AllG(100, vector<shared_ptr<Node>>());

void addNode(string node) {
    shared_ptr<Node> n(new Node(node));
    for (auto x: AllG[node.length()]) {
        if (checkLink(x->s, node)) {
            x->adj.push_back(n);
            n->adj.push_back(x);
        }
    }
    AllG[node.length()].push_back(n);
}

int DijShortesPath(shared_ptr<Node> s, shared_ptr<Node> e) {
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, function<bool(shared_ptr<Node>, shared_ptr<Node>)>> pq([](shared_ptr<Node> n1, shared_ptr<Node> n2)->bool {
        return n1->w < n2->w;
    });
    s->w = 0;
    pq.push(s);
    while (pq.size() > 0) {
        auto t = pq.top();
        pq.pop();
        for (auto x: t->adj) {
            if (t->w + 1 < x->w) {
                x->w = t->w + 1;
                pq.push(x);
            }
        }
    }
    return e->w;
}

int minDis(string x, string y) {
    if (x.length() != y.length()) return -1;
    auto s = find_if( AllG[x.length()].begin(), AllG[x.length()].end(), [x](shared_ptr<Node> w)->bool {
                if (x == w->s) return true;
                return false;
            });
    auto e = find_if( AllG[x.length()].begin(), AllG[x.length()].end(), [y](shared_ptr<Node> w)->bool {
                if (y == w->s) return true;
                return false;
            });
    if ( s != AllG[x.length()].end() && e != AllG[x.length()].end()) {
        return DijShortesPath(*s, *e);
    }
    return -1;
}

//Flowyd marshall based Mapbased graph implimentation
vector<map<string, map<string, int>>> AG(100);
void addNode2(string node) {
    int l = node.length();
    AG[l].emplace(node, map<string, int>());
    for (auto x: AG[l]) {
        if (checkLink(x.first, node)) {
            AG[l][x.first].emplace(node, 1);
            AG[l][node].emplace(x.first, 1);
        }
    }
}

int findWt (int l, string s, string e) {
   if (AG[l].find(s) == AG[l].end()) {
       return -1;
   } 
   if (AG[l][s].find(e) == AG[l][s].end()) {
       return -1;
   }
   return AG[l][s][e];
}

void FW(int l) {
    for (auto in:AG[l]) {
        for (auto i:AG[l]) {
            for (auto j:AG[l]) {
                if (i.first != j.first && i.first != in.first && j.first != in.first) {
                    int w1 = findWt(l, i.first, in.first);
                    int w2 = findWt(l, in.first, j.first);
                    int tw = findWt(l, i.first, j.first);
                    if (w1 == -1 || w2 == -1) {
                    } else if (tw == -1 || w1 + w2 < tw) {
                        if (tw == -1) {
                            AG[l][i.first].emplace(j.first, w1 + w2);
                        } else {
                            AG[l][i.first][j.first] = w1 + w2;
                        }
                    }
                }
            }
        }
    }
}

int minDis2(string s1, string s2) {
    if (s1.length() != s2.length())return MAX_WAIT;
    return AG[s1.length()][s1][s2];
}

//Dictonary based implimentation......
class Dict {
    public:
        bool vw;
        vector<shared_ptr<Dict>> c;
        Dict():vw(false),c(26, shared_ptr<Dict>(NULL)){};
};

shared_ptr<Dict> root(new Dict());

void addNode3(string x) {
    auto lr = root;
    for (int i = 0; i < x.length()-1; i++) {
        auto c = x[i];
        if (lr->c[c - 'a'] == NULL) {
            shared_ptr<Dict> t(new Dict());
            lr->c[c - 'a'] = t;
        }
        lr = lr->c[c - 'a'];
    }
    if (lr->c[x[x.length() - 1] - 'a'] == NULL) {
        shared_ptr<Dict> t(new Dict());
        lr->c[x[x.length() - 1] - 'a'] = t;
    }
    lr->c[x[x.length() - 1] - 'a']->vw = true;
}

bool validWord (string x) {
    auto lr = root;
    for (int i = 0; i < x.length()-1; i++) {
        auto c = x[i];
        if (lr->c[c - 'a'] == NULL) {
            return false;
        }
        lr = lr->c[c - 'a'];
    } 
    return (lr->c[x[x.length() - 1] - 'a'] != NULL && lr->c[x[x.length() - 1] - 'a']->vw);
}

//This is a DFS not a shortest path just finds if conversion possbile or not
int minDis3(string s, string e, set<string> &v) {
    if (s.length() != e.length())return MAX_WAIT;
    if (!validWord(s) || !validWord(e)) return MAX_WAIT;
    if (s == e) return 0;
    for (int i = 0; i <  s.length(); i++) {
        char sc = s[i];
        for (char c = 'a'; c <= 'z'; c++) {
            s[i] = c;
            if(v.find(s) == v.end()) {
                v.emplace(s);
                int weight = 1 + minDis3(s, e, v);
                if  (weight < MAX_WAIT) {
                    return 1 + weight;
                }
            }
        }
        s[i] = sc;
    }
    return MAX_WAIT;
}

int main () {
    addNode("man");
    addNode("pan");
    addNode("can");
    addNode("cat");
    addNode("pat");
    addNode("pet");
    addNode("met");
    //man->can->cat->pat->pet->met one conversion
    //man->pan->pat->pet->met //Optimimun in 4 steps.
    cout << minDis("man", "met") << endl;

    addNode2("man");
    addNode2("pan");
    addNode2("can");
    addNode2("cat");
    addNode2("pat");
    addNode2("pet");
    addNode2("met");
    FW(3);
    cout << minDis2("man", "met") << endl;
    cout << minDis2("man", "pet") << endl;
    cout << minDis2("met", "can") << endl;
    cout << minDis2("man", "can") << endl;

    addNode3("man");
    addNode3("can");
    addNode3("cat");
    addNode3("pet");
    set<string> v;
    v.emplace("man");
    cout << "mindDis3??" << minDis3("man", "cat", v) << endl;
    v.clear();
    v.emplace("man");
    cout << "mindDis3??" << minDis3("man", "pet", v) << endl;
}
