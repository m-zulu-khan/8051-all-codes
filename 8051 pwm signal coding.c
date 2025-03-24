#include <reg51.h>

// Define the PWM pin (e.g., P1.0)
sbit PWMPIN = P1^0;

// Delay function for timing
void delay(unsigned int time) {
  while (time--);
}

// Custom analogWrite function for 8051
void analogWrite(unsigned int dutyCycle) {
  unsigned int i;

  // Ensure dutyCycle is within 0-255
  if (dutyCycle > 255) {
    dutyCycle = 255;
  }

  // Generate PWM signal
  for (i = 0; i < 255; i++) {
    if (i < dutyCycle) {
      PWMPIN = 1;  // Set PWM pin HIGH
    } else {
      PWMPIN = 0; // Set PWM pin LOW
    }
    delay(1); // Short delay to create the PWM effect
  }
}

void main() {
  unsigned int brightness = 0;

  while (1) {
    // Increase brightness
    for (brightness = 0; brightness <= 255; brightness++) {
      analogWrite(brightness);
      delay(20000); // Adjust delay for visible effect
    }

    // Decrease brightness
    for (brightness = 255; brightness > 0; brightness--) {
      analogWrite(brightness);
      delay(20000); // Adjust delay for visible effect
    }
  }
}
