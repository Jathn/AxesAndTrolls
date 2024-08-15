#include "BattleWindow.hpp"

BattleWindow::BattleWindow(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::vector<std::shared_ptr<Unit>> a_units, std::vector<std::shared_ptr<Unit>> d_units, std::pair<int, int> position) {
    player1_ = player1;
    player2_ = player2;
    battle_simulator_ = std::make_unique<BattleSimulator>(a_units, d_units);
    background_ = sf::RectangleShape(sf::Vector2f(1080, 720));
    background_.setFillColor(sf::Color::White);
    background_.setOutlineColor(sf::Color::Red);
    background_.setOutlineThickness(5);
    background_.setPosition(position.first, position.second);

    roll_button_ = std::make_unique<Button>("Roll", std::make_pair(100, 100), std::make_pair(position.first + 900, position.second + 580));
}

void BattleWindow::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    
}

void BattleWindow::draw(sf::RenderWindow& window) {
    // Drawing logic here
    window.draw(background_);
    roll_button_->draw(window);
}

bool BattleWindow::isOver() {
    return battle_simulator_->isBattleOver();
}