#ifndef CUSTOM_COLOR_H
#define CUSTOM_COLOR_H

#include <cstdint>
#include <sstream>

/**
* @namespace customcolor
* 
* @brief Provides utilities for creating a particles color
*/
namespace customcolor {
    /**
    * @struct Color
    *
    * A structure storing the rgb values making up a color
    *
    * struct of unsigned int (0 - 255) that are exactly 8 bits wide
    */
    struct Color { 
        uint8_t r, g, b;
    
        /**
        * Returns the string representation of Color
        */
        std::string toString() const;
    };

    /*Generates a random color
    *
    * @return `Color` color
    */
    Color random_rgb();
};

#endif // CUSTOM_COLOR_H