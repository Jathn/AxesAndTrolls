#include "utility/Randoms.hpp"

template<typename T>
T RANDOM::chooseAlternative(const std::map<T, double>& alternatives) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::discrete_distribution<> dist(alternatives.begin(), alternatives.end(),
                                      [](const std::pair<const T, double>& pair) {
                                          return pair.second;
                                      });
    
    return dist(gen)->first;
}

