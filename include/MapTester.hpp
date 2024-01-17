#ifndef Map_TESTER_HPP
#define Map_TESTER_HPP

#include <string>

#include <Tile.hpp>

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
    int runTest();

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
    int tests_total_;
    int tests_completed_;
};

#endif // Map_TESTER_HPP