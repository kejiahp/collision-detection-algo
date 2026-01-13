#include "custom_color.hpp"
#include "utils.hpp"


namespace customcolor{
    std::string Color::toString() const{
        std::ostringstream ss;
        ss << "Color{" << static_cast<int>(r) << ',' << static_cast<int>(g) << ',' << static_cast<int>(b) << '}';
        return ss.str();
    }

    Color random_rgb() {
        return Color{ static_cast<uint8_t>(utils::random_in_range(0, 255)),
                      static_cast<uint8_t>(utils::random_in_range(0, 255)),
                      static_cast<uint8_t>(utils::random_in_range(0, 255)) };
    }
}