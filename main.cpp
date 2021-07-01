#include "hwlib.hpp"
#include <stdint.h>
#include "DHT11.hpp"
#include "neopixel.hpp"


void schermpje(uint8_t temp1, uint8_t temp2, uint8_t temp3, uint8_t temp4, uint8_t hum_gem){
    auto scl     = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda     = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 

    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from( oled, font );
    
    display 
     << "\f" << "CPU-Onder | " << temp1 << " C"
     << "\n" << "CPU-Boven | " << temp2 << " C"
     << "\n" << "GPU-Links | " << temp3 << " C"
     << "\n" << "GPU-Rechts| " << temp4 << " C"
     << "\n" << "-------------------------------------"
     << "\n" << "Humidity  | " << hum_gem << " %"
     << hwlib::flush;  
}

int main( void ){
    auto meter_1 = hwlib::target::pin_in_out(hwlib::target::pins::d6); 
    DHT11 sensor1(meter_1);
    
    auto meter_2 = hwlib::target::pin_in_out(hwlib::target::pins::d7); 
    DHT11 sensor2(meter_2);
    
    auto meter_3 = hwlib::target::pin_in_out(hwlib::target::pins::d3); 
    DHT11 sensor3(meter_3);
    
    auto meter_4 = hwlib::target::pin_in_out(hwlib::target::pins::d2); 
    DHT11 sensor4(meter_4);
    
    auto pin_led_ring = hwlib::target::pin_out(hwlib::target::pins::d8);
    unsigned int n_leds = 32;    
    neopixel led_ring(pin_led_ring, n_leds);
    uint32_t cold = 0x200000;
    uint32_t normal = 0x202000; 
    uint32_t warm = 0x004000;
    
    
//    uint32_t off = 0x000000;
//    for (;;){
//        led_ring.show(n_leds, cold);
//        hwlib::wait_ms(1000);    
//        led_ring.show(n_leds, normal);
//        hwlib::wait_ms(1000);    
//        led_ring.show(n_leds, warm);
//        hwlib::wait_ms(1000);
//        led_ring.show(n_leds, off);
//        hwlib::wait_ms(1000);
//    }
    
    for (;;){
        float hum1 = sensor1.get_humidity();
        float temp1 = sensor1.get_temperature();
        float hum2 = sensor2.get_humidity();
        float temp2 = sensor2.get_temperature();
        float hum3 = sensor3.get_humidity();
        float temp3 = sensor3.get_temperature();
        float hum4 = sensor4.get_humidity();
        float temp4 = sensor4.get_temperature();
        float temp_gem = (temp1 + temp2 + temp3 + temp4) / 4;
        float hum_gem = (hum1 + hum2 + hum3 + hum4) / 4;
        schermpje(temp1, temp2, temp3, temp4, hum_gem);
        if (temp_gem < 20){
            led_ring.show(n_leds, cold);
        }else if (temp_gem >= 20 && temp_gem < 30){
            led_ring.show(n_leds, normal);
        }else if (temp_gem >= 30){
            led_ring.show(n_leds, warm);
        }
    }
}