#include<iostream>
#include<string> 
#include<stack>

using namespace std;

int main () {
    int t = 0;
    cin >> t;
    for (int ii = 0; ii < t; ii++) {
        string ip;
        cin >> ip;
        stack<int> braces;
        for (int i = 0; i < ip.size(); i++) {
            if (ip[i] == '(') {
                braces.push(i);
            } else {
                if (!braces.empty() &&  ip[braces.top()] == '(') {
                    braces.pop();
                } else {
                    braces.push(i);
                }
            }
        }

        int max = 0;
        int e = ip.size();
        while (!braces.empty()) {
            if ((e - braces.top() - 1) % 2 == 0)
                max = (e - braces.top() - 1) > max ? (e - braces.top() - 1):max;
            e = braces.top();
            braces.pop();
        }
        if ((e) % 2 == 0)
            max = (e) > max? e:max;
        cout << max << endl;
    }
}
