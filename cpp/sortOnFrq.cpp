#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;

pair<int,int> countArray[61];
void solve(int n) {
    cout << "reading " << n << endl;
    for (int i = 0; i < n; i++) {
        int ii;
        cin >> ii;
        countArray[ii].first++;
        countArray[ii].second = ii;
    }

    sort(countArray, countArray+61, [](const pair<int,int> &a, const pair<int,int> b) -> bool 
    {
        if (a.first == b.first) return a.second > b.second;
        return a.first > b.first;
    });

    for (int i = 0; i < 61; i++) {
        for(int j = 0; j < countArray[i].first; j++) {
            cout << countArray[i].second << " ";
        }
        countArray[i].first = 0;
        countArray[i].second = 0;
    }
    cout << endl;
}


int main () {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int l;
        cin >> l;
        solve(l);
    }
}
