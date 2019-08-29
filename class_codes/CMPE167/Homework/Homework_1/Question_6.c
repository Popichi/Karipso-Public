#include <stdio.h>

int main (void) {
    int i = 0;
    for (i = 0; i < 1001; i++) {
        if (((i % 4) == 0) && ((i % 9) == 0)) {
            // If the number is divisible by 4 and 9
            printf("DEADBEEF\n");
        } else if ((i % 4) == 0) {
            // If the number is divisible only by 4
            printf("DEAD\n");
        } else if (((i / 9) % 2) == 0 && (i / 9) != 0 && (i % 9) == 0) {
            // If the number is EVENLY divisible by 9
            printf("BEEF\n");
        } else {
            // If the number doesn't satisfy any of the conditions above
            // then print the number itself
            printf("%d\n", i);
        }
    }
    return 0;
}
