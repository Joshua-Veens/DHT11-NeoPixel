#ifndef NEOPIXEL_HPP
#define NEOPIXEL_HPP
#include <stdint.h>
#include "hwlib.hpp"

///@file

/// \brief
/// NeoPixel by Joshua Veens
/// \details
/// A simple library for a neopixel ring or led strip

class neopixel {
private:
    hwlib::target::pin_out & neo_pin;
    unsigned int & num_leds;
    uint32_t colour;
    uint32_t tmp;
public:

    /// @brief
    /// Neopixel constructor
    /// @details
    /// @param neo_pin      Gets pin and initializes it.
    /// @param num_leds     The number of leds on the strip or ring.
    /// @param colour       The colour of the leds in hex (24 bit).
    /// @param tmp          Temp variable used for temporary storing colour.

    neopixel(
    hwlib::target::pin_out & neo_pin, 
    unsigned int & num_leds,
    uint32_t colour = 0,
    uint32_t tmp = 0);
    
    /// @brief
    /// Sends a 1 bit to the led strip or ring.
    /// @details
    /// Writes double 1 then double 0 for correct timings.
    void send_one();
    
    /// @brief
    /// Sends a 0 bit to the led strip or ring.
    /// @details
    /// Writes 1 and then double 0 for correct timings.
    void send_zero();
    
    /// @brief
    /// Reset for inbetween frames.
    /// @details
    /// Writes 0 and waits for ~10 ms.
    void reset();
    
    /// @brief
    /// Turns on the amount of leds with the right colour.
    /// @details
    /// Runs reset in case there was a previous frame.
    /// For every led it writes the right hex number to the led strip or ring.
    void show(unsigned int num_leds, uint32_t colour);
};

#endif // NEOPIXEL_HPP
