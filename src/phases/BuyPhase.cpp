#include "BuyPhase.hpp"
#include "CombatMovePhase.hpp"

BuyPhase::BuyPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Buy Phase") {
        BuyWindow buy_window_ = BuyWindow();
        confirm_button_ = std::make_shared<Button>("Confirm Purchases", std::pair<int, int>(100, 50), std::pair<int,int>(800, 850));
    }

void BuyPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        if (confirm_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
            // Handle the confirm button
            setDone();
        }
    }

    buy_window_.handleEvent(event, window, state_manager_.lock()->getCurrentPlayer());
    
}

void BuyPhase::draw(sf::RenderWindow& window) {
    // Draw the buy window
    buy_window_.draw(window);
    confirm_button_->draw(window);
}

std::shared_ptr<Phase> BuyPhase::getNextPhase() {
    return std::make_shared<CombatMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}