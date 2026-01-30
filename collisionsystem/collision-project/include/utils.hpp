#ifndef UTILS_H
#define UTILS_H

#include <random>

namespace utils {

    /**
     * @brief Generates a random integer within a specified inclusive range.
     *
     * This function returns a uniformly distributed integer between
     * @p min and @p max, including both endpoints. The behavior is
     * undefined if @p min is greater than @p max.
     *
     * @param min The lower bound of the range (inclusive).
     * @param max The upper bound of the range (inclusive).
     * @return A random integer in the range [min, max].
     */
    int random_in_range(int min, int max);

}


#endif // !UTILS_H