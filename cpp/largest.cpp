#include<string>
#include<algorithm>
#include<iostream>
#include<set>

using namespace std;

void solve(int n) {
    vector<string> ip;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ip.push_back(to_string(x));
    }

    sort(ip.begin(), ip.end(),
    [](const string &s1, const string &s2){
        return (s1+s2) > (s2+s1);
    });
    for(auto x: ip) {
        cout << x;
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i =0; i < t; i++) {
        int n;
        cin >> n;
        solve(n);
    }
}
