#include "BuyWindow.hpp"

int window_width = 750;
int window_height = 400;
int window_x = 200;
int window_y = 200;
int text_x = 230;
int text_y = 230;
int font_size = 40;
int button_size = 100;
int button_x = 250;
int button_y = 250;
int button_spacing = 120;

std::vector<UnitType> unit_types = {UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON};
std::vector<BuildingType> building_types = {BuildingType::CITY, BuildingType::FARM, BuildingType::MINE, BuildingType::LODGE};

BuyWindow::BuyWindow() {
    font_.loadFromFile("../resources/fonts/TTF/Crimson-Bold.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(font_size);
    text_.setFillColor(sf::Color::Black);
    text_.setOutlineColor(sf::Color(100, 100, 100, 255));
    text_.setPosition(text_x, text_y);

    background_.setSize(sf::Vector2f(window_width, window_height));
    background_.setOutlineThickness(5);
    background_.setOutlineColor(sf::Color(150, 150, 150));
    background_.setFillColor(sf::Color::White);
    background_.setPosition(window_x, window_y);

    int column = 0;
    int row = 0;
    buttons_ = std::vector<std::shared_ptr<BuyButton>>();
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

    column = 0;
    row = 0;

    building_buttons_ = std::vector<std::shared_ptr<BuildingBuyButton>>();
    for (auto building_type : building_types) {
        if (column % 2 == 0 && column != 0) {
            row++;
            column = 0;
        }
        std::shared_ptr<BuildingBuyButton> button_ptr = std::make_shared<BuildingBuyButton>(std::make_pair(button_size, button_size), 
                                                                            std::make_pair(button_x + 2 * button_spacing + button_spacing * column, button_y + button_spacing * row), 
                                                                            building_type);
        building_buttons_.push_back(button_ptr);
        column++;
    }

} 

void BuyWindow::draw(sf::RenderWindow& window) {
    window.draw(background_);
    for (auto button : buttons_) {
        button->draw(window);
    }

    for (auto button : building_buttons_) {
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

        for (auto button : building_buttons_) {
            if (button->isInside(event.mouseButton.x, event.mouseButton.y)) {
                try {
                    player->buyBuilding(button->getBuildingType());
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
}
