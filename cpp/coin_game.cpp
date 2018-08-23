#include<iostream>
#include<vector>

using namespace std;

typedef unsigned int uint;
//6 3 1 2 3 4
static vector<int> ac;
static vector<int> bc;
int total;

int max_A_Meme(vector<int> &c) {
    vector<vector<int>> v(c.size(), vector<int>(c.size()));
    for (uint i = 0; i < c.size(); i++) {
        for (uint j = 0; j < c.size(); j++) {
            if (i == j) v[i][j] = c[i];
            if (i > j ) v[i][j] = -1;
        }
    }
    vector<int> sum;
    int t = 0;
    for(int i = 0; i < c.size(); i++) {
        t += c[i];
        sum.push_back(t);
    }
    for (uint i = 1; i < c.size(); i++) {
        for (uint j = 0; j + i < c.size(); j++) {
            int x1 = (sum[j+i] - sum[j] + c[j]) - v[j+1][j+i];
            int x2 = (sum[j+i] - sum[j] + c[j]) - v[j][j+i-1];
            v[j][j+i] = (x1 > x2)?x1:x2;
        }
    }
    return v[0][c.size() -1];
}
int max_A(vector<int> &c, bool a, int s, int e) {
    if (s > e) {
        if(a)  {
            ac.push_back(-1);
        } else {
            bc.push_back(-1);
        }
        return 0;
    }
    if (s == e) {
        if(a)  {
            ac.push_back(s);
        } else {
            bc.push_back(s);
        }
        return c[s];
    }
    //int total = 0;
    //for (int i = s; i<=e; i++) total += c[i]; 
    if (a) {
        total = total - c[s];
        int a1 = total - max_A(c, false, s+1, e);
        int a1b = bc[bc.size() -1];
        bc.pop_back();
        total += c[s];
        a1 += c[s];
        total = total - c[e];
        int a2 = total - max_A(c, false, s, e - 1);
        int a2b = bc[bc.size() -1];
        bc.pop_back();
        total += c[e];
        a2 += c[e];
        if (a1 > a2) {
            ac.push_back(s);
            bc.push_back(a1b);
            return a1;
        } else {
            ac.push_back(e);
            bc.push_back(a2b);
            return a2;
        }
    } else {
        total = total - c[s];
        int b1 = total - max_A(c, true, s+1, e);
        ac.pop_back();
        b1 += c[s];
        total += c[s];
        total = total - c[e];
        int b2 = total - max_A(c, true, s, e - 1);
        ac.pop_back();
        total += c[e];
        b2 += c[e];
        if (b1 > b2) {
            bc.push_back(s);
            return b1;
        } else {
            bc.push_back(e);
            return b2;
        }
    }
}

int main () {
    int tc;
    cin >> tc;
    vector<int> coins;
    total = 0;
    while (tc--) {
        int x;
        cin >> x;
        total += x;
        coins.push_back(x);
    }
    //cout << endl << max_A(coins, true, 0, coins.size() - 1) << endl;
    for(auto x: ac) {
        cout << x << ", ";
    }
    cout << endl;
    for(auto x: bc) {
        cout << x << ", ";
    }
    cout << endl;
    cout << max_A_Meme(coins);
    cout << endl;
}
