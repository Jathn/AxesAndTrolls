#include "CombatPhase.hpp"
#include "FriendlyMovePhase.hpp"

CombatPhase::CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Phase") {
        updateContestedTiles();
    }

void CombatPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}


void CombatPhase::updateContestedTiles() {
    // Update contested tiles here
    std::vector<std::shared_ptr<Tile>> contested_tiles = state_manager_.lock()->getContestedTiles();
    for (auto tile : state_manager_.lock()->getMap()) {
        bool is_contested = std::find(contested_tiles.begin(), contested_tiles.end(), tile) != contested_tiles.end();
        tile->setActive(is_contested);
    }
}

void CombatPhase::draw(sf::RenderWindow& window) {
    updateContestedTiles();
}

std::shared_ptr<Phase> CombatPhase::getNextPhase() {
    return std::make_shared<FriendlyMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}