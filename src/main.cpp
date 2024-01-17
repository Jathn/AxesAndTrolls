#include <iostream>

#include <SFML/Graphics.hpp>
#include <SfmlTester.hpp>
#include <MapTester.hpp>

int main() {
    int runMapTest = 0;
    int runSfmlTest = 0;
    std::cout << "Which tests do you wish to run? 1 to choose a test, other write something else." << std::endl;
    std::cout << "1. Map generation" << std::endl;
    std::cin >> runMapTest;
    std::cout << "2. SFML resource generation" << std::endl;
    std::cin >> runSfmlTest;
    
    if (runMapTest == 1) {
        MapTester map_tester = MapTester();
        if (map_tester.runTest() != 0) {
            std::cerr << "Map test failed." << std::endl;
            return -1;
        };
    } 
    if (runSfmlTest == 1) {
        SfmlTester sfml_tester = SfmlTester();
        if (sfml_tester.runTest() != 0) {
            std::cerr << "SFML test failed." << std::endl;
            return -1;
        };
    }

    return 0;
}