#include<iostream>
#include<vector>
#include<string>
#define MAX(A,B) A>B?A:B;
using namespace std;

//If s = abcaeabcabd then this version
//print worng answer fo SP[9]
//SP[9] = 0 As per this program
//But it is actually 2 (ab)
//Note:If we impliment KMP with the below
//Preprocessing then that will not faile
//But the prformance will be low.
auto ComputeSp(string S) {
    vector<int> r;
    r.push_back(0);

    for (int i =1; i < S.length(); i++) {
        if (S[r[i-1]] == S[i]) {
            r.push_back(r[i-1] + 1);
        } else {
            r.push_back(0);
        }
    }

    return r;
}

//Z_Algo copied from Z-Algo
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
                //S[r - k + 1] so x = r - k + 1;
                x = r-k+1;
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

auto Z_AlgoBasedPreProc(string S) {
    auto zR = Z_Algo(S);
    vector<int> tr;
    for (int i = 0; i < S.length(); i++) {
        tr.push_back(0);
    }
    for (int i = 1; i < S.length(); i++) {
        if (zR[i] != 0) {
            tr[ i + zR[i] - 1] = zR[i];
        }
    }
    for (int i = S.length() - 1; i >= 1; i--) {
        tr[i] = MAX(tr[i], tr[i+1]-1);
    }

    return tr;
}

auto KMP (string T, string P) {
    vector<int> r;
    int ti = 0;
    int pi = 0;
    auto Z = Z_AlgoBasedPreProc(P);
    while ( (T.length() - ti) >= P.length() ) {
        if (T[ti + pi] != P[pi]) {
            if (pi == 0) {
                ti++;
            } else {
                ti += pi - Z[pi-1];
                pi = Z[pi-1];
            }
        } else {
            pi++;
            if (pi == P.length()) {
                r.push_back(ti);
                ti++; //This can be optimized think of
                pi = 0;
            }
        }
    }
    return r;
}

int main () {
    string T;
    cin >> T;
    string P;
    cin >> P;
    //auto r = Z_AlgoBasedPreProc(S);//ComputeSp(S);
    auto r = KMP(T, P);
    for (auto x = r.begin();
              x != r.end();
              x++){
        cout << *x << ",";
    }
    cout << endl;
}
