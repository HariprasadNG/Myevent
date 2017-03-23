#include<iostream>
#include<vector>
using namespace std;

int maxDiff(vector<int> v) {
    int x;
    int max = 0;
    for (int i = 0; i < v.size() ; i++) {
        if(i!=0 && v[0] < v[i]) {
            continue;
        }
        x = v.size() - 1;
        if ((x - i) < max) return max;
        while(x > i) {
            if(v[x]>=v[i]) {
                break;
            }
            x--;
        }
        max = (x-i) > max? (x-i):max;
        if(max == v.size()-1) return max;
    }
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int l;
        cin >> l;
        vector<int> ip;
        for (int x = 0 ; x < l; x++) {
            int temp;
            cin >> temp;
            ip.push_back(temp);
        }

        cout << maxDiff(ip) << endl;
    }
}
