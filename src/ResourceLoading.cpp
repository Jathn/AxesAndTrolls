#include "ResourceLoading.hpp"

template <typename T>
T loadResource(const std::string& resource_url) {
    T resource;
    try {
        if(!resource.loadFromFile(resource_url)) {
            throw std::runtime_error("Failed to load: " + resource_url);
        }
    } catch(const std::exception& e) {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
        
        // Rethrow to higher order function:
        throw;
    }

    return resource;
}


sf::Text loadText(  const std::string& str,
                    ResourceStorage& storage,
                    const std::string& font_url, 
                    const int& font_size, 
                    const sf::Color& text_color ) {
    std::shared_ptr<sf::Font> fontPtr;
    sf::Text text;
    try {
        // Might throw exception:
        fontPtr = std::make_shared<sf::Font>(loadResource<sf::Font>(font_url));
        storage.addFont(fontPtr);
        // Only if ^ successful:
        text.setFont(*fontPtr);
        text.setCharacterSize(font_size);
        text.setFillColor(text_color);
        text.setString(str);
    } catch (const std::exception& e) {
        std::cerr << "Exception while loading font: " << e.what() << std::endl;
    }

    return text;
}


sf::Sprite loadSprite(  ResourceStorage& storage,
                        const std::string& picture_url,
                        sf::Color color  ) {
    std::shared_ptr<sf::Texture> texturePtr;
    sf::Sprite sprite;

    try {
        if(picture_url.length() > 0) {
            // Might throw exception:
            texturePtr = std::make_shared<sf::Texture>(loadResource<sf::Texture>(picture_url));
            storage.addTexture(texturePtr);
            sprite.setTexture(*texturePtr);
        } else {
            sprite.setColor(color);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception while loading textures: " << e.what() << std::endl;
    }

    return sprite;
}