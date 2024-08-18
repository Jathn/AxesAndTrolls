#include "IncomePhase.hpp"
#include "BuyPhase.hpp"

IncomePhase::IncomePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Income Phase") {
        try {
            goldIncome_ = state_manager_.lock()->getCurrentPlayer()->getResourceGeneration(ResourceType::GOLD);
        } catch (std::exception& e) {
            goldIncome_ = 0;
        }

        try {
            woodIncome_ = state_manager_.lock()->getCurrentPlayer()->getResourceGeneration(ResourceType::WOOD);
        } catch (std::exception& e) {
            woodIncome_ = 0;
        }
        
        try {
            foodIncome_ = state_manager_.lock()->getCurrentPlayer()->getResourceGeneration(ResourceType::FOOD);
        } catch (std::exception& e) {
            foodIncome_ = 0;
        }

        background_color_ = sf::Color(255, 255, 255, 200);
        background_ = sf::RectangleShape(sf::Vector2f(540, 300));
        background_.setFillColor(background_color_);
        background_.setOutlineColor(sf::Color::Black);
        background_.setOutlineThickness(5);
        background_.setPosition(500, 400);
    }

void IncomePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        state_manager_.lock()->getCurrentPlayer()->generateIncome();
        setDone();
    }
}

void IncomePhase::draw(sf::RenderWindow& window) {

    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        std::cout << "Could not load font" << std::endl;
    }
    sf::Text income_text;
    income_text.setFont(font);
    income_text.setCharacterSize(24);
    income_text.setFillColor(sf::Color::Black);
    income_text.setPosition(550, 420);
    income_text.setString("Your income this round:\nGold: " + std::to_string(goldIncome_) + "\nWood: " + std::to_string(woodIncome_) + "\nFood: " + std::to_string(foodIncome_) + "\n\nClick anywhere to continue");

    window.draw(background_);
    window.draw(income_text);
    
}

std::shared_ptr<Phase> IncomePhase::getNextPhase() {
    state_manager_.lock()->checkGameOver();
    state_manager_.lock()->nextPlayer();
    return std::make_shared<BuyPhase>(state_manager_.lock(), graphics_manager_.lock());
}