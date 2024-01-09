#ifndef RESOURCE_LOADING_HPP
#define RESOURCE_LOADING_HPP

/**
 * @file ResourceLoading.hpp
 * @author Jonathan Ramstedt
 * @brief File intended to contain functions for handling the loading of necessary resources.
 * 
 * @version 0.1
 * @date 2024-01-09 
 */

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <ResourceStorage.hpp>  

/**
 * @brief Function for loading SFML library object resources. This includes: fonts & textures etc.
 * 
 * @tparam T 
 * @param resource_url 
 * @return T resource - Loaded resource 
 */
template <typename T>
T loadResource(const std::string& resource_url);

/**
 * @brief Function for loading a SFML text object with given parameters. Default parameters: ("../resources/fonts/TTF/Crimson-Italic.ttf", 24, sf::Color::Red)
 * 
 * @param str Message to be displayed.
 * @param storage ResourceStorage object.
 * @param font_url Relative path to font (.ttf file)
 * @param font_size
 * @param text_color 
 * @return Ready to display text object.
 */
sf::Text loadText(  const std::string& str,
                    ResourceStorage& storage,
                    const std::string& font_url="../resources/fonts/TTF/Crimson-Italic.ttf", 
                    const int& font_size=24, 
                    const sf::Color& text_color=sf::Color::Red );

/**
 * @brief Primarily loads a picture via it's url and creates a texture for the returned sprite. 
 *        If no URL is provided a sprite with @param color is returned. 
 * @param picture_url 
 * @param color Default: White
 * @return Ready to display sprite object.
 */
sf::Sprite loadSprite(  ResourceStorage& storage,
                        const std::string& picture_url="",
                        sf::Color color=sf::Color::White    );

#endif // RESOURCE_LOADING_HPP
