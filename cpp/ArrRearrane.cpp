#include<iostream>
#include<vector>
using namespace std;

void Solve(int n) {
    vector<int> ip;
    for (int i =0; i < n; i++) {
        int x;
        cin >> x;
        ip.push_back(x);
    }

    for(int i = 0; i < n; i++) {
        cout << ip[ip[i]] << " ";
    }

    cout << endl;
}

int main () {
    int t;
    cin >> t;
    for (int i = 0 ; i < t; i++) {
        int x;
        cin >> x;
        Solve(x);
    }
}
