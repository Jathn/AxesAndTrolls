#ifndef BUY_BUTTON_HPP
#define BUY_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "Button.hpp"
#include "Unit.hpp"

/**
 * @file BuyButton.hpp
 * @brief Class for handling the buy button.
 * 
 * This class is responsible for handling the buy button.
 * It is a subclass of the Button class.
 * 
 * @version 1.0
 * @date 2024-05-15
 */
class BuyButton : public Button {
public:
    BuyButton(const std::pair<int, int>& size, const std::pair<int, int>& position, UnitType unit_type);

    const UnitType& getUnitType() const;
private:
    UnitType unit_type_;
};

#endif // BUY_BUTTON_HPP