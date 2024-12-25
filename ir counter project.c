#include <reg51.h>
#define lcd_data_port P2  // Use Port 2 for data port
sbit rs = P3^0;           // Register select pin
sbit rw = P3^1;           // Read/Write pin
sbit en = P3^2;           // Enable pin
sbit ir_sensor = P3^3;    // IR sensor input pin
unsigned int count = 0;   // Variable to store count

void delay(unsigned int count) {
    unsigned int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < 112; j++);
}

void LCD_Command(unsigned char cmd) {
    lcd_data_port = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    delay(1);
    en = 0;
    delay(5);
}

void LCD_Char(unsigned char char_data) {
    lcd_data_port = char_data;
    rs = 1;
    rw = 0;
    en = 1;
    delay(1);
    en = 0;
    delay(10);
}

void LCD_String(unsigned char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) {
        LCD_Char(str[i]);
    }
}

void LCD_Init(void) {   
    delay(20);
    LCD_Command(0x38); // 2 lines and 5x7 matrix
    LCD_Command(0x0C); // Display on, cursor off
    LCD_Command(0x06); // Increment cursor
    LCD_Command(0x01); // Clear display
    LCD_Command(0x80); // Force cursor to the beginning of the first line
}

void LCD_DisplayNumber(unsigned int num) {
    char buffer[5];
    buffer[0] = (num / 1000) + '0';
    buffer[1] = ((num / 100) % 10) + '0';
    buffer[2] = ((num / 10) % 10) + '0';
    buffer[3] = (num % 10) + '0';
    buffer[4] = '\0';
    
    LCD_Command(0xC0); // Force cursor to the beginning of the second line
    LCD_String(buffer);
}

void main() {
    LCD_Init();
    LCD_Command(0x80); 
    LCD_String("Count: ");
    
    while (1) {
        if (ir_sensor == 0) { // If IR sensor detects an object
            count++;          // Increment count
            while (ir_sensor == 0); // Wait until the object passes
            LCD_DisplayNumber(count);	// Display the updated count
       
        if(count==1000)
				{
					count=0;
				}
    }
}
		}
