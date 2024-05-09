#include "PlacementPhase.hpp"

PlacementPhase::PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager_) : Phase(state_manager, graphics_manager_) { }

void PlacementPhase::onTileClick(int tile_id) {
    std::cout << "Tile clicked: " << tile_id << std::endl;
}

void PlacementPhase::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
        }
    }

    if (checkLeftClick(event)) {
        
        int tile_id = graphics_manager_.lock()->getTileId(event.mouseButton.x, event.mouseButton.y);
        if (tile_id == -1) {
            std::cout << "Something else clicked" << std::endl;
        } else {
            onTileClick(tile_id);
        }
    }
}