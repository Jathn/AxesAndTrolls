#include "BattleWindow.hpp"

std::vector<std::pair<int, int>> dice_positions = {
    {200, 100},
    {200, 250},
    {200, 400},
    {200, 550},
    {600, 100},
    {600, 250},
    {600, 400},
    {600, 550}
};

std::vector<UnitType> unittypes = {UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON};

std::map<UnitType, int> unit_ys = {
    {UnitType::INFANTRY, 200},
    {UnitType::ARTILLERY, 350},
    {UnitType::RIDER, 500},
    {UnitType::DRAGON, 650}
};

BattleWindow::BattleWindow(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::vector<std::shared_ptr<Unit>> a_units, std::vector<std::shared_ptr<Unit>> d_units, std::pair<int, int> position) {
    player1_ = player1;
    player2_ = player2;
    battle_simulator_ = std::make_unique<BattleSimulator>(a_units, d_units);
    background_ = sf::RectangleShape(sf::Vector2f(1080, 900));
    background_.setFillColor(sf::Color::White);
    background_.setOutlineColor(sf::Color::Red);
    background_.setOutlineThickness(5);
    background_.setPosition(position.first, position.second);

    for (int i = 0; i < dice_positions.size(); i++) {
        dices_.push_back(DiceView(std::make_pair(100, 100), std::make_pair(position.first + dice_positions[i].first, position.second + dice_positions[i].second)));
    }

    for (auto type : unittypes) {
        unit_views_[player1].push_back(std::make_unique<UnitView>(type));
    }

    for (auto type: unittypes) {
        unit_views_[player2].push_back(std::make_unique<UnitView>(type));
    }

    roll_button_ = std::make_unique<Button>("Roll", std::make_pair(100, 100), std::make_pair(position.first + 900, position.second + 580));
}

std::shared_ptr<Player> BattleWindow::getWinner() {
    int attackers_left = battle_simulator_->getStatus().first;
    int defenders_left = battle_simulator_->getStatus().second;

    if (defenders_left == 0 && attackers_left > 0) {
        return player1_.lock();
    }

    return player2_.lock();
}
void BattleWindow::rollDice() {
    battle_simulator_->rollAllDie();
    std::map<UnitType, int> hits_p1 = battle_simulator_->getDicesRolled(player1_.lock());
    std::map<UnitType, int> hits_p2 = battle_simulator_->getDicesRolled(player2_.lock());
    for (int i = 0; i < hits_p1.size(); i++) {
        dices_[i].setNumber(hits_p1[unittypes[i]]);
    }

    for (int i = 0; i < hits_p2.size(); i++) {
        dices_[i + 4].setNumber(hits_p2[unittypes[i]]);
    }
}

void BattleWindow::handleAttackerAssigns(sf::Event& event, sf::RenderWindow& window) {
    // Handle attacker assigns here
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (100 <= localPosition.x <= 200) {
            if (200 <= localPosition.y <= 300) {
                battle_simulator_->takeHitAttacker(UnitType::INFANTRY);
            } else if (350 <= localPosition.y <= 450) {
                battle_simulator_->takeHitAttacker(UnitType::ARTILLERY);
            } else if (500 <= localPosition.y <= 600) {
                battle_simulator_->takeHitAttacker(UnitType::RIDER);
            } else if (650 <= localPosition.y <= 750) {
                battle_simulator_->takeHitAttacker(UnitType::DRAGON);
            }
        }
    }
}

void BattleWindow::handleDefenderAssigns(sf::Event& event, sf::RenderWindow& window) {
    // Handle defender assigns here
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (800 <= localPosition.x <= 900) {
            if (200 <= localPosition.y <= 300) {
                battle_simulator_->takeHitDefender(UnitType::INFANTRY);
            } else if (350 <= localPosition.y <= 450) {
                battle_simulator_->takeHitDefender(UnitType::ARTILLERY);
            } else if (500 <= localPosition.y <= 600) {
                battle_simulator_->takeHitDefender(UnitType::RIDER);
            } else if (650 <= localPosition.y <= 750) {
                battle_simulator_->takeHitDefender(UnitType::DRAGON);
            }
        }
    }
}

void BattleWindow::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (battle_simulator_->getHitMap().first != 0 && !isOver()) {
        handleAttackerAssigns(event, window);
    } else if (battle_simulator_->getHitMap().second != 0 && !isOver()) {
        handleDefenderAssigns(event, window);
    } else {
        if (roll_button_->isInside(event.mouseButton.x, event.mouseButton.y) && !isOver()) {
            rollDice();
        }
    }
}

void BattleWindow::draw(sf::RenderWindow& window) {
    // Drawing logic here
    window.draw(background_);
    roll_button_->draw(window);
    for (auto& dice : dices_) {
        dice.draw(window);
    }

    for (auto& unit : unit_views_[player1_.lock()]) {
        int count = battle_simulator_->getAttackersCount(unit->getType());
        unit->draw(window, std::make_pair(100, unit_ys[unit->getType()]), 100, count);
    }

    for (auto& unit : unit_views_[player2_.lock()]) {
        int count = battle_simulator_->getDefendersCount(unit->getType());
        unit->draw(window, std::make_pair(800, unit_ys[unit->getType()]), 100, count);
    }

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        throw std::runtime_error("Font not found");
    }

    std::pair<int, int> hit_map = battle_simulator_->getHitMap();

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    std::string hitCounts = "Attacker Hits: ";
    hitCounts += std::to_string(hit_map.first) + "\t";

    hitCounts += "Defender Hits: ";
    hitCounts += std::to_string(hit_map.second);

    text.setString(hitCounts);
    text.setPosition(300, 900);
    window.draw(text);
}

bool BattleWindow::isOver() {
    return battle_simulator_->isBattleOver();
}