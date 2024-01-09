#ifndef SFML_TESTER_HPP
#define SFML_TESTER_HPP

#include <SFML/Graphics.hpp>
#include <ResourceLoading.hpp>

class ResourceStorage;

/**
 * @brief Class for testing functionality of the SFML library.
 * 
 * This class provides a simple interface to test SFML features & make sure the library builds correctly.
 * 
 */
class SfmlTester {
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

#endif // SFML_TESTER_HPP