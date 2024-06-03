#include "GameInfo.hpp"

GameInfo::GameInfo(std::pair<int, int> position, int size) 
 : position_(position), font_size_(size) { 
    if (!font_.loadFromFile("../resources/fonts/ttf/crimson-bold.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    text_.setFont(font_);
    text_.setCharacterSize(font_size_);
    text_.setFillColor(sf::Color::Black);
    text_.setPosition(10, 10);
}

void GameInfo::draw(sf::RenderWindow& window, int round, std::shared_ptr<Player> player, std::shared_ptr<Phase> phase) {
    text_.setString("Player: " + player->getName() + "\tRound: " + std::to_string(round) + "\tPhase: " + phase->getName());
    window.draw(text_);
}