#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

float running_med() {
   priority_queue<int, vector<int>, greater<int>> max_side;
   priority_queue<int, vector<int>, less<int>> min_side;
   float med;
   unsigned long long n;
   cin >> n;
   while(n--) {
       int x;
       cin >> x;
       if (!max_side.empty() && max_side.top() < x) {
           max_side.push(x);
           if( (max_side.size() -  min_side.size()) > 1) {
                int f = max_side.top();
                min_side.push(f);
                max_side.pop();
           }
       } else {
           min_side.push(x);
           if ( (min_side.size() - max_side.size()) > 1) {
               int f = min_side.top();
               max_side.push(f);
               min_side.pop();
           }
       }
       if ( (min_side.size() + max_side.size()) %2 == 0) {
           med  = (min_side.top() + max_side.top()) / 2;
       } else {
           if(min_side.size() > max_side.size())
            med = min_side.top();
           else
            med = max_side.top();
       }
       cout << med << " ";
   }
   return med;
}

int main () {
    running_med();
}
