#ifndef DHT11_HPP
#define DHT11_HPP
#define TIMEOUT 10000
#include <stdint.h>
#include "hwlib.hpp"

///@file

/// \brief
/// DHT11 Sensor by Joshua Veens
/// \details
/// DHT11 temperature and humidity sensor. 
/// Reads value's of temperature or humidity every 1.3 seconds. 
/// Gives back temperature in Celcius and humidity in percentage. 
///
/// Has error codes: 
/// 40 startup low signal timed out. 
/// 80 startup high signal timed out. 
/// 10 checksum was not correct. 
/// 0 Succes! 

class DHT11 {
private:
    hwlib::target::pin_in_out & pin;
    uint8_t error;
    uint_fast64_t now;
    uint_fast64_t time;
    uint8_t data[5];
    unsigned int loopcounter;
    uint8_t index;
    uint8_t cnt;
public:
    
    /// @brief
    /// DHT11 constructor
    /// @details
    /// @param pin          Gets pin and initializes it.
    /// @param error        Error codes get stored in this parameter.
    /// @param now          Time of that moment gets set in this parameter.
    /// @param time         Time of that moment - nu gets set in this parameter.
    /// @param data[5]      Parameter where the 40 bits of data get saved in. 
    /// @param loopcounter  Checks for the amounts of loops.
    /// @param index        Parameter to check where in the array the bits need to be set.
    /// @param cnt          Parameter to check how many bits are already in the array.
    
    DHT11(hwlib::target::pin_in_out & pin, 
    uint8_t error = 0, 
    uint_fast64_t now = 0,
    uint_fast64_t time = 0,  
    uint8_t data[5] = 0, 
    unsigned int loopcounter = TIMEOUT, 
    uint8_t index = 0,
    uint8_t cnt = 0);
    
    /// @brief
    /// This function starts up the sensor and get it ready to send data.
    /// @details
    /// Sets high 'reset' signal for 1200 milliseconds on data line.
    /// Sets low signal for at least 18 ms, 20 ms to be safe on data line.
    /// Check for low then high signal of ~80 microseconds.
    void start_up();
    
    /// @brief
    /// Reads the data send by the DHT11 temperature and humidity sensor.
    /// @details
    /// Sets previous data to 0 so data array is empty.
    /// Loops through all 40 bits that are sent by DHT11 sensor. 
    /// Check for low signal of ~50 microseconds.
    /// Check for 0 or 1 with keeping time in microseconds.
    /// 0 = ~30 microseconds, 1 = ~70 microseconds.
    /// Set 0 or 1 in data.
    void read_data();
    
    /// @brief
    /// Gets the temperature.
    /// @details
    /// Calls start_up fuction.
    /// Call read_data function.
    /// Calculate temperature if data[3] = 128
    /// Returns temperature.
    float get_temperature();
    
    /// @brief
    /// Gets the humidity.
    /// @details
    /// Calls start_up fuction.
    /// Call read_data function.
    /// Returns humidity.
    float get_humidity();
    
    /// @brief
    /// Gets error code.
    /// @details
    /// If previous functions gave error code it return those.
    /// Check if checksum is correct.
    /// Return error code.
    float get_errors();
};

#endif // DHT11_HPP