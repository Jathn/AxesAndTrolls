#include "PlacementPhase.hpp"

PlacementPhase::PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager_) 
    : Phase(state_manager, graphics_manager_) { 
        font_.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
        text_.setFont(font_);
        text_.setCharacterSize(35);
        text_.setFillColor(sf::Color::Black);
        text_.setOutlineColor(sf::Color(100, 100, 100, 255));
        text_.setPosition(200, 50);
        std::string confirm_button_text = "Confirm";
        button_ = std::make_shared<Button>(confirm_button_text, std::make_pair(200, 50), std::make_pair(1150, 800));
    }

void PlacementPhase::handleLeftClick(sf::Event& event) {
    int tile_id = graphics_manager_.lock()->getTileId(event.mouseButton.x, event.mouseButton.y);
    if (tile_id == -1) {
        std::cout << "Something else clicked" << std::endl;
    } else {
        onTileClick(tile_id);
    }
}

void PlacementPhase::onTileClick(int tile_id) {
    state_manager_.lock()->setCurrentTile(tile_id);
}

void PlacementPhase::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
        }
    }

    if (checkLeftClick(event)) {
        handleLeftClick(event);
    }
}

void PlacementPhase::draw(sf::RenderWindow& window) {
    text_.setString(state_manager_.lock()->getCurrentPlayer()->getName() + ", place your initial city.");
    window.draw(text_);
    button_->draw(window);
}