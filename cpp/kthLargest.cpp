#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main () {
    int T;
    cin >> T;
    while(T--) {
        unsigned int k;
        cin >> k;
        int n;
        cin >> n;
        priority_queue<int, vector<int>, greater<int>> pq;
        while (n--) {
            int x;
            cin >> x;
            if (pq.size() < k) {
                pq.push(x);
            } else if (pq.top() < x) {
                pq.pop();
                pq.push(x);
            }
            if(pq.size() < k) {
                cout << -1 << " ";
            } else {
                cout << pq.top() << " ";
            }
        }
    }
}
