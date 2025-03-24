#include <reg51.h>
void delay50ms(void);

void main() {
    
    
    while (1) {
        P0 = 0xFF;
        delay50ms();
			P0 = 0x00;
			 delay50ms();
    }
}

void delay50ms() {
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0xB0;
    TR0 = 1;
    while (TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}
