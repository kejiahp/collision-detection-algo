#include "utils.hpp"

namespace utils {
	int random_in_range(int min, int max) {
		// Ensures efficient and independent random streams if used in multithreaded code.
		static thread_local std::mt19937 rng(std::random_device{}());
		// // Create random engine that guarantees values between min and max, including both ends.
		std::uniform_int_distribution<int> dist(min, max);
		return dist(rng);
	}
}