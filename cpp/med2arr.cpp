#include <iostream>
#include <vector>

using namespace std;

int search(vector<int> a, int x, int s, int e) {
    int m = (s + e)/2;
    if (s > e && e >= 0) return e;
    if (e <= -1) return -1;
    while (s < e) {
        if (a[m] == x) {
            return m;
        } else if (a[m] > x) {
            e = m - 1;
            m = (s + e)/2;
        } else {
            s = m + 1;
            m = (s + e)/2;
        }
    }
    if (a[s] > x) return s - 1;
    return s;
}
int med(vector<int> a, vector<int> b) {
    int as = 0;
    int ae = a.size() - 1;
    int bs = 0;
    int be = b.size() - 1;
    int ma = (as + ae)/2;
    int x = search(b, a[ma], 0, b.size() - 1);
    while (true) {
        if ( (x + 1 + ma + 1) == (a.size() + b.size())/2) {
            return a[ma];
        }
        if ( (x + 1 + ma + 1) == (a.size() + b.size())/2 + 1) {
            return max(a[ma-1], b[x]);
        }
        if ( (x + 1 + ma + 1) == (a.size() + b.size())/2 - 1) {
            return min(a[ma + 1], b[x + 1]);
        }
        if ( (x + 1 + ma + 1) > (a.size() + b.size())/2) {
            ae = ma - 1;;
            bs = x + 1;
        }
        if ( (x + 1 + ma + 1) < (a.size() + b.size())/2) {
            as = ma + 1;
            be = x - 1;
        }
        ma = (as + ae)/2;
        x = search(b, a[ma], bs, be);
    }
    
}
int main () {
    vector<int> a = {1,2,3,4,5};
    vector<int> b = {6,7,8,9,10};
    cout << med (a, b) << endl;
    cout << med (b, a) << endl;
    vector<int> aa = {2,4,6,8,10};
    vector<int> bb = {1,3,5,7,9};
    cout << med(aa, bb) << endl;
    cout << med(bb, aa) << endl;
    vector<int> aaa = {1, 2, 3, 9, 10};
    vector<int> bbb = {4, 5, 6, 7, 8};
    cout << med(aaa, bbb) << endl;
    cout << med(bbb, aaa) << endl;
}
