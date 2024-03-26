#ifndef TESTMAIN_HPP
#define TESTMAIN_HPP

#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include <SfmlTester.hpp>
#include <MapTester.hpp>
#include <MovementTester.hpp>
#include <RunAroundTester.hpp>
#include <TurnTester.hpp>

int testmain() {
     
    /* Tests to run */
    int runMapTest = 0;
    int runSfmlTest = 0;
    int runMovementTest = 0;
    int runRunAroundTest = 0;
    int runTurnTest = 0;

    int tests_total = 0;
    int tests_completed = 0;
    std::cout << "Which tests do you wish to run? 1 to choose a test, other write something else." << std::endl;
    std::cout << "1. Map generation" << std::endl;
    std::cin >> runMapTest;
    std::cout << "2. SFML resource generation" << std::endl;
    std::cin >> runSfmlTest;
    std::cout << "3. Movement" << std::endl;
    std::cin >> runMovementTest;
    std::cout << "4. RunAround" << std::endl;
    std::cin >> runRunAroundTest;
    std::cout << "5. TurnTester" << std::endl;
    std::cin >> runTurnTest;

    if (runMapTest == 1) {
        MapTester map_tester = MapTester();
        std::pair<int, int> map_test_result = map_tester.runTest();
        tests_total += map_test_result.first;
        tests_completed += map_test_result.second;
    } 
    if (runSfmlTest == 1) {
        SfmlTester sfml_tester = SfmlTester();
        std::pair<int, int> sfml_test_result = sfml_tester.runTest();
        tests_total += sfml_test_result.first;
        tests_completed += sfml_test_result.second;
    }
    if (runMovementTest) {
        MovementTester movement_tester = MovementTester();
        std::pair<int, int> movement_test_result = movement_tester.runTest();
        tests_total += movement_test_result.first;
        tests_completed += movement_test_result.second;
    }
    
    if (runRunAroundTest) {
        RunAroundTester run_around_tester = RunAroundTester();
        std::pair<int, int> run_around_test_result = run_around_tester.runTest();
        tests_total += run_around_test_result.first;
        tests_completed += run_around_test_result.second;
    }

    if (runTurnTest) {
        TurnTester turn_tester = TurnTester();
        std::pair<int, int> turn_test_result = turn_tester.runTest();
        tests_total += turn_test_result.first;
        tests_completed += turn_test_result.second;
    }
    
    std::cout << "### Final Result ###" << std::endl;
    std::cout << "Tests passed: " << tests_completed << "/" << tests_total << std::endl;

    if (tests_total == tests_completed) {
        std::cout << "All tests completed successfully!" << std::endl;
        return 0;
    } else {
        std::cout << "Some tests were unsuccessful!" << std::endl;
        return -1;
    }
}

#endif // TESTMAIN_HPP