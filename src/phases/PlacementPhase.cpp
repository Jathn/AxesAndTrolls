#include "PlacementPhase.hpp"

PlacementPhase::PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager_) 
    : Phase(state_manager, graphics_manager_, "Placement Phase") { 
        font_.loadFromFile("../resources/fonts/TTF/Crimson-Bold.ttf");
        text_.setFont(font_);
        text_.setCharacterSize(35);
        text_.setFillColor(sf::Color::Black);
        text_.setOutlineColor(sf::Color(100, 100, 100, 255));
        text_.setPosition(200, 50);
        std::string confirm_button_text = "Confirm";
        button_ = std::make_shared<Button>(confirm_button_text, std::make_pair(200, 50), std::make_pair(1150, 800));
    }

void PlacementPhase::handleLeftClick(sf::Event& event, sf::Vector2f localPosition) {
    /* Mapping click to position */
    int tile_id = graphics_manager_.lock()->getTileId(localPosition.x, localPosition.y);
    if (tile_id == -1) {
        std::cout << "Something else clicked" << std::endl;
    } else {
        onTileClick(tile_id);
    }

    if (button_->isInside(localPosition.x, localPosition.y)) {
        if (state_manager_.lock()->getCurrentTile() != nullptr) {
                std::shared_ptr<Player> current_player = state_manager_.lock()->getCurrentPlayer();
                std::shared_ptr<Tile> current_tile = state_manager_.lock()->getCurrentTile();

                current_player->addResource(ResourceType::GOLD, 100);
                current_player->addResource(ResourceType::FOOD, 100);
                current_player->buyUnit(UnitType::INFANTRY);
                current_player->buyBuilding(BuildingType::CITY);
                current_player->getTerritory()->addTile(current_tile);
                current_player->placeBuilding(current_player->getUnplacedBuildings().back(), current_tile);
                current_player->placeUnit(current_player->getUnplacedUnits().back(), current_tile);
                state_manager_.lock()->nextPlayer();
                if (state_manager_.lock()->getCurrentPlayer() == state_manager_.lock()->getPlayers().front()) {
                    std::cout << "Placement phase done" << std::endl;
                    setDone();
                }
        } else {
            std::cout << "No tile selected" << std::endl;
        }
        
    }
}

void PlacementPhase::onTileClick(int tile_id) {
    state_manager_.lock()->setCurrentTile(tile_id);
}

void PlacementPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
        }
    }

    if (checkLeftClick(event)) {
        sf::Vector2f globalPosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        handleLeftClick(event, globalPosition);
    }
}

void PlacementPhase::draw(sf::RenderWindow& window) {
    text_.setString(state_manager_.lock()->getCurrentPlayer()->getName() + ", place your initial city.");
    window.draw(text_);
    button_->draw(window);
}

std::shared_ptr<Phase> PlacementPhase::getNextPhase() {
    return std::make_shared<BuyPhase>(state_manager_.lock(), graphics_manager_.lock());
}