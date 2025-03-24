#include <reg51.h>              // Include 8051 header file
#define lcd_data_port P2        // Define Port 2 for data port

sbit rs = P1^0;                 // Register select pin at Port 1, Pin 0
sbit rw = P1^1;                 // Read/Write pin at Port 1, Pin 1
sbit en = P1^2;                 // Enable pin at Port 1, Pin 2
sbit ir_sensor = P1^3;          // IR sensor input pin at Port 1, Pin 3
unsigned int count = 0;         // Initialize count variable to store count

void delay(unsigned int count) {
    unsigned int i, j;
    for (i = 0; i < count; i++) // Loop to create a delay
        for (j = 0; j < 112; j++); // Nested loop for delay
}

void LCD_Command(unsigned char cmd) {
    lcd_data_port = cmd;        // Send command to LCD
    rs = 0;                     // Set RS to 0 for command
    rw = 0;                     // Set RW to 0 for write
    en = 1;                     // Set Enable to high
    delay(1);                   // Wait for a short period
    en = 0;                     // Set Enable to low
    delay(5);                   // Wait for the command to execute
}

void LCD_Char(unsigned char char_data) {
    lcd_data_port = char_data;  // Send character data to LCD
    rs = 1;                     // Set RS to 1 for data
    rw = 0;                     // Set RW to 0 for write
    en = 1;                     // Set Enable to high
    delay(1);                   // Wait for a short period
    en = 0;                     // Set Enable to low
    delay(10);                  // Wait for the character to be written
}

void LCD_String(unsigned char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) { // Loop through the string
        LCD_Char(str[i]);           // Send each character to LCD
    }
}

void LCD_Init(void) {
    delay(20);                  // Initial delay
    LCD_Command(0x38);          // Command to set LCD to 2 lines and 5x7 matrix
    LCD_Command(0x0C);          // Command to turn on display and turn off cursor
    LCD_Command(0x06);          // Command to increment cursor
    LCD_Command(0x01);          // Command to clear display
    LCD_Command(0x80);          // Command to set cursor to the beginning of the first line
}

void LCD_DisplayNumber(unsigned int num) {
    char buffer[5];
    buffer[0] = (num / 1000) + '0'; // Extract and convert thousands place digit to char
    buffer[1] = ((num / 100) % 10) + '0'; // Extract and convert hundreds place digit to char
    buffer[2] = ((num / 10) % 10) + '0'; // Extract and convert tens place digit to char
    buffer[3] = (num % 10) + '0'; // Extract and convert units place digit to char
    buffer[4] = '\0'; // Null-terminate the string
    
    LCD_Command(0xC0); // Command to set cursor to the beginning of the second line
    LCD_String(buffer); // Display the number on LCD
}

void main() {
    LCD_Init();              // Initialize the LCD
    LCD_Command(0x80);       // Set cursor to the beginning of the first line
    LCD_String("Count: ");   // Display "Count: " on the LCD
    
    while (1) {
        if (ir_sensor == 0) {  // If IR sensor detects an object
            count++;           // Increment count
            while (ir_sensor == 0); // Wait until the object passes
            LCD_DisplayNumber(count); // Display the updated count
            
            if (count == 1000) {  // If count reaches 1000
                count = 0;        // Reset count to 0
            }
        }
    }
}
