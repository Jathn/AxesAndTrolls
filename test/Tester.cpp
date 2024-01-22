#include "Tester.hpp"

Tester::Tester() : test_results_(std::make_pair<int,int>(0,0)) { }

void Tester::addCompleted(const std::string& str) {
    test_results_.first += 1;
    test_results_.second += 1;
    std::cout << "Test completed: " << str << std::endl;
}

void Tester::addUnsuccessful(const std::string& str) {
    test_results_.first += 1;
    std::cout << "Test unsuccessful: " << str << std::endl;
}
