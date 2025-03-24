#include <reg51.h>

// Define segment control for the 7-segment display
sbit segment_a = P2^0;
sbit segment_b = P2^1;
sbit segment_c = P2^2;
sbit segment_d = P2^3;
sbit segment_e = P2^4;
sbit segment_f = P2^5;
sbit segment_g = P2^6;

// Array to store segment values for digits 0-9
unsigned char digit[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Function to display a digit
void display_digit(unsigned char num) {
    // Set each segment pin according to the digit
    P2 = digit[num];
}

// Dummy delay function (needs to be properly implemented according to clock speed)
void delay() {
    int i, j;
    for(i = 0; i < 1000; i++) {
        for(j = 0; j < 100; j++);
    }
}

void main() {
    int i;
    while(1) {
        for(i = 0; i < 10; i++) {
            display_digit(i);
            // Add delay to view each digit clearly (assuming some delay function)
            delay();
        }
    }
}


