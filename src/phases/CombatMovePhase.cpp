#include "CombatMovePhase.hpp"
#include "CombatPhase.hpp"

CombatMovePhase::CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Move Phase") { }

void CombatMovePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}

void CombatMovePhase::draw(sf::RenderWindow& window) {

}

std::shared_ptr<Phase> CombatMovePhase::getNextPhase() {
    return std::make_shared<CombatPhase>(state_manager_.lock(), graphics_manager_.lock());
}