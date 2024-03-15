#ifndef PLAYER_TESTER_HPP
#define PLAYER_TESTER_HPP

#include <memory>
#include <iostream>
#include <vector>
#include <string>

#include "Tester.hpp"

class PlayerTester : public Tester {
public:
    PlayerTester();
    std::pair<int, int> runTest() override;
};

#endif // PLAYER_TESTER_HPP