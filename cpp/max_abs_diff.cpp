#include<iostream>
#include<functional>
#include<vector>
#include<algorithm>
#include<limits>
using namespace std;

int max_abs_diff(vector<int> &ip) {
    vector<int> dif;
    int sum = 0;
    for (int i = 0; i < ip.size(); i++) {
        sum = sum + ip[i];
        dif.push_back(sum);
    }
    cout << endl;
    int max = abs(sum);
    for (int i = 0; i < ip.size(); i++) {
        max = (max < abs(dif[i] - (sum - dif[i])))? abs(dif[i] - (sum - dif[i])):max;
    }
    cout << endl;

    return max;
}

template<class compare>
int max_c_seq(vector<int> &ip, vector<int>&op, compare cp) {
    int max = 0;
    int rmax= 0;
    for (int i = 0; i < ip.size(); i++) {
        rmax += ip[i];
        if (cp(max, rmax)) {
            max = rmax;
        }
        if (cp(rmax, 0)) {
            rmax = 0;
        }
        op[i] = rmax;
        cout << op[i] << " ";
    }
    cout << endl;
    return max;
};

int max_diff(vector<int> ip) {
    greater<int> g;
    less<int> l;
    vector<int> f_fill_less(ip.size());
    vector<int> f_fill_greater(ip.size());
    vector<int> r_fill_less(ip.size());
    vector<int> r_fill_greater(ip.size());
    max_c_seq(ip, f_fill_greater, g);
    max_c_seq(ip, f_fill_less, l);
    reverse(ip.begin(), ip.end());
    max_c_seq(ip, r_fill_greater, g);
    max_c_seq(ip, r_fill_less, l);
    reverse(r_fill_greater.begin(), r_fill_greater.end());
    reverse(r_fill_less.begin(), r_fill_less.end());
    int max_s = numeric_limits<int>::min();//INT_MIN;//max(f_fill_less[ip.size() -1]);
    for (int i = 0; i < ip.size()-1; i++) {
        max_s = max(max_s, max((f_fill_less[i] - r_fill_greater[i+1]),(r_fill_less[i] - f_fill_greater[i+1])));
    }
    return max_s;
}

int main () {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> ip;
        while (n--) {
            int temp;
            cin >> temp;
            ip.push_back(temp);
        }

        cout << max_diff(ip) << endl;
    }
}
