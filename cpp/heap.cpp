#include <iostream>

using namespace std;

#define LEFT(i) (i)*2 + 1
#define RIGHT(i) (i)*2 + 2

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

void print(int *a, int l) {
    for (int i = 0; i < l; i++){
        cout << a[i] << ",";
    }
}

void swiftdown (int *a, int s, int l) {
    while (LEFT(s) < l) {
        if(RIGHT(s) >= l) {
            if(a[LEFT(s)] > a[s]) {
                swap(a[s], a[LEFT(s)]);
                return;
            }
        }
        if (a[LEFT(s)] < a[RIGHT(s)]) {
            if(a[s] > a[RIGHT(s)]) {
                return;
            }
            swap(a[s], a[RIGHT(s)]);
            s = RIGHT(s);
        } else {
            if(a[s] > a[LEFT(s)]) {
                return;
            }
            swap(a[s], a[LEFT(s)]);
            s = LEFT(s);
        }
    }
}

void heapify(int *a, int l) {
    l = l-1;
    if (RIGHT((l)>>1) <= l) {
        if (a[l>>1] < a[RIGHT(l>>1)]) {
            swap(a[l>>1], a[RIGHT(l>>1)]);
        }
    }
    if(a[l>>1] < a[LEFT(l>>1)]) {
        swap(a[l>>1], a[LEFT(l>>1)]);
    }
    for (int i = (l>>1) - 1; i >= 0; i--) {

        if (a[LEFT(i)] < a[RIGHT(i)]) {
            if(a[RIGHT(i)] > a[i] ) {
                swap(a[i], a[RIGHT(i)]);
                swiftdown(a, RIGHT(i), l+1);
            }
        } else {
            if (a[LEFT(i)] > a[i]) {
                swap(a[i],a[LEFT(i)]);
                swiftdown(a, LEFT(i), l+1);
            }
        }
        
    }
}


int main() {
    int a[] = {1,2,3,4,5,6,7,8};
    heapify(a, sizeof(a)/sizeof(int));
    print(a,sizeof(a)/sizeof(int));
}
