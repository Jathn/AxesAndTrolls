#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"

/**
 * @file Menu.hpp
 * @brief Class for handling the menu.
 * 
 * This class is responsible for handling the menu.
 * 
 * @version 1.0
 * @date 2024-08-17
 */
class Menu {
public:
    Menu();

    /* Getter Functions */
    bool getGameActivated() const;

    /* Setter Functions */
    void setGameActivated(bool game_activated);

    
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    
private:
    bool game_activated_;
    std::unique_ptr<Button> start_button_;
};

#endif // MENU_HPP