#ifndef CURRENT_TILE_VIEW_HPP
#define CURRENT_TILE_VIEW_HPP

#include "Tile.hpp"
#include "UnitView.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class CurrentTileView {
public:
    CurrentTileView();
    void draw(sf::RenderWindow& window, const std::string& building, const std::vector<std::weak_ptr<Unit>>& units);
    void handleLeftClick(sf::RenderWindow& window, const sf::Vector2i& position);
    void onMoveButtonClicked();
    void onCancelButtonClicked();
    void onSelectUnitButtonClicked(const int& index); // 0: Infantry, 1: Artillery, 2: Rider, 3: Dragon

    std::vector<std::weak_ptr<Unit>> getSelectedUnits() const;

    bool isMoveButtonClicked(const sf::Vector2i& position) const;
    bool isCancelButtonClicked(const sf::Vector2i& position) const;
    bool isSelectUnitButtonClicked(const sf::Vector2i& position) const;

    bool isMoveActive() const;
private:
    sf::RectangleShape background_;
    sf::Text text_;
    sf::Font font_;
    std::vector<UnitView> unit_views_;
    std::unique_ptr<Button> move_button_;
    std::unique_ptr<Button> cancel_button_;
    std::vector<std::weak_ptr<Unit>> selected_units_;
    std::vector<std::unique_ptr<Button>> select_unit_buttons_;
    bool move_active_;
};

#endif // CURRENT_TILE_VIEW_HPP
