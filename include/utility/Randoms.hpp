#ifndef RANDOMS_HPP
#define RANDOMS_HPP

#include <map>
#include <random>

/**
 * @file RANDOM.hpp
 * @brief The RANDOM namespace contains some functions dealing with randomness.
 * 
 * @version 0.1
 * @date 2024-01-15 
 */
namespace RANDOM {

template<typename T>
T chooseAlternative(const std::map<T, double>& alternatives);

} // namespace RANDOM

#endif // RANDOMS_HPP