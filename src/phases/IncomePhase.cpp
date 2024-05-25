#include "IncomePhase.hpp"
#include "BuyPhase.hpp"

IncomePhase::IncomePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Income Phase") { }

void IncomePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        setDone();
    }
}

void IncomePhase::draw(sf::RenderWindow& window) {

}

std::shared_ptr<Phase> IncomePhase::getNextPhase() {
    state_manager_.lock()->nextPlayer();
    return std::make_shared<BuyPhase>(state_manager_.lock(), graphics_manager_.lock());
}