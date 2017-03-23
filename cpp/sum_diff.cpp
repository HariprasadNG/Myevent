#include<iostream>
#include<vector>

using namespace std;

int CountBits (int x) {
    int m = 1;
    int count = 0;
    for (int i = 0; i < sizeof(int); i++) {
        if (x & m) count++;
        m = m << 1;
    }
    return count;
}

int count(vector<int> &v) {
    int c = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            c += (2 * CountBits(v[i]^v[j]));
        }
    }
    return c;
}


int main () {
    int t;
    cin >> t;
    while (t) {
        int n;
        cin >> n;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }

        cout << count(v) << endl;
        t--;        
    }
}
