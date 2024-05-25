#include "CombatPhase.hpp"
#include "FriendlyMovePhase.hpp"

CombatPhase::CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Phase") { }

void CombatPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}

void CombatPhase::draw(sf::RenderWindow& window) {

}

std::shared_ptr<Phase> CombatPhase::getNextPhase() {
    return std::make_shared<FriendlyMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}