#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;
vector<vector<int>> mem(10, vector<int>(1000, -1));
int rec_coinChange (vector<int> &c, int n, uint s) {
    if (s >= c.size()) return 0;
    if (n == 0)return 1;
    if (mem[s][n] != -1) return mem[s][n];
    int count = 0;
    int x = c[s];
    int j = 0;
    while (x*j <= n) {
        count += rec_coinChange(c, n - x*j, s+1);
        j++;
    }
    mem[s][n] = count;
    return count;
}

int dp_coinChange(vector<int> &c, int n) {
    vector<vector<int>> r(n+1, vector<int>(c.size(), 0));
    //Sum 0 can be achived in a unique way
    for (uint i= 0; i < c.size(); i++) {
        r[0][i] = 1;
    }

    //Find out how 1 to n can be achived by using only last coin
    for (int i = 1; i <= n; i++) {
        r[i][c.size()-1] = (i%c[c.size() -1] == 0) ? 1:0;
    }

    //Find out how 1 to n can be achived from  using
    //last 2 coins (using the result of last 1 coin)
    //last 3 coins (using the result of last 2 coins)
    //last 4 coins (using the result of last 3 coins)
    //last n coins (using the result of last n-1 coins)
    for (int i = 1; i <= n; i++) {
        for (int x = c.size() - 2; x >= 0; x--) {
            int count = 0;
            int tx = c[x];
            int j = 0;
            while ((tx * j) <= i) {
               int b = i - (tx *j);
               count += r[b][x+1];
               j++;
            }
            r[i][x] = count;
        }

    }
    return r[n][0];
}

//2 + 2 + 2 + 2 + 2
//5 + 5
//5 + 3 + 2
//3 + 3 + 2 + 2
//6 + 2 + 2
int main () {
    vector<int> c = {2,5,3,6};
    vector<int> c2 = {3,5,10};
    int num = 10;
    cin >> num;
    //cout << change_pos(c, num) << endl;
    //cout << rec_coinChange(c, num, 0) <<  endl;
    cout << dp_coinChange(c2, num);
    return 0;
}
