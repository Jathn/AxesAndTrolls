#include "ResourceStorage.hpp"


ResourceStorage::ResourceStorage() { }


void ResourceStorage::addTexture(const std::shared_ptr<sf::Texture> texture) {
    textures.push_back(texture);
}


void ResourceStorage::addFont(const std::shared_ptr<sf::Font> font) {
    fonts.push_back(font);
}


const std::vector<std::shared_ptr<sf::Texture>> ResourceStorage::getTextures() const {
    return textures;
}


const std::vector<std::shared_ptr<sf::Font>> ResourceStorage::getFonts() const {
    return fonts;
}