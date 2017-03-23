#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

int solve(map<int,int> &sl) {
    vector<int> sol(30);

    sol[0] = 0;
    for (int i = 1; i < 30; i++) {
        if(sl.find(i) == sl.end()) {
            sol[i] = 999;
        } else if (sl[i] < i) {
            sol[i] = 10000;
        } else {
            sol[i] = 999;
        }
    }

    for (int i = 1; i <= 6; i++) {
        if (sl.find(i) == sl.end()){ 
            sol[i] = 1;
        } else if (sl[i] > i) {
            sol[sl[i]] = 1;
            sol[i] = 1;
        } else {
            sol[i] = 10000;
        }
    }

    for (int i = 7; i < 30; i++) {
        if (sol[i] == 10000) {
            continue;
        }
        
        for (int j = 6; j >= 1; j-- ) {
            sol[i] = ((sol[i-j] + 1) > sol[i]) ? sol[i] : (sol[i-j] + 1);
        }

        if (sl.find(i) != sl.end()) {
            sol[sl[i]] = sol[i] < sol[sl[i]] ? sol[i]:sol[sl[i]];
        }
    }
    return sol[29];
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        map<int, int> sl;
        while (n--) {
            int s, d;
            cin >> s >> d;
            sl.insert({s-1,d-1});
        }
        cout << solve(sl) << endl;
    }
}
