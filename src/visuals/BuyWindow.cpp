#include "BuyWindow.hpp"

int window_width = 750;
int window_height = 750;
int window_x = 200;
int window_y = 200;
int text_x = 230;
int text_y = 230;
int font_size = 40;
int button_size = 200;
int button_x = 250;
int button_y = 250;
int button_spacing = 280;

std::vector<UnitType> unit_types = {UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON};

BuyWindow::BuyWindow() {
    font_.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf");
    text_.setFont(font_);
    text_.setString("Buy Units");
    text_.setCharacterSize(font_size);
    text_.setFillColor(sf::Color::Black);
    text_.setPosition(text_x, text_y);

    background_.setSize(sf::Vector2f(window_width, window_height));
    background_.setOutlineThickness(5);
    background_.setOutlineColor(sf::Color(150, 150, 150));
    background_.setFillColor(sf::Color::White);
    background_.setPosition(window_x, window_y);

    int column = 0;
    int row = 0;
    for (auto unit_type : unit_types) {
        if (column % 2 == 0 && column != 0) {
            row++;
            column = 0;
        }
        std::shared_ptr<BuyButton> button_ptr = std::make_shared<BuyButton>(std::make_pair(button_size, button_size), 
                                                                            std::make_pair(button_x + button_spacing * column, button_y + button_spacing * row), 
                                                                            unit_type);
        buttons_.push_back(button_ptr);
        column++;
    }

} 

void BuyWindow::draw(sf::RenderWindow& window) {
    window.draw(background_);
    window.draw(text_);
    for (auto button : buttons_) {
        button->draw(window);
    }
}

void BuyWindow::handleEvent(sf::Event& event, sf::RenderWindow& window, const std::shared_ptr<Player>& player) {
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto button : buttons_) {
            if (button->isInside(event.mouseButton.x, event.mouseButton.y)) {
                try {
                    player->buyUnit(button->getUnitType());
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
}
