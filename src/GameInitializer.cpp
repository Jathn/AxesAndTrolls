#include "GameInitializer.hpp"

GameInitializer::GameInitializer() { 
    num_players_ = 0;
    current_name_ = "";
};

std::vector<std::string> GameInitializer::getPlayerNames() {
    return player_names_;
}

bool GameInitializer::isDone() {
    return num_players_ > 0 && player_names_.size() == num_players_;
}

void GameInitializer::draw(sf::RenderWindow& window) {
    int window_size_x = window.getSize().x;
    int window_size_y = window.getSize().y;
    sf::Font font;
    font.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
    sf::Text text;
    text.setFont(font);
    if (num_players_ == 0) {
        text.setString("Enter number of players (1-4), press enter to confirm: " + current_name_);
    } else {
        text.setString("Enter player name, press enter to confirm: " + current_name_);
    }
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(window_size_x / 2.4, window_size_y / 2 - 30);
    window.draw(text);
    for (int i = 0; i < player_names_.size(); i++) {
        sf::Text player_text;
        player_text.setFont(font);
        player_text.setString(std::to_string(i + 1) + ": " + player_names_[i]);
        player_text.setCharacterSize(24);
        player_text.setFillColor(sf::Color::White);
        player_text.setPosition(window_size_x / 2.4, window_size_y / 2 + i * 30);
        window.draw(player_text);
    }
}

void GameInitializer::handleEvent(sf::Event& event) {
    if (num_players_ == 0) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode <= 52 && event.text.unicode >= 49) {
                current_name_ = event.text.unicode;
            } else if (event.text.unicode == 13) {
                num_players_ = std::stoi(current_name_);
                current_name_ = "";
            }
        }
    } else {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 13) {
                player_names_.push_back(current_name_);
                current_name_ = "";
            }
            if (event.text.unicode == 8) {
                if (current_name_.size() > 0) {
                    current_name_.pop_back();
                }
            } else {
                current_name_.push_back(event.text.unicode);
            }
        }
    }
}