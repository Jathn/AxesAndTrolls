#ifndef MOVEMENT_TESTER_HPP
#define MOVEMENT_TESTER_HPP

#include "GameStateManager.hpp"
#include "Tester.hpp"
#include "Unit.hpp"
#include "Movement.hpp"
#include "MovementHandler.hpp"

class MovementTester : public Tester {
public:
    /**
     * @brief Constructor for MapTester.
     *
     * Initializes the MapTester object.
     */
    MovementTester();

    /**
     * @brief Run a test.
     *
     * This function runs a test and returns the result.
     *
     * @return The result of the test. (total, successful).
     */
    std::pair<int, int> runTest() override;

private:
    GameStateManager game_state_manager_;
};

#endif // MOVEMENT_TESTER_HPP