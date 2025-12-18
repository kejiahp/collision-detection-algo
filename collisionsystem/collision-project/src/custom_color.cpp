#include "custom_color.hpp"
#include "utils.hpp"


namespace customcolor{
    Color random_rgb() {
        return Color{ static_cast<uint8_t>(utils::random_in_range(0, 255)),
                      static_cast<uint8_t>(utils::random_in_range(0, 255)),
                      static_cast<uint8_t>(utils::random_in_range(0, 255)) };
    }
}