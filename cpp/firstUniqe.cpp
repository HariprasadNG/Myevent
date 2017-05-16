#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <string.h>
using namespace std;

void FirstUnique(vector<char> &s)
{
    int a[26];
    memset(a,0, sizeof(a));
    queue<char> q;
    for (auto c:s) {
        if (a[c - 'a'] == false) {
            a[c - 'a'] = 1;
            q.push(c);
            cout << q.front();
        } else {
            a[c - 'a'] = 2;
            while(!q.empty() && a[q.front() - 'a'] == 2) {
                q.pop();
            }
            if(q.empty()) {
                cout << -1;
            }else {
                cout << q.front();
            }
        }
    }
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int cc;
        cin >> cc;
        vector<char> ip;
        while (cc--) {
            char c;
            cin >> c;
            ip.push_back(c);
        }
        FirstUnique(ip);
        cout << endl;
    }
}
