#include<vector>
#include<iostream>
#include<utility>
#include<limits>
using namespace std;

void min_max(vector<int> &v) {
    int max = numeric_limits<int>::min();
    int min = -1;
    for (int w = 1; w <= v.size(); w++) {
        max = numeric_limits<int>::min();
        min = -1;
        for (int i = 0; i <= (v.size() - w); i++) {
            if (i-1 == min) {
               min = i;
               for (int x = 1; x < w; x++) {
                    if(v[x+i] <= v[min]) {
                        min = x+i;
                    }
               }
            }
            if (max < v[min]) {
                max = v[min];
            }
        }
        cout << max << " ";
    }
}

int main () {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        vector<int> v;
        for (int j = 0; j < n; j++) {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }
        min_max(v);
        cout << endl;
    }
}
