#ifndef RESOURCE_STORAGE_HPP
#define RESOURCE_STORAGE_HPP

/**
 * @file ResourceStorage.hpp
 * @author Jonathan Ramstedt
 * @brief Class for storing pointers to resource requiring objects.
 * 
 * @version 0.1
 * @date 2024-01-09 
 */

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class ResourceStorage;

/**
 * @brief A class for managing SFML graphics resources.
 */
class ResourceStorage {
public:
    /**
     * @brief Construct a new Resource Storage object
     * 
     */
    ResourceStorage();
    /**
     * @brief Adds a texture to the storage.
     * @param texture Shared pointer to sf::Texture.
     */
    void addTexture(const std::shared_ptr<sf::Texture> texture);

    /**
     * @brief Adds a font to the storage.
     * @param font Shared pointer to sf::Font.
     */
    void addFont(const std::shared_ptr<sf::Font> font);

    /**
     * @brief Retrieves the vector of textures.
     * @return Const reference to the vector of shared pointers to sf::Texture.
     */
    const std::vector<std::shared_ptr<sf::Texture>> getTextures() const;

    /**
     * @brief Retrieves the vector of fonts.
     * @return Const reference to the vector of shared pointers to sf::Font.
     */
    const std::vector<std::shared_ptr<sf::Font>> getFonts() const;
    
    private:
        std::vector<std::shared_ptr<sf::Texture>> textures; ///< Vector of shared pointers to sf::Texture.
        std::vector<std::shared_ptr<sf::Font>> fonts;       ///< Vector of shared pointers to sf::Font.
};

#endif // RESOURCE_STORAGE_HPP