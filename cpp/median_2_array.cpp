#include<iostream>
#include<vector>
using namespace std;
float median(vector<int> &v1, vector<int> &v2) {
    int n1 = v1.size();
    int n2 = v2.size();
    int s1 = 0, s2 = 0;
    int x = (n1 + n2)/2;
    int mid1 = n1/2;
    int mid2 = x - mid1;
    if (mid2 >= n2) {
        int delta = mid2 - (n2 - 1);
        mid2 = n2 - 1;
        mid1 += delta;
    }

    int r1 = v1[mid1];
    int l1 = (mid1 - 1 >= 0) ?v1[mid1 -1]: v2[mid1];
    int r2 = v2[mid2];
    int l2 = (mid2 - 1 >= 0) ?v2[mid2 -1]: v2[mid1];

        cout << l1 << ":" << r1 << "(" << n1 <<")::" << l2 << ":" << r2 << "(" << n2  << ")" << endl;
        cout << s1 << ":" << n1 << "::" << s2 << ":" << n2 << endl;

    while (true) {
        if ( l1 <=  r2  && 
             l2 <= r1 ){
            //x-2, x-1, x, x+1
            cout << l1 << ":" << r1 << "::" << l2 << ":" << r2 << endl;
            if ( l2 >= l1 ) {
                //After rearrage ....l1, l2,.... 
                if ( r1 < r2) {
                    if ( (v1.size() + v2.size()) % 2) return r1;
                    return (l2 + r1)/2.0;
                } else {
                    if ( (v1.size() + v2.size()) % 2) return r2;
                    return (l2 + r2)/2.0;
                }
            } else if (r2 <= r1) {
                //After rearrage ........ r2, r1, .... 
                if ((v1.size() + v2.size())%2 == 1) return r2;
                if ( l1 > l2) {
                     return (l1 + r2)/2.0;
                } else {
                    return (l2 + r2)/2.0;
                }
            } else { 
                //After rearrange ...l2, l1, r1, r2, ....
                if ((v1.size() + v2.size())%2 == 1) return r1;
                if ((v1.size() + v2.size())%2 == 1) return l2;
                return (l1 + r1)/2.0;
            }
        } else if ( r2 < l1) {
            int delta = mid2;
            s2 = mid2 + 1;
            n1 = mid1 + 1;
            if ( s2 == v2.size()) {
                int y = x - v2.size();
                if ( (n1 + n2) % 2 == 0) {
                    int l;
                    if ( y != 0)
                        l = (v2[v2.size() - 1] >= v1[y-1])? v2[v2.size() -1] : v1[y-1];
                    else 
                        l = v2[v2.size() -1];
                    return (l + v2[y])/2;
                } else {
                    return v1[y];
                }
            }
            mid2 = (s2 + v2.size()-1)/2;
            delta = mid2 - delta;
            mid1 += delta;
        } else {
            int delta = mid1; 
            s1 = mid1 + 1;
            n2 = mid2 + 1;
            if (s1 == v1.size()) {
                int y = x - v1.size();
                if ((n1 + n2) % 2 == 0) {
                    int l;
                    if ( y != 0)
                        l = (v1[v1.size() - 1] >= v2[y-1])? v1[v1.size() -1]: v2[y -1];
                    else
                        l = v1[v1.size() - 1];
                    return (l + v1[y])/2;
                } else {
                    return v2[y];
                }
            }
            mid1 = (s1 + v1.size() - 1) /2;
            delta = mid1 - delta;
            mid2 += delta;
        }
         r1 = v1[mid1];
         l1 = (mid1 - 1 >= 0) ?v1[mid1 -1]: v2[mid1];
         r2 = v2[mid2];
         l2 = (mid2 - 1 >= 0) ?v2[mid2 -1]: v2[mid1];

    }
}

int main () {
    vector<int> v1 = {1,2,3,7};
    vector<int> v2 = {4,5,6,8,9};
    cout << (float)median(v1, v2) << endl;
}
