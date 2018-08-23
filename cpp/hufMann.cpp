#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iterator>
#include <functional>
using namespace std;
typedef unsigned int uint;
class tree {
public:
    uint sum;
    multimap<uint, char, less<uint> >::iterator start;
    tree *left;
    tree *right;
    tree(uint su, multimap<uint, char, less<uint> >::iterator st):sum(su), 
                           start(st),
                           left(NULL), 
                           right(NULL)
    {
    }
};

void hufT(multimap<uint, char, less<uint>> ip, tree* s) {
    if (s->start == ip.end() || s->start->first == s->sum) return;
    
    auto lst = s->start;
    uint lsum = lst->first;
    lst++;
    while ((lsum + lst->first) < ((s->sum >> 1) + (s->sum % 2))) {
        cout << "Taking more..." << endl;
         lsum += lst->first;
         lst++;
    }
    tree *left = new tree((lsum), s->start);
    tree *right = new tree((s->sum - lsum ), lst);
    hufT(ip, left);
    s->left = left; 
    hufT(ip, right);
    s->right = right;
}

map<char, string> g_set;
void getCode (tree *r, string& s) {
    if (r->left == NULL && r->right == NULL) {
        g_set.emplace(make_pair(r->start->second, s));
        return;
    }
    if (r->left) {
        s.push_back('0');
        getCode (r->left,s);
        s.pop_back();
    }
    if (r->right) {
        s.push_back('1');
        getCode (r->right,s);
        s.pop_back();
    }
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        multimap<uint,char, less<uint> > fq;
        g_set.clear();
        string cd;
        cin >> cd;
        uint sum = 0;
        for (int i = 0; i<cd.size() ;i++) {
            int temp;
            cin >> temp;
            fq.emplace(make_pair(temp, cd[i]));
            sum += temp;
        }
        tree *r = new tree(sum, fq.begin());
        hufT(fq, r);
        string s = "";
        getCode(r, s);
        for (auto x:g_set) {
            cout << x.first << ":" << x.second << endl;
        }
    }
}

