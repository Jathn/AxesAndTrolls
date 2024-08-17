#ifndef BUILDING_BUY_BUTTON_HPP
#define BUILDING_BUY_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "Button.hpp"
#include "Building.hpp"

/**
 * @file BuildingBuyButton.hpp
 * @brief Class for handling the buy button.
 * 
 * This class is responsible for handling the buy button. Difference to BuyButton: handles buildingtypes.
 * It is a subclass of the Button class.
 * 
 * @version 1.0
 * @date 2024-08-17
 */
class BuildingBuyButton : public Button {
public:
    BuildingBuyButton(const std::pair<int, int>& size, const std::pair<int, int>& position, BuildingType building_type);

    const BuildingType& getBuildingType() const;
private:
    BuildingType building_type_;
};

#endif // BUILDING_BUY_BUTTON_HPP