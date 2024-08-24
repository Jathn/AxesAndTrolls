#include "ReinforcementPhase.hpp"
#include "IncomePhase.hpp"

ReinforcementPhase::ReinforcementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Reinforcement Phase") {
        current_player_ = state_manager->getCurrentPlayer();
        std::vector<std::shared_ptr<Unit>> unplaced_units = current_player_.lock()->getUnplacedUnits();
        std::vector<std::shared_ptr<Building>> unplaced_buildings = current_player_.lock()->getUnplacedBuildings();

        for (auto unit : unplaced_units) {
            unplaced_units_.push_back(unit);
        }

        for (auto building : unplaced_buildings) {
            unplaced_buildings_.push_back(building);
        }

        sell_button_ = std::make_unique<Button>("Sell", std::pair<int, int>(150, 50), std::pair<int,int>(1000, 950));
    }

void ReinforcementPhase::unitPlacement(sf::Event& event, sf::RenderWindow& window) {
    if (checkLeftClick(event)) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        int tile_id = graphics_manager_.lock()->getTileId(localPosition.x, localPosition.y);
        if (tile_id == -1) {
            std::cout << "Something else clicked" << std::endl;
        } else {
            try {
                current_player_.lock()->placeUnit(unplaced_units_[0].lock(), state_manager_.lock()->getMap().at(tile_id));
                unplaced_units_.erase(unplaced_units_.begin());
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (sell_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
            current_player_.lock()->sellUnit(unplaced_units_[0].lock());
            unplaced_units_.erase(unplaced_units_.begin());
        }
    }
}

void ReinforcementPhase::buildingPlacement(sf::Event& event, sf::RenderWindow& window) {
    if (checkLeftClick(event)) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        int tile_id = graphics_manager_.lock()->getTileId(localPosition.x, localPosition.y);
        if (tile_id == -1) {
            std::cout << "Something else clicked" << std::endl;
        } else {
            try {
                current_player_.lock()->placeBuilding(unplaced_buildings_[0].lock(), state_manager_.lock()->getMap().at(tile_id));
                unplaced_buildings_.erase(unplaced_buildings_.begin());
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (sell_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
            current_player_.lock()->sellBuilding(unplaced_buildings_[0].lock());
            unplaced_buildings_.erase(unplaced_buildings_.begin());
        }
    }
}

void ReinforcementPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (!allUnitsPlaced()) {
        unitPlacement(event, window);
    } else if (!allBuildingsPlaced()) {
        buildingPlacement(event, window);
    } else {
        std::shared_ptr<Player> current_player = state_manager_.lock()->getCurrentPlayer();
        for(auto unit : current_player->getUnits()) {
            unit->setMovementLeft(unit->getMovement());
        }
        current_player->updateGeneration();
        setDone();
    }
}

void ReinforcementPhase::drawUnplacedUnits(sf::RenderWindow& window) {
    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(700, 950);
    if (unplaced_units_.size() > 0) {
        std::string unit_name = "Infantry";
        switch (unplaced_units_[0].lock()->getTypeChar()) {
            case 'A':
                unit_name = "Artillery";
                break;
            case 'R':
                unit_name = "Rider";
                break;
            case 'D':
                unit_name = "Dragon";
                break;
        }

        text.setString("Place " + unit_name);
    }

    window.draw(text);
}

void ReinforcementPhase::drawUnplacedBuildings(sf::RenderWindow& window) {
    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(700, 950);
    if (unplaced_buildings_.size() > 0) {
        std::string building_name = "City";
        switch (unplaced_buildings_[0].lock()->getTypeChar()) {
            case 'F':
                building_name = "Farm";
                break;
            case 'M':
                building_name = "Mine";
                break;
            case 'L':
                building_name = "Lodge";
                break;
        }

        text.setString("Place " + building_name);
    }

    window.draw(text);
}

void ReinforcementPhase::draw(sf::RenderWindow& window) {
    graphics_manager_.lock()->draw(window);
    if (!allUnitsPlaced()) {
        drawUnplacedUnits(window);
    } else if (!allBuildingsPlaced()) {
        drawUnplacedBuildings(window);
    } 
    sell_button_->draw(window);
}

std::shared_ptr<Phase> ReinforcementPhase::getNextPhase() {
    return std::make_shared<IncomePhase>(state_manager_.lock(), graphics_manager_.lock());
}

bool ReinforcementPhase::allUnitsPlaced() const {
    return unplaced_units_.size() == 0;
}

bool ReinforcementPhase::allBuildingsPlaced() const {
    return unplaced_buildings_.size() == 0;
}