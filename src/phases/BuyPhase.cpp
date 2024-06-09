#include "BuyPhase.hpp"
#include "CombatMovePhase.hpp"

BuyPhase::BuyPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Buy Phase") {
        std::cout << "Buy Phase Init" << std::endl;
        buy_window_ = BuyWindow();
        confirm_button_ = std::make_shared<Button>("Confirm Purchases", std::pair<int, int>(250, 50), std::pair<int,int>(650, 850));
        std::cout << "Buy Phase Init Done" << std::endl;
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
    std::cout << "Drawing buy_window_" << std::endl;
    buy_window_.draw(window);
    std::cout << "Drawing confirm_button_" << std::endl;
    confirm_button_->draw(window);
    std::cout << "Drawing done" << std::endl;
}

std::shared_ptr<Phase> BuyPhase::getNextPhase() {
    return std::make_shared<CombatMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}