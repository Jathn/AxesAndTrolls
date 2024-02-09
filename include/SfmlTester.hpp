#ifndef SFML_TESTER_HPP
#define SFML_TESTER_HPP

#include <SFML/Graphics.hpp>
#include <ResourceLoading.hpp>
#include "Tester.hpp"

class ResourceStorage;

/**
 * @file SfmlTester.hpp
 * @author Jonathan Ramstedt
 * @brief File containing SfmlTester class, which is used to test the sfml functionality.
 * 
 * @version 0.1
 * @date 2024-01-10
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