#include <iostream>
#include <vector>
using namespace std;

int diffbits (int a, int b) {
    int x = a ^ b;
    int i = 1;
    int count = 0;
    for (int j = 0; j < 4; j++) {
        if (x&i)count ++;
        i = i << 1;
    }
    return count;
}

int solve (vector<int> &v) {
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i+1; j < v.size(); j++) {
            count += diffbits(v[i], v[j]);
        }
    }
    return count << 1;
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        int e;
        vector<int> v;
        cin >> e;
        while (e--) {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }
        cout << solve(v) << endl;
    }
}
