#include <avr/io.h>
#include <util/delay.h>


const uint8_t segments[10] = {
    0xFC,
    0x60,
    0xDA,
    0xF2,
    0x66,
    0xB6,
    0xBE,
    0xE0,
    0xFE,
    0xF6 
};


int main(void){
    int i = 0;
    uint8_t lastA;
    uint8_t currentA;
    DDRA = 0xFE;
    DDRC &= ~(0x83);
    PORTC |= 0x83;
    PORTA = segments[i];
    lastA = PINC & 0x02;


    while(1){

        currentA = PINC & 0x02;

        if (lastA != 0 && currentA == 0) {
            _delay_ms(5);

            if ((PINC & 0x02) == 0) {
                if ((PINC & 0x01) != 0) {
                    i++;
                    if (i > 9) {
                        i = 0;
                    }
                }
                else {
                    i--;
                    if (i < 0) {
                        i = 9;
                    }
                }

                PORTA = segments[i];
            }
        }

        lastA = PINC & 0x02;


        if (((PINC & 0x80) == 0)){
            _delay_ms(20);
            if (((PINC & 0x80) == 0)){
                i++;
                if (i > 9){
                    i=0;
                }
                PORTA = segments[i];
                while(((PINC & 0x80) == 0)){

                }
            }
        }

        // for(i = 1; i < 9; i++){
        //     PORTA = segments[i];
        //     _delay_ms(1000);
        // }
        // i = 0;
        // PORTA = segments[i];
    }
}