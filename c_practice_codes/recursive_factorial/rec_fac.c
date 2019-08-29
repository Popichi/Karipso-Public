#include <stdio.h>

long int fac(int n) {
    if (n >= 1) {
        return n*fac(n-1);
    } else {
        return 1;
    }
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    printf("Factorial of %d = %ld\n", n, fac(n));
    return 0;
}

