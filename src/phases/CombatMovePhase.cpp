#include "CombatMovePhase.hpp"
#include "CombatPhase.hpp"

CombatMovePhase::CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Move Phase") {
        current_tile_view_ = CurrentTileView();
        next_button_ = std::make_shared<Button>("Combat!", std::pair<int, int>(150, 50), std::pair<int,int>(1200, 950));
}

void CombatMovePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        handleLeftClick(window, localPosition);
    }
}

void CombatMovePhase::handleLeftClick(sf::RenderWindow& window, const sf::Vector2i& position) {
    if (next_button_->isInside(position.x, position.y)) {
            // Handle the confirm button
            setDone();
    }
    current_tile_view_.handleLeftClick(window, position, state_manager_.lock());
    int tile_id = graphics_manager_.lock()->getTileId(position.x, position.y);
    if (tile_id == -1) {
        std::cout << "Something else clicked" << std::endl;
    } else {
        if (current_tile_view_.isMoveActive()) {
            std::vector<std::shared_ptr<Unit>> units_to_move = current_tile_view_.getSelectedUnits();
            try {
                state_manager_.lock()->getCurrentPlayer()->getMovementHandler()->moveUnits(units_to_move, state_manager_.lock()->getMap().at(tile_id));
                current_tile_view_.setMoveActive(false);

                for (auto player : state_manager_.lock()->getPlayers()) {
                    for (auto tile : player->getTiles()) {
                        if (tile->getOwner().lock() != player) {
                            player->getTerritory()->removeTile(tile);
                        }
                    }
                }
                
                for (auto tile : state_manager_.lock()->getMap()) {
                    tile->setActive(false);
                }
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            
        } else {
            state_manager_.lock()->setCurrentTile(tile_id);
            current_tile_view_.wipeSelectedUnits();
        }

    }
}

void CombatMovePhase::draw(sf::RenderWindow& window) {

    if (state_manager_.lock()->getCurrentTile() == nullptr) {
        return;
    }
    std::vector<std::weak_ptr<Unit>> tile_units = state_manager_.lock()->getCurrentTile()->getUnits();
    std::vector<std::shared_ptr<Unit>> player_units = state_manager_.lock()->getCurrentPlayer()->getUnits();
    std::vector<std::weak_ptr<Unit>> units;
    
    for (auto unit : tile_units) {
        if (player_units.end() != std::find(player_units.begin(), player_units.end(), unit.lock())) {
            units.push_back(unit);
        }
    }

    if (current_tile_view_.isMoveActive()) {
        std::shared_ptr<MovementHandler> movement_handler = state_manager_.lock()->getCurrentPlayer()->getMovementHandler();
        std::vector<std::shared_ptr<Tile>> available_tiles = movement_handler->getAvailableTiles(current_tile_view_.getSelectedUnits());
        std::vector<int> available_tile_ids;
        
        for (const auto& tile : available_tiles) {
            available_tile_ids.push_back(tile->getId());
        }

        for (auto i : available_tile_ids) {
            std::shared_ptr<Tile> tile = state_manager_.lock()->getMap().at(i);
            tile->setActive(true);
        }
    } else {
        for (auto tile : state_manager_.lock()->getMap()) {
            tile->setActive(false);
        }
    }
    
    std::string building_name = "No building";
    if (state_manager_.lock()->getCurrentTile()->getBuilding() != nullptr) {
        building_name = state_manager_.lock()->getCurrentTile()->getBuilding()->getName();
    }
    current_tile_view_.draw(window, building_name, units);
    next_button_->draw(window);
}

std::shared_ptr<Phase> CombatMovePhase::getNextPhase() {
    return std::make_shared<CombatPhase>(state_manager_.lock(), graphics_manager_.lock());
}