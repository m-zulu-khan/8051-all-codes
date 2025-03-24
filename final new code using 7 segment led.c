#include <reg51.h>
 #define msec 100
unsigned int digit[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10};
sbit d2=P3^0;
sbit d1=P3^1;
sbit d0=P3^2;
sbit d= P3^3;       
sbit hours = P1^0;
sbit minus = P1^1;
sbit start = P1^2;
sbit relay = P1^4;
bit count = 0;
int seconds = 59;
int minutes = 0;
int hour = 0;
char number[4];

void delay(unsigned int count) {
    int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < 112; j++);
}


void LCD_DisplayTime( ) {
    char number[4];

    number[0] = hour / 10;     // Tens place of the hour
    number[1] = hour % 10;     // Units place of the hour
    number[2] = minutes / 10;  // Tens place of the minutes
    number[3] = minutes % 10;  // Units place of the minutes

    d = 1;
	d2 = d0 = d1= 0;
	 P2 = digit[number[3]];
	delay(msec);
    
   d0 = 1;
	d1 =d=d2= 0;
	 P2 = digit[number[2]];
	delay(msec);
	
	d1 = 1;
	d2 =d=d0= 0;
	P2 = digit[number[1]];
	delay(msec);
	
	d2 = 1;
	d1 =d=d0= 0;
	P2 = digit[number[0]];
	delay(msec);


}

void decrementHour() {
  //  hour--;
    if (hour <= 0) {
        relay = 0;
        while (1) {     
           LCD_DisplayTime( );
           
        }
    }
}

void decrementMinutes() {
 if(minutes <= 0)
 {
  minutes = 59;
   hour--;
 }   
				   minutes--;
    if (minutes <= 0) {
        decrementHour();
    }
}

void decrementTime() {
  while(1){
       
	   
	if(minutes >0){
       relay = 1;
			 seconds--;
			 
  if (seconds <= 0) {
    seconds = 59;
     decrementMinutes();
  }
		
    LCD_DisplayTime();
    delay(1000);
}
}
	}


void set_time() {
    while (1) {
			 LCD_DisplayTime( );
        if (hours == 0) {       
            hour++; 
            if (hour > 5) {
                hour = 0;
            }
         LCD_DisplayTime( );
            delay(1000);
        }
        
        if (minus == 0) {
            minutes++;
            if (minutes > 59) {
                minutes = 0;
            }
            LCD_DisplayTime( );
            delay(1000);
        }
        
        if (start == 0) {
             decrementTime();
        }
				delay(msec);
    }
}

void main() {
	while(1)
	{
	 LCD_DisplayTime( );
    P1 = 0x0F;  // Set P1.3, P1.2, P1.1, P1.0 high and the rest low
    set_time();
	}
}

