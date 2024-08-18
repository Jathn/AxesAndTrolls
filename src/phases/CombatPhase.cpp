#include "CombatPhase.hpp"
#include "ReinforcementPhase.hpp"

CombatPhase::CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Phase") {
        updateContestedTiles();
        finish_button_ = std::make_unique<Button>("Finish", std::pair<int, int>(150, 50), std::pair<int,int>(1000, 950));
        if (state_manager->getContestedTiles().size() == 0) {
            setDone();
        }
    }

std::shared_ptr<Player> CombatPhase::getAttackingPlayer() {
    // Get attacking player here
    return state_manager_.lock()->getCurrentPlayer();
}

std::shared_ptr<Player> CombatPhase::getDefendingPlayer(const std::shared_ptr<Tile>& tile) {
    // Get defending player here
    return tile->getOwner().lock();
}
    
std::vector<std::shared_ptr<Unit>> CombatPhase::getPlayerUnits(const std::shared_ptr<Tile>& tile, const std::shared_ptr<Player>& player) {
    // Get attacking units here
    std::vector<std::shared_ptr<Unit>> units;
    for (auto unit : tile->getUnits()) {
        if (unit.lock()->getOwner() == player) {
            units.push_back(unit.lock());
        }
    }

    return units;
}

void CombatPhase::startCombat(std::shared_ptr<Tile> tile) {
    // Start combat here
    std::shared_ptr<Player> attacking_player = getAttackingPlayer();
    std::shared_ptr<Player> defending_player = getDefendingPlayer(tile);
    std::vector<std::shared_ptr<Unit>> attacking_units = getPlayerUnits(tile, attacking_player);
    std::vector<std::shared_ptr<Unit>> defending_units = getPlayerUnits(tile, defending_player);

    battle_window_ = std::make_unique<BattleWindow>(attacking_player, defending_player, attacking_units, defending_units, std::make_pair(100, 100));
    in_combat_ = true;
}

void CombatPhase::resolveBattle() {
    std::shared_ptr<Player> winner = battle_window_->getWinner();
    
    std::shared_ptr<Player> previous = battle_tile_.lock()->getOwner().lock();

    previous->getTerritory()->removeTile(battle_tile_.lock());
    battle_tile_.lock()->setOwner(winner);
    winner->getTerritory()->addTile(battle_tile_.lock());
    for (auto unit : battle_tile_.lock()->getUnits()) {
        std::shared_ptr<Player> owner = unit.lock()->getOwner();
        if (owner != winner) {
            battle_tile_.lock()->removeUnit(unit.lock());
        }
    }
    in_combat_ = false;
    battle_window_.reset();
    if (state_manager_.lock()->getContestedTiles().size() == 0) {
        setDone();
    }
}

void CombatPhase::inCombatHandleEvent(sf::Event& event, sf::RenderWindow& window) {

    if (battle_window_ == nullptr) {
        throw std::runtime_error("Battle window is not initialized");
    }
    // Handle events during combat here
    if (battle_window_->isOver() && battle_window_ != nullptr) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (finish_button_->isInside(event.mouseButton.x, event.mouseButton.y)) {
                resolveBattle();
            }
        }
    } else {
        battle_window_->handleEvent(event, window);
    }
}

void CombatPhase::outCombatHandleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (checkLeftClick(event)) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        int tile_id = graphics_manager_.lock()->getTileId(localPosition.x, localPosition.y);

        if (tile_id == -1) {
            std::cout << "Something else clicked" << std::endl;
        } else {
            if (isContested(state_manager_.lock()->getMap().at(tile_id))) {
                std::shared_ptr<Tile> tile = state_manager_.lock()->getMap().at(tile_id);
                battle_tile_ = tile;
                try {
                    startCombat(tile);
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            } else {
                std::cout << "Tile is not contested" << std::endl;
            }
        }
        
    }
}

void CombatPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (in_combat_) {
        try {
            inCombatHandleEvent(event, window);
        } catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    } else {
        outCombatHandleEvent(event, window);
    }
}


void CombatPhase::updateContestedTiles() {
    // Update contested tiles here
    std::vector<std::shared_ptr<Tile>> contested_tiles = state_manager_.lock()->getContestedTiles();
    for (auto tile : state_manager_.lock()->getMap()) {
        bool is_contested = std::find(contested_tiles.begin(), contested_tiles.end(), tile) != contested_tiles.end();
        tile->setActive(is_contested);
    }
}

void CombatPhase::draw(sf::RenderWindow& window) {
    updateContestedTiles();

    if (in_combat_ && battle_window_ != nullptr) {
        battle_window_->draw(window);
        if (battle_window_->isOver()) {
            finish_button_->draw(window);
        }
    }
}

std::shared_ptr<Phase> CombatPhase::getNextPhase() {
    return std::make_shared<ReinforcementPhase>(state_manager_.lock(), graphics_manager_.lock());
}

bool CombatPhase::isContested(const std::shared_ptr<Tile>& tile) {
    // Check if tile is contested
    std::vector<std::shared_ptr<Tile>> contested_tiles = state_manager_.lock()->getContestedTiles();

    // One liner -> shorter code -> so much better -> "so much wow" ~Copilot
    return std::find(contested_tiles.begin(), contested_tiles.end(), tile) != contested_tiles.end();
}