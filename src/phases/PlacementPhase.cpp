#include "PlacementPhase.hpp"

PlacementPhase::PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager) : Phase(state_manager) { }

void PlacementPhase::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
        }
    }
}