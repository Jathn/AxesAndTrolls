#ifndef CURRENT_TILE_VIEW_HPP
#define CURRENT_TILE_VIEW_HPP

#include "Tile.hpp"
#include "UnitView.hpp"
#include "Button.hpp"
#include "GameStateManager.hpp"
#include <SFML/Graphics.hpp>

/**
 * @file CurrentTileView.hpp
 * @brief Class for handling the current tile view of the game.
 * 
 * This class is responsible for handling the current tile view of the game. It allows the player to see the units on the tile and select them for movement.
 * 
 * The class works with CombatMovePhase and FriendlyMovePhase to handle GUI interactions for moving units.
 * CurrentTileView displays information about the tile, but also keeps track of "selected units", which is a key point to note.
 * 
 * @author Jathn
 * @version 1.0
 * @date 2024-08-02
 */
class CurrentTileView {
public:
    CurrentTileView();

    /* Getter Functions */
    std::vector<std::shared_ptr<Unit>> getSelectedUnits() const;

    /* Setter Functions */
    void setMoveActive(bool active);
    
    /**
     * @brief Helper function for "draw" function. Draws the @selected_units_ relevant information.
     * 
     * @param window sf::RenderWindow to draw on.
     * @param position std::pair<int, int> position of the top left corner of the rectangle.
     * @param size int size of the rectangle.
     */
    void drawSelectedCounts(sf::RenderWindow& window, const std::pair<int, int>& position, const std::pair<int, int>& size);

    /**
     * @brief Helper function for "draw" function. Draws the @unit_views_.
     * 
     * @param window sf::RenderWindow to draw on.
     * @param units std::vector<std::weak_ptr<Unit>> units to draw.
     * @param position std::pair<int, int> position of the top left corner of the rectangle.
     * @param size std::pair<int, int> size of the rectangle.
     */
    void drawUnitViews(sf::RenderWindow& window, const std::vector<std::weak_ptr<Unit>>& units, const std::pair<int, int>& position, const std::pair<int, int>& size);

    /**
     * @brief Draws the CurrentTileView on the window.
     * 
     * @param window sf::RenderWindow to draw on.
     * @param building std::string name of the building on the tile. (If any)
     * @param units std::vector<std::weak_ptr<Unit>> units on the tile.
     */
    void draw(sf::RenderWindow& window, const std::string& building, const std::vector<std::weak_ptr<Unit>>& units);

    /**
     * @brief Handles the left click event on the CurrentTileView. Pass through function from top level.
     * 
     * @param window sf::RenderWindow to handle the event on.
     * @param position sf::Vector2i position of the click.
     * @param state_manager std::shared_ptr<GameStateManager> to handle the event.
     */
    void handleLeftClick(sf::RenderWindow& window, const sf::Vector2i& position, const std::shared_ptr<GameStateManager>& state_manager);

    
    /* Button Click Helper functions */
    void onMoveButtonClicked();
    void onCancelButtonClicked();
    void onSelectUnitButtonClicked(const int& index, const std::shared_ptr<GameStateManager>& state_manager); // 0: Infantry, 1: Artillery, 2: Rider, 3: Dragon

    /* Empties selected units */
    void wipeSelectedUnits();
    
    /* Button Click Check functions */
    bool isMoveButtonClicked(const sf::Vector2i& position) const;
    bool isCancelButtonClicked(const sf::Vector2i& position) const;
    int isSelectUnitButtonClicked(const sf::Vector2i& position) const;

    /**
     * @brief Filters the units based on the type.
     * 
     * @param units std::vector<std::weak_ptr<Unit>> units to filter.
     * @param type UnitType type to filter by.
     * @return std::vector<std::shared_ptr<Unit>> filtered units.
     */
    const std::vector<std::shared_ptr<Unit>> filterUnits(const std::vector<std::weak_ptr<Unit>>& units, UnitType type);

    /**
     * @brief Counts the units based on the type. Example: count_units(units)[UnitType::Infantry] returns the count of infantry units.
     * 
     * @param units std::vector<std::weak_ptr<Unit>> units to count.
     * @return std::map<UnitType, int> count of units.
     */
    const std::map<UnitType, int> count_units(const std::vector<std::weak_ptr<Unit>>& units) const;

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
