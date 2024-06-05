#ifndef BUY_WINDOW_HPP
#define BUY_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "BuyButton.hpp"
#include "Player.hpp"

class BuyWindow {
public:
    BuyWindow();
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window, const std::shared_ptr<Player>& player);
private:
    sf::RectangleShape background_;
    sf::Text text_;
    sf::Font font_;
    std::vector<std::shared_ptr<BuyButton>> buttons_;
};

#endif // BUY_WINDOW_HPP