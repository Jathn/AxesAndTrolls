#ifndef TURN_TESTER_HPP
#define TURN_TESTER_HPP

#include "Tester.hpp"
#include "GameStateManager.hpp"
#include "Player.hpp"
/**
 * @brief Class for simulating a played turn
 *        Note: created before turn system implementation, so doesn't use such functionality
 * 
 */
class TurnTester : public Tester {
    public:
        TurnTester();

    std::pair<int, int> runTest();

    void printMap(std::pair<int, int> ms, GameStateManager gsm);
};

#endif // TURN_TESTER_HPP