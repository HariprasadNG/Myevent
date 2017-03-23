#include <iostream>
#include <vector>
using namespace std;

vector<int> bts;

int count(int n) {
    if(bts.size() == 0) {
        bts.push_back(0);
        bts.push_back(1);
        bts.push_back(2);
    }
    
    if (n < bts.size()) {
        return bts[n];
    }
    
    for (int i = bts.size(); i <= n; i++) {
        int count  = 0;
        for (int j = i - 1; j >= 0; j--) {
            count = count + bts[j==0?1:j]*bts[(i-j-1)==0?1:(i-j-1)];
        }
        bts.push_back(count);
    }

    return bts[n];
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        int x;
        cin >> x;
        cout << count(x) << endl;
    }
}
