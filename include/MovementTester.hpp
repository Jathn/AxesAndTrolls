#ifndef MOVEMENT_TESTER_HPP
#define MOVEMENT_TESTER_HPP

#include "Tester.hpp"
#include "Tile.hpp"

/**
 * @file MovementTester.hpp
 * @author Jonathan Ramstedt
 * @brief MovementTester.hpp contains the class responsible for testing map movement. (Algorithms etc.)
 * 
 * @version 0.1
 * @date 2024-02-06
 */
class MovementTester : public Tester {
public:
    /**
     * @brief Construct a new Movement Tester object
     * 
     * Initializes the MovementTester object.
     */
    MovementTester();

    /**
     * @brief Run a test.
     *
     * Test all possible movement types and events that need testing.
     *
     * @return The result of the test. 0 if successful, otherwise -1.
     */
    std::pair<int, int> runTest();
};

#endif // MOVEMENT_TESTER_HPP