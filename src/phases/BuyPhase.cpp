#include "BuyPhase.hpp"
#include "CombatMovePhase.hpp"

BuyPhase::BuyPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Buy Phase") {
        buy_menu_open_ = false;
        buy_window_ = BuyWindow();
        confirm_button_ = std::make_unique<Button>("Confirm Purchases", std::pair<int, int>(250, 50), std::pair<int,int>(550, 850));
        buy_menu_button_ = std::make_unique<Button>("Buy Menu", std::pair<int, int>(250, 50), std::pair<int,int>(850, 850));
    }

void BuyPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        if (buy_menu_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
            buy_menu_open_ = !buy_menu_open_;
        }

        if (confirm_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
            setDone();
        }
    }
    
    if (buy_menu_open_) {
        buy_window_.handleEvent(event, window, state_manager_.lock()->getCurrentPlayer());
    }
    
}

void BuyPhase::draw(sf::RenderWindow& window) {
    graphics_manager_.lock()->draw(window);
    if (buy_menu_open_) {
        buy_window_.draw(window);
    }
    buy_menu_button_->draw(window);
    confirm_button_->draw(window);
}

std::shared_ptr<Phase> BuyPhase::getNextPhase() {
    return std::make_shared<CombatMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}