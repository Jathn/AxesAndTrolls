#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include <SfmlTester.hpp>
#include <MapTester.hpp>

int main() {
     
    int runMapTest = 0;
    int runSfmlTest = 0;
    int tests_total = 0;
    int tests_completed = 0;
    std::cout << "Which tests do you wish to run? 1 to choose a test, other write something else." << std::endl;
    std::cout << "1. Map generation" << std::endl;
    std::cin >> runMapTest;
    std::cout << "2. SFML resource generation" << std::endl;
    std::cin >> runSfmlTest;
    
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