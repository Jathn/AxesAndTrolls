#ifndef RANDOMS_HPP
#define RANDOMS_HPP

#include <map>
#include <random>

#include "Tile.hpp"

class Map;


/**
 * @file RANDOM.hpp
 * @brief Contains some functions dealing with randomness.
 * 
 * @version 0.1
 * @date 2024-01-15 
 */

/**
 * @brief Function for choosing an alternative based on a probability distribution.
 * 
 * @tparam T 
 * @param alternatives , dictionary of possible values paired with their probability.
 * @return T , the chosen alternative.
 */
template<typename T>
T chooseAlternative(const std::map<T, double>& alternatives) {
    if (!alternatives.empty()) {
        
        /* Total probability calculation */
        double sum = 0;
        for (const auto& pair : alternatives) {
            sum += pair.second;
        }

        /* Create a CRF distribution */
        std::uniform_real_distribution<> dis(0.0, sum);

        /* Generate a random number */
        std::random_device rd;
        std::mt19937 gen(rd());
        double random = dis(gen);

        double current = 0.0;

        /* Checking which Item of type T got randomly picked */
        for (const auto& pair : alternatives) {
            current += pair.second;
            if (random <= current) {
                return pair.first;
            }
        }
    }

    /* Default return value, NULL almost */
    return T();
}

#endif // RANDOMS_HPP