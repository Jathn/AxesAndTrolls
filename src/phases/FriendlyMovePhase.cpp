#include "FriendlyMovePhase.hpp"
#include "ReinforcementPhase.hpp"

FriendlyMovePhase::FriendlyMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Friendly Move Phase") { }

void FriendlyMovePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}

void FriendlyMovePhase::draw(sf::RenderWindow& window) {

}

std::shared_ptr<Phase> FriendlyMovePhase::getNextPhase() {
    return std::make_shared<ReinforcementPhase>(state_manager_.lock(), graphics_manager_.lock());
}