#ifndef CUSTOM_COLOR_H
#define CUSTOM_COLOR_H

#include <cstdint>
#include <sstream>

/**
 * @namespace customcolor
 *
 * @brief Utilities for generating and representing particle colors.
 *
 * This namespace provides lightweight color utilities, including a simple
 * RGB color struct and a function for generating random colors suitable
 * for particle visualization.
 */
namespace customcolor {

    /**
     * @struct Color
     * @brief Represents an RGB color using 8‑bit channels.
     *
     * Each channel (red, green, blue) is stored as an unsigned 8‑bit integer
     * in the range 0–255. This struct is intended for simple color handling
     * in particle systems or rendering utilities.
     */
    struct Color {
        uint8_t r; ///< Red channel (0–255)
        uint8_t g; ///< Green channel (0–255)
        uint8_t b; ///< Blue channel (0–255)

        /**
         * @brief Converts the color to a human‑readable string.
         *
         * The returned format is typically `"r,g,b"` or similar,
         * depending on the implementation.
         *
         * @return A string representation of the color.
         */
        std::string toString() const;
    };

    /**
     * @brief Generates a random RGB color.
     *
     * Each channel is assigned a random value in the range 0–255.
     * Useful for assigning varied colors to particles or visual elements.
     *
     * @return A randomly generated Color.
     */
    Color random_rgb();
};


#endif // CUSTOM_COLOR_H