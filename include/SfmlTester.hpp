#ifndef SFML_TESTER_HPP
#define SFML_TESTER_HPP

#include <SFML/Graphics.hpp>
#include <ResourceLoading.hpp>
#include "Tester.hpp"

class ResourceStorage;

/**
 * @brief Class for testing functionality of the SFML library.
 * 
 * This class provides a simple interface to test SFML features & make sure the library builds correctly.
 * 
 */
class SfmlTester : public Tester {
public:
    /**
     * @brief Constructor for SfmlTester.
     *
     * Initializes the SfmlTester object.
     */
    SfmlTester();

    /**
     * @brief Run a test.
     *
     * This function runs a test and returns the result.
     *
     * @return The result of the test. 0 if successful, otherwise -1.
     */
    std::pair<int, int> runTest();
};

#endif // SFML_TESTER_HPP