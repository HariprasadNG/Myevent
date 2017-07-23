#include <iostream>
#include <vector>
using namespace std;

void printSol (int n, int s, vector<int> &v) {
    if ( n == 0) {
        for (auto x : v) {
            cout << x;
        }
        cout << " ";
        return;
    }
    if ((9-s)+1  >= n) {
        for (int i = s+1; i <= 9; i++) {
            v.push_back(i);
            printSol(n-1, i, v);
            v.pop_back();
        }
    }
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> v;
        int i = 1;
        cout << i << "::" << n << endl;
        printSol(n, 0, v);
        cout << endl;
    }
}
