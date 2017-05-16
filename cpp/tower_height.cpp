#include <iostream>
#include <vector>
using namespace std;

int calc(vector<int> v, int max, int min, int k) {
    int d = (max - k) - (min + k);
    max = max - k;
    min = min + k;
    cout << "max:" << max << " min:" << min << " d:" << d << endl;
    for(auto x:v) {
        if ( (x - k >= min) && (x - k <= max)) {
            continue;
        } else if ((x + k >= min) && (x + k <= max)){
            continue;
        } else {
            if ( (max - (x-k)) > (x+k - min)) {
                max = x + k;
            } else {
                min = x - k;
            }
            d = max - min;
        }
    }

    return d;
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        int k;
        int n;
        vector<int> v;
        cin >> k >> n;
        int max = 0;
        int min = 501;
        while(n--) {
            int temp;
            cin >> temp;
            v.push_back(temp);
            if ( temp > max) {
                max = temp;
            } 
            if ( temp < min) {
                min = temp;
            }
        }
        if (v.size() == 1) {
            cout << v[0] << endl;
        }

        cout << calc(v, max, min, k) << endl;
    }
}
