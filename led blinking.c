#include <REGX51.H>
#include <stdlib.h>

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 1275; j++); // Inner loop for approximate delay
    }
}

void main(void) {
    while (1) {
        P1 = 255; // Turn ON all LEDs (set all bits to 1)
        delay(100); // Wait for 500 ms
        P1 = 0; // Turn OFF all LEDs (clear all bits)
        delay(100); // Wait for 500 ms
    }
}
