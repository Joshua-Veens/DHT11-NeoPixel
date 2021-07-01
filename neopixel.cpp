#include "neopixel.hpp"

neopixel::neopixel(
    hwlib::target::pin_out & neo_pin, 
    unsigned int & num_leds,
    uint32_t colour,
    uint32_t tmp):
    neo_pin ( neo_pin ),
    num_leds ( num_leds ),
    colour ( colour ),
    tmp ( tmp )
    {}

void neopixel::send_one(){
    neo_pin.write ( 1 );
    neo_pin.write ( 1 );
    neo_pin.write ( 0 );
    neo_pin.write ( 0 );
}

void neopixel::send_zero(){
    neo_pin.write ( 1 );
    neo_pin.write ( 0 );
    neo_pin.write ( 0 );
}

void neopixel::reset(){
    neo_pin.write( 0 );
    hwlib::wait_ms(10);
}

void neopixel::show(unsigned int num_leds, uint32_t colour){
    reset();
    for (unsigned int i = 0; i < num_leds; i++){
        tmp = colour;
        for (unsigned int j = 0; j < 24; j++){
            if (tmp & 0x800000){
                send_one();
            }else{
                send_zero();
            }
            tmp <<= 1;
        }
    }
}

