#ifndef TESTER_HPP
#define TESTER_HPP

#include <string>
#include <iostream>
/**
 * @brief Parent class for testing functionality.
 * 
 * This class provides a common interface for testing functionality.
 * 
 */
class Tester {
public:
    /**
     * @brief Constructor for Tester.
     *
     * Initializes the Tester object.
     */
    Tester();

    /**
     * @brief Run a test.
     *
     * This function runs a test and returns the result.
     *
     * @return The result of the test. 0 if successful, otherwise -1.
     */
    virtual std::pair<int, int> runTest() = 0;

    /**
     * @brief Update statistics for a completed test.
     * 
     */
    void addCompleted(const std::string& str);

    /**
     * @brief Update statistics for an unsuccessful test.
     * 
     */
    void addUnsuccessful(const std::string& str);

protected:
    std::pair<int, int> test_results_;
};

#endif // TESTER_HPP
