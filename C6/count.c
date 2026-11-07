#include <avr/io.h>


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
    DDRA = 0xFE;
    PORTA = segments[0];
    while(1){
        
    }
}