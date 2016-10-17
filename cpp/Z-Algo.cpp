#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> Z_Algo(string S) {
    auto len = S.length();
    vector<int> Z;
    Z.reserve(len);
    Z.push_back(0);
    int r = 0;
    int l = 0;
    auto *s = S.c_str();
    int x = 0;
    for (int i = 1; i<len; i++) {
        if (s[i] != s[x]) {
            break;
        } else {
            x++;
        }
    }

    if (x==0) {
        r = 0; l = 0;
    } else {
    }
    Z.push_back(x);
    l = 1;
    r = x;

    for (int k = 2; k < len; k++) {
        if (k > r) {
            x = 0;
            for (int i = k; i < len; i++) {
                if (s[i] != s[x]) {
                    break;
                } else {
                    x++;
                }
            }
            l = k;
            r = k + x - 1;
            Z.push_back(x);
        } else {
            //We have from l to r same as 
            // 0 to r - l so the value of 
            //Z[k-l] has info about value
            //Z[k] i.e
            if (r - k + 1 <= Z[k - l]) {
                //if Z[k-l] >= r-k+1
                //We are sure that that 
                //from k to r all the char (r-k+1)chars
                // is same as (k-l) to ((k-l) + (r-k+1))
                Z.push_back(r-k+1);
                //Now try to find any newly matched from S[r+1]
                //S[r+1-l] so x = r+1 - l;
                x = r+1 - l;
                for (int i = r+1; i < len; i++) {
                    if (s[i] != s[x]) {
                        break;
                    } else {
                        Z[k]++;
                        r++;
                    }
                }
                l = k;
            } else {
                //k-r is same  as k-l to r-l
                //Z[k-l] < (r -k +1)chars
                //So Z[k] will also be same lenght
                //as of Z[k-l]
                Z.push_back(Z[k-l]);
            }
        }
    }
    return Z;
}

vector<int> find_pattern(string T, string P) {
    string C = P;
    C.append("$");
    C.append(T);
    auto Z = Z_Algo(C);
    vector<int> R;
    int i =0;
    for (auto x = Z.begin(); x != Z.end(); x++,i++) {
        if (*x == P.length()) {
            R.push_back(i - P.length() - 1);
        }
    }
    return R;
}


int main () {
    string t;
    cin >> t;
    string p;
    cin >> p;
    auto Z = find_pattern(t, p);
    for (auto x = Z.begin(); x != Z.end(); x++) {
        cout << *x << ",";
    }
    cout << endl;
}
