#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef unsigned long long ull;

ull countStepFrom(ull s, ull m, ull n ) {
    queue<ull> q;
    q.push(s);
    ull count = 0;
    if (s == 0 && m > 0)return 0;
    if (s == 0 & m == 0)return 1;
    while (!q.empty()) {
        ull x = q.front();
        q.pop();
        if (x >= m && x <= n) {
            count++;
        }
        if (x < n ) {
            if (x%10 != 0) {
                q.push(x*10 + (x%10) - 1);
            }
            if (x%10 != 9) {
                q.push(x*10 + (x%10) + 1);
            }
        }
    }
    return count;
}

ull count_step (ull m, ull n) {
    ull count = 0;
    for(ull i = 0; i <= 9; i++) {
        count += countStepFrom(i, m, n);
    }
    return count;
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        ull m, n;
        cin >> m >> n;
        cout << count_step(m,n) << endl;
    }
}
