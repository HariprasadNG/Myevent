#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;

void print_path(vector<vector<int>> &m, vector<vector<int>> &r) {
   int ci = 0, cj = 0;
   while (ci != (m.size()-1) && cj != (m[0].size()-1)) {
       if (r[ci][cj] - m[ci][cj] == r[ci+1][cj]) {
           cout << "D{" << m[ci][cj] << "} ";
           ci++;
       } else {
           cout << "R{" << m[ci][cj] << "} ";
           cj++;
       }
   }
   int x = ci;
   while (ci < (m.size() - 1)) {
       cout << "D{" << m[x++][cj] << "} ";
       ci--;
   }
   x = cj;
   while (cj < (m[0].size() - 1)) {
       cout << "R{" << m[ci][x++] <<"} ";
       cj--;
   }
   cout << "{" << m[m.size() -1][m[0].size() -1] << "}";
   cout << endl;
}

int max_sum(vector<vector<int>> &m) {
    vector<vector<int>> r(m.size(), vector<int>(m.size(), 0));
    r[m.size() - 1][m[0].size() - 1] = m[m.size() - 1][m[0].size() - 1];

    for (int i = r.size() - 1; i >= 0; i--) {
        for (int j = r[i].size() - 1; j >= 0; j--) {
            int d = 0;
            int l = 0;
            if ((i + 1) < r.size()) {
                d = r[i+1][j];
            }
            if ((j + 1) < r[0].size()) {
                 l = r[i][j+1];
            }
            if (d > l) {
                r[i][j] = d + m[i][j];
            } else {
                r[i][j] = l + m[i][j];
            }
        }
    }
    print_path(m ,r);
    return r[0][0];
}


int main () {
    vector<vector<int>> m = {
                                {1, 10, 3, 8},
                                {12, 2, 9, 6},
                                {5, 7, 4, 11},
                                {3, 7, 16, 5}
                            };

    cout << max_sum(m) << endl;
    return 0;
}
