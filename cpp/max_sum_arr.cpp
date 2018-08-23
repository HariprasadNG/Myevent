#include <vector>
#include <iostream>
#include <limits>
using namespace std;


int maxSum(vector<int> a) {
    int max = numeric_limits<int>::min();
    int rs = 0;
    for (int i = 0 ; i < a.size(); i++) {
        if (max < rs + a[i]) {
            max = rs + a[i];
        } 
        if ((rs + a[i]) < 0) {
            rs = 0; //This case is for all -ve numbers find the biggest negative numnber.
        } else {
            rs += a[i];
        }
    }
    return max;
}

int main () {
    int s, t;
    vector<int> a;
    cin >> s;
    while (s) {
        cin >> t;
        s--;
        a.push_back(t);
    }
    cout << endl << maxSum(a) << endl;
}
