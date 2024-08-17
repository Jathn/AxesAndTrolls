#include "Menu.hpp"
#include <SFML/Audio.hpp>

Menu::Menu() : game_activated_(false), start_button_(std::make_unique<Button>("Start", std::make_pair(200, 50), std::make_pair(800, 900))) {
}

bool Menu::getGameActivated() const {
    return game_activated_;
}

void Menu::setGameActivated(bool game_activated) {
    game_activated_ = game_activated;
}

void Menu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (start_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
            setGameActivated(true);
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/TTF/Crimson-Bold.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(800, 800);
    text.setString("Axes and Trolls");
    window.draw(text);
    text.setPosition(880, 850);
    text.setCharacterSize(24);
    text.setString("Beta Version 0.1");
    window.draw(text);
    start_button_->draw(window);
}
