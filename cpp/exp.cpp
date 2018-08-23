#include<iostream>
#include<vector>

using namespace std;

vector<int> Solve(string ip, unsigned int &s) {
    vector<int> res(26, 0);
    if (s >= ip.length()) {
        return res;
    }

    bool p = true;
    for  (;s < ip.length(); s++){
        if (ip[s] >= 'a' && ip[s] <= 'z') {
            if (p) {
                res[ip[s] - 'a']++;
            } else {
                res[ip[s] - 'a']--;
            }
        } else if (ip[s] == '+') {
            p = true;
        } else if (ip[s] == '-') {
            p = false;
        } else if (ip[s]  == '(') {
            s++;
            vector<int> pr = Solve(ip, s);
            if (p) {
                for (int i = 0; i < pr.size(); i++) {
                    res[i] += pr[i];
                }
            } else {
                for (int i = 0; i < pr.size(); i++) {
                    res[i] -= pr[i];
                }
            }
        } else if (ip[s] == ')') {
            s++;
            return res;
        }
    }
    return res;
}

int main () {
 string ip = "a + b + b - (a + b - (c - d))";
 cin >> ip;
 cout << "HARI " <<  ip << endl;
 unsigned int s = 0;
 vector<int> res = Solve(ip, s);
 for (auto x: res) {
    cout << x << ", ";
 }
 cout << endl ;
}
