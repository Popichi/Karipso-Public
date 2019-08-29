#include <stdio.h>
#define BIT3HI 0x04 // 0000 0100

int main (void) {
    char bitBang = 0;
    char bitThreeTest = bitBang & BIT3HI; // Test bit 3
    bitBang |= BIT3HI;                    // Set bit 3
    bitBang &= 0xFB;                      // Clear bit 3
    bitBang ^= BIT3HI;                    // Toggle bit 3

   return 0;
}
