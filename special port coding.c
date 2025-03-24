#include <REGX51.H>

sbit mybit1 = P0^0;
sbit mybit2 = P0^1;
sbit mybit3 = P0^2;
sbit mybit4 = P0^3;
sbit inputbit1 = P1^0;
sbit inputbit2 = P1^1;
sbit inputbit3 = P1^2;
sbit inputbit4 = P1^3;

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 1275; j++); // Inner loop for approximate delay
    }
}

void main(void) {
    while (1) {
        P1 = 0xFF; // Set all P1 pins high to enable pull-up resistors
        P0 = 0x00; // Clear all P0 pins initially
        
        if (inputbit1 == 0) {
            mybit1 = 1; // Set mybit1 high
        } else {
            mybit1 = 0; // Set mybit1 low
        }
        
        if (inputbit2 == 0) {
            mybit2 = 1; // Set mybit2 high
        } else {
            mybit2 = 0; // Set mybit2 low
        }
        
        if (inputbit3 == 0) {
            mybit3 = 1; // Set mybit3 high
        } else {
            mybit3 = 0; // Set mybit3 low
        }
        
        if (inputbit4 == 0) {
            mybit4 = 1; // Set mybit4 high
        } else {
            mybit4 = 0; // Set mybit4 low
        }

        delay(100); // Add a small delay to debounce the inputs
    }
}
