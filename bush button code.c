#include <reg51.h>

sbit LED_pin = P2^0;
sbit switch_pin = P1^0;

void Delay(int); // Function prototype for delay

void main() {
	LED_pin= 0;
	switch_pin = 1;
    while(1) {
        if(switch_pin == 0) { // If switch is pressed
             // Delay for 2 seconds
            LED_pin = 1; // Turn off LED
        }
				else 
				{
					 LED_pin = 0;
    }
}
}