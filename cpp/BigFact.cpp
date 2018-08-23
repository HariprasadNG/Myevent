#include <deque>
#include <iostream>

using namespace std;

void bigFact (int n) {
    deque<int> v;
    v.push_back(1);
    for (int i = 1; i <= n; i++) {
        for (auto x = v.begin(); x != v.end(); x++) {
            *x = *x * i;
        }
        for (int j = v.size()-1; j >= 0 ; j--) {
            int c = v[j]/10;
            if (c) {
                v[j] = v[j]%10;
                if ( j == 0) {
                    v.push_front(c);
                    while(v[0]/10) {
                        int nc = v[0]/10;
                        v[0] = v[0] % 10;
                        v.push_front(nc);
                    }
                } else {
                    v[j-1] += c;
                }
            }
        }
    }
    for (auto x: v) {
        cout << x;
    }
    return ;
}

int main () {
    int x;
    cin >> x;
    bigFact(x);
    return 0;
}
