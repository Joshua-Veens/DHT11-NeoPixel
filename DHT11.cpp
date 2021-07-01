#include "DHT11.hpp"

DHT11::DHT11(
    hwlib::target::pin_in_out & pin, 
    uint8_t error, 
    uint_fast64_t now,
    uint_fast64_t time,  
    uint8_t data[5], 
    unsigned int loopcounter, 
    uint8_t index,
    uint8_t cnt):
    pin ( pin )
    {}


void DHT11::start_up() {
    pin.direction_set_output();
    pin.write( 1 );
    pin.flush();
    hwlib::wait_ms(1200);
    
    pin.write( 0 );
    pin.flush();
    hwlib::wait_ms( 20 );
    
    pin.write( 1 );
    pin.flush();
    
    pin.direction_set_input();
    hwlib::wait_us( 40 );
    
    loopcounter = TIMEOUT;
    while (pin.read() == 0){
        if (loopcounter-- == 0){
            error += 40;
            break;
        }
    }
    loopcounter = TIMEOUT;
    while (pin.read() == 1){
        if (loopcounter-- == 0) {
            error += 80;
            break;
        }
    }
}
    
void DHT11::read_data(){
    index = 0;
    cnt = 0;
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;
    for (unsigned int i = 0; i < 40; i++) { 
        
        loopcounter = TIMEOUT;
        while (pin.read() == 0){
            if (loopcounter-- == 0){
                break;
            }
        }
        
        loopcounter = TIMEOUT;
        now = hwlib::now_us();
        while (pin.read() == 1){
            if (loopcounter-- == 0){
                break;
            }
        }
        time = hwlib::now_us() - now;
        
        if (time > 40){
            data[index] = data[index] << 1;
            data[index] |= 1;
        }else{
            data[index] = data[index] << 1;
        }
        if (cnt == 7){
            index++;
            cnt = 0;
        }else{
            cnt++;
        }
    }
}

float DHT11::get_temperature() {
    DHT11::start_up();
    DHT11::read_data();
    float temp = data[2];
    if (data[3] & 0x80) {
    temp = -1 - temp;
    }
    temp += (data[3] & 0x0f) * 0.1;
    return temp;
}

float DHT11::get_humidity() {
    DHT11::start_up();
    DHT11::read_data();
    return data[0];
}

float DHT11::get_errors() {
    if ( error == 0 ) {
        if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
            error += 0;
        }else{
            error += 10;
        }
    }else{
        return error;
    }
    return error;
}