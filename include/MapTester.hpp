#ifndef MAP_TESTER_HPP
#define MAP_TESTER_HPP

#include <string>

#include "GameStateManager.hpp"

/**
 * @brief Class for testing functionality of the Map.
 * 
 * This class provides a simple interface to test Map features & make sure everything works correctly.
 * 
 */
class MapTester {
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
     * @return The result of the test. 0 if successful, otherwise -1.
     */
    std::pair<int, int> runTest();

    /**
     * @brief Update statistics for a completed test.
     * 
     */
    void addCompleted(const std::string& str);

    /**
     * @brief Update statistics for a unsuccessful test.
     * 
     */
    void addUnsuccessful(const std::string& str);

private:
    std::pair<int, int> test_results_;
    GameStateManager game_state_manager_;
};

#endif // MAP_TESTER_HPP