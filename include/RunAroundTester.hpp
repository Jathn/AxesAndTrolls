#ifndef RUNAROUNDTESTER_HPP
#define RUNAROUNDTESTER_HPP

#include "Tester.hpp"
#include "GameStateManager.hpp"
#include "Tile.hpp"
#include "Unit.hpp"
#include "MovementHandler.hpp"

class RunAroundTester : public Tester {
public:
    RunAroundTester();

    /**
     * @brief Run a test.
     *
     * This function runs a test and returns the result.
     *
     * @return The result of the test. (total, successful).
     */
    std::pair<int, int> runTest() override;

private:
    GameStateManager gameStateManager;
    MovementHandler movementHandler;
    Unit* unit;
};

#endif // RUNAROUNDTESTER_HPP