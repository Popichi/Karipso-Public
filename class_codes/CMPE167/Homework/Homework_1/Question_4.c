#include <stdio.h>
#include <math.h>

int main (void) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        printf("2^%d is = %f\n",i ,pow(2, i));
    }
    return 0;
}

