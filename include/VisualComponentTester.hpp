#ifndef VISUAL_COMPONENT_TESTER_HPP
#define VISUAL_COMPONENT_TESTER_HPP

#include <SFML/Graphics.hpp>

#include "GameGraphicsManager.hpp"
#include "GameStateManager.hpp"
#include "Tester.hpp"

class VisualComponentTester : public Tester {
public:
    VisualComponentTester();
    std::pair<int, int> runTest();
};

#endif // VISUAL_COMPONENT_TESTER_HPP