#include "CombatMovePhase.hpp"
#include "CombatPhase.hpp"

CombatMovePhase::CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Move Phase") {
        current_tile_view_ = CurrentTileView();
    }

void CombatMovePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}

void CombatMovePhase::draw(sf::RenderWindow& window) {
    if (state_manager_.lock()->getCurrentTile() == nullptr) {
        return;
    }
    current_tile_view_.draw(window, state_manager_.lock()->getCurrentTile()->getBuilding()->getName(), state_manager_.lock()->getCurrentTile()->getUnits());
}

std::shared_ptr<Phase> CombatMovePhase::getNextPhase() {
    return std::make_shared<CombatPhase>(state_manager_.lock(), graphics_manager_.lock());
}