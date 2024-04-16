#include "PlayerView.hpp"

PlayerView::PlayerView(std::shared_ptr<Player> player, std::pair<int, int> position, std::pair<int, int> size) : player_(player), position_(position), size_(size) {
    font_.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
    text_.setFont(font_);
    initializeIcons(3 * size_.second / 4);
}

void PlayerView::draw(sf::RenderWindow& window) {
    /* Draws a hud displaying resources, production and count for buildings, units and tiles under its control */
    drawBackground(window);
    /* Player nr drawing as "title" */
    text_.setCharacterSize(size_.first / 10);
    text_.setString("Player X");
    text_.setPosition(position_.first + size_.first / 2 - text_.getGlobalBounds().getSize().x / 2, position_.second + size_.second / 10);
    window.draw(text_);
    drawCounts(window);
}

void PlayerView::drawBackground(sf::RenderWindow& window) {

    /* Draws the background of the hud */
    
    /* Darker grey outline, lighter grey overall */
    sf::RectangleShape background(sf::Vector2f(size_.first, size_.second));
    background.setFillColor(sf::Color(200, 200, 200));
    background.setOutlineColor(sf::Color(150, 150, 150));
    background.setOutlineThickness(2);
    background.setPosition(position_.first, position_.second);
    window.draw(background);
}

void PlayerView::drawCounts(sf::RenderWindow& window) {
    /* Draws the counts for the resources */

    /* Could be refactored A LOT */
    int font_size = size_.first / 10;
    int spacing = size_.first / 25;
    int y_offset = 3 * size_.second / 4;

    text_.setFillColor(sf::Color::Black);
    text_.setCharacterSize(font_size);

    /* Wood count */
    text_.setString(std::to_string(player_.lock()->getResource(ResourceType::WOOD)));
    text_.setPosition(wood_.getPosition().x + wood_.getSize().x + spacing, wood_.getPosition().y);
    window.draw(text_);


    /* Gold count */
    text_.setString(std::to_string(player_.lock()->getResource(ResourceType::GOLD)));
    text_.setPosition(gold_.getPosition().x + gold_.getRadius() * 2 + spacing, gold_.getPosition().y);
    window.draw(text_);
    
    /* Food count */
    text_.setString(std::to_string(player_.lock()->getResource(ResourceType::FOOD)));
    text_.setPosition(food_.getPosition().x + food_.getRadius() * 2 + spacing, food_.getPosition().y);
    window.draw(text_);

    window.draw(wood_);
    window.draw(gold_);
    window.draw(food_);
    drawTerritoryCount(window);
}

void PlayerView::initializeIcons(const int& y_offset) {

    int space_between_icons = size_.first / 4;
    int icon_size_measure = size_.first / 20;
    /* Draws the icons for the resources */
    sf::RectangleShape wood(sf::Vector2f(icon_size_measure * 2, icon_size_measure * 2));
    wood.setFillColor(sf::Color(139, 69, 19));
    wood.setOutlineColor(sf::Color(0, 0, 0));
    wood.setOutlineThickness(2);
    wood.setPosition(position_.first + space_between_icons / 20, position_.second + y_offset);
    wood_ = wood;

    sf::CircleShape gold(icon_size_measure);
    gold.setFillColor(sf::Color(255, 215, 0));
    gold.setOutlineColor(sf::Color(0, 0, 0));
    gold.setOutlineThickness(2);
    gold.setPosition(wood_.getPosition().x + space_between_icons + 2 * icon_size_measure, position_.second + y_offset);
    gold_ = gold;

    sf::CircleShape food(icon_size_measure);
    food.setFillColor(sf::Color(200, 150, 5));
    food.setOutlineColor(sf::Color(0, 0, 0));
    food.setOutlineThickness(2);
    food.setPosition(gold_.getPosition().x + space_between_icons + 2 * icon_size_measure, position_.second + y_offset);

    food_ = food;

}

void PlayerView::drawTerritoryCount(sf::RenderWindow& window) {
    /* Draws the count of tiles under the player's control */
    text_.setCharacterSize(size_.first / 15);
    int tile_count = (int) player_.lock()->getTiles().size();
    int unit_count = (int) player_.lock()->getUnits().size();
    text_.setString("Territory: " + std::to_string(tile_count));
    text_.setPosition(position_.first + size_.first / 2 - text_.getGlobalBounds().getSize().x / 2, position_.second + size_.second / 3);
    window.draw(text_);
    text_.setString("Units: " + std::to_string(unit_count));
    text_.setPosition(position_.first + size_.first / 2 - text_.getGlobalBounds().getSize().x / 2, position_.second + size_.second / 3 + text_.getCharacterSize() * 1.1);
    window.draw(text_);
}