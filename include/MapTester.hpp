#ifndef MAP_TESTER_HPP
#define MAP_TESTER_HPP

#include <string>

#include "GameStateManager.hpp"
#include "Tester.hpp"
#include "Movement.hpp"

/**
 * @brief Class for testing functionality of the Map.
 * 
 * This class provides a simple interface to test Map features & make sure everything works correctly.
 * 
 */
class MapTester : public Tester {
public:
    /**
     * @brief Constructor for MapTester.
     *
     * Initializes the MapTester object.
     */
    MapTester();

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

#endif // MAP_TESTER_HPP