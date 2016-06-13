#include <stdio.h>

int main () {
    int curpos = 2;
    for(int i = 0; i < 10000; i++) {
        curpos = 2;
        int n = i;
        bool lucky = true;
        while (n >= curpos) {
            if (n%curpos == 0) {
                lucky = false;
                break;
            }
            n = n - n/curpos;
            curpos++;
        }
        if(lucky) {
            printf("%d,", i);
        }
    }
}
