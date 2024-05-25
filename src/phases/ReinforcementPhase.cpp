#include "ReinforcementPhase.hpp"
#include "IncomePhase.hpp"

ReinforcementPhase::ReinforcementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Reinforcement Phase") { }

void ReinforcementPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        std::cout << "Clickity click" << std::endl;
    }
}

void ReinforcementPhase::draw(sf::RenderWindow& window) {

}

std::shared_ptr<Phase> ReinforcementPhase::getNextPhase() {
    return std::make_shared<IncomePhase>(state_manager_.lock(), graphics_manager_.lock());
}