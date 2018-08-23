#include<iostream>
#include<vector>
#include<limits>
using namespace std;
typedef unsigned int uint;

int min_coin(vector<int> &c, int s) {
   vector<int> mat(s+1, 1000);
   mat[0] = 0;
   for (int i = 1; i <= s; i++) {
        for (auto x: c) {
            if ( x <= i) {
                mat[i] = mat[i] > (1 + mat[i - x])?(1 + mat[i - x]):mat[i];
            }
        }
   }
   return mat[s];
}


int main () {
    vector<int> c = {9,5,6,8};
    int s = 11;
    cin >> s;
    cout << min_coin(c, s) << endl;
    return 0;
}
