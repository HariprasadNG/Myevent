#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
ull nChoosek( ull n, ull k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    lli result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

double WaterFill(int r, int c, int qt) {
    ull mp = nChoosek(r-1, c-1);
    cout << (1<<r) << endl;
    return (double)(qt * mp)/(double)(1<<r);
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int r, c, qt;
        cin >> qt >> r >> c;
        cout << WaterFill(r, c, qt) << endl;
    }
}
