#include "BuyPhase.hpp"
#include "CombatMovePhase.hpp"

BuyPhase::BuyPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Buy Phase") { }

void BuyPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}

void BuyPhase::draw(sf::RenderWindow& window) {

}

std::shared_ptr<Phase> BuyPhase::getNextPhase() {
    return std::make_shared<CombatMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}