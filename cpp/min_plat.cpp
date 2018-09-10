#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>
#include<utility>
#include<queue>


using namespace std;
typedef unsigned int uint;

int min_lat(vector<pair<int,int>> S) {
    sort(S.begin(), S.end(), [](const pair<int,int> a, const pair<int,int> b)->bool
            {
                return a.first < b.first;
            });

    priority_queue<int, vector<int>, greater<int>> pq;
    int pl = 0; int maxP = 0;
    for (auto x : S) {
       pl++;
       while (pq.size() > 0 && x.first > pq.top()) {
            pq.pop();
            pl--;
       }
       maxP = max(pl, maxP);
       pq.push(x.second);
    }
    return maxP;
}

vector<pair<int, int>> combined_int(vector<pair<int,int>> s) {
    sort(s.begin(), s.end(), [](const pair<int,int> a, const pair<int,int> b) -> bool {
                return a.first < b.first;
            });
    pair<int, int> cs = s[0];
    vector<pair<int, int>> R;

    for (auto x:s) {
        if (cs.second > x.first) {
            if (cs.second < x.second) {
                cs.second = x.second;
            }
        } else {
            R.push_back(cs);
            cs = x;
        }
    }

    R.push_back(cs);
    return R;
}



int main () {
    vector<pair<int,int>> S = {{900,910}, {940,1200}, {950,1120}, {1100,1130}, {1500,1900}, {1800,2000}};
    cout << min_lat(S) << endl;
    vector<pair<int,int>> CI = combined_int(S); 
    for (auto x: CI) {
        cout << "{" << x.first << ", " << x.second << "}, ";
    }
    cout << endl;
}
