#ifndef VISUAL_COMPONENT_TESTER_HPP
#define VISUAL_COMPONENT_TESTER_HPP

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "PlayerView.hpp"
#include "TileView.hpp"
#include "MovementHandler.hpp"
#include "Unit.hpp"
#include "Tile.hpp"
#include "Territory.hpp"
#include "Tester.hpp"

class VisualComponentTester : public Tester {
public:
    VisualComponentTester();
    std::pair<int, int> runTest();
};

#endif // VISUAL_COMPONENT_TESTER_HPP