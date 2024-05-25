#include "Phase.hpp"


Phase::Phase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager, const std::string& name) 
: state_manager_(state_manager), graphics_manager_(graphics_manager), is_done_(false), name_(name) { }

bool Phase::checkLeftClick(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            return true;
        }
    }

    return false;
}

bool Phase::isDone() const {
    return is_done_;
}

void Phase::setDone() {
    is_done_ = true;
}

