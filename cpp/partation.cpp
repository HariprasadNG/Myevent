#include <iostream>

using namespace std;

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y  = temp;
}

void print (int *a, int s, int e) {
    for(int i = s; i <= e; i++) {
        cout << a[i] << ",";
    }
}

int partationInterview(int*a, int s, int e) {
    int pv = a[e];
    int small = s;
    int large = e-1;
    for(int i = s; i < large; i++) {
        if(a[i] <= pv) {
            swap(a[small++],a[i]);
        } else {
            swap(a[i], a[large--]);
            i--; //This is required since we are not sure if a[large] was actually small than pv.
        }
    }

    swap(a[small], a[e-1]);
    return small; 
}

int partation(int *a, int s, int e) {
    if( s >= e) {
        return s;
    }
    int p = a[s];
    int i = s;
    int j = e;
    while (i < j) {
        if (a[i] <= p) {
            i++;
        } else {
            while (a[j] > p && (j > i ) ) j--;
            if( j == i) break;
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }

    if(a[i] > p) {
        swap(a[s], a[i-1]);
        return i;
    } else {
        if( i <= e )swap(a[s], a[i]);
        return i + 1;
    }
}


int main () {
    int a[] = {1,1,1,1,1,1,1};
    int p = a[0];
    int i = partation(a,0,(sizeof(a)/sizeof(int))-1);
    cout << "All elements from " << i << "(including) are > " << p << endl;
    print(a,0, (sizeof(a)/sizeof(int))-1);
}
