#include "GameInitializer.hpp"

GameInitializer::GameInitializer() { 
    num_players_ = 0;
    current_name_ = "";
};

std::vector<std::string> GameInitializer::getPlayerNames() {
    return player_names_;
}

void GameInitializer::setDone(bool is_done) {
    is_done_ = is_done;
}

bool GameInitializer::isDone() {
    return is_done_;
}

void GameInitializer::toggleDone() {
    setDone(true);
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
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Black);
    text.setPosition(window_size_x / 4, window_size_y / 2 - 30);
    window.draw(text);
    for (int i = 0; i < player_names_.size(); i++) {
        sf::Text player_text;
        player_text.setFont(font);
        player_text.setString(std::to_string(i + 1) + ": " + player_names_[i]);
        player_text.setCharacterSize(35);
        player_text.setFillColor(sf::Color::Black);
        player_text.setPosition(window_size_x / 4, window_size_y / 2 + i * 30);
        window.draw(player_text);
    }
}

void GameInitializer::handleEvent(sf::Event& event, const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) {
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
                if (player_names_.size() == num_players_) {
                    state_manager->createPlayers(num_players_);
                    int i = 0;
                    for (auto player : state_manager->getPlayers()) {
                        player->setName(player_names_[i]);
                        i++;
                    }
                    graphics_manager->update(state_manager);
                    toggleDone();
                    state_manager->setCurrentPlayer(state_manager->getPlayers()[0]);
                }
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