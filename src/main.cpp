#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "../include/testmain.hpp"
#include "../include/Movement.hpp"

int main() {
    bool testmode = false;
    if (testmode) {
        return testmain();
    }

    std::vector<std::shared_ptr<Tile>> map;
    int width = 7;
    int height = 7;

    std::pair<int, int> mapSize = std::make_pair(width, height);

    for (int i = 0; i < width * height; i++) {
        std::vector<std::shared_ptr<Tile>> neighbors;
        if (i % width != 0) {
            neighbors.push_back(map[i - 1]);
        }
        if (i >= width) {
            neighbors.push_back(map[i - width]);
        }
        std::shared_ptr<Tile> tile = std::make_shared<Tile>(i, i%width, i/width, neighbors, false, TileType::GRASS);

        map.push_back(tile);
    }
    
    for (int i = 0; i < width * height; i++) {
        if (i % width != width - 1) {
            map[i]->addNeighbor(map[i + 1]);
        }
        if (i < width * (height - 1)) {
            map[i]->addNeighbor(map[i + width]);
        }
    }

    for (int i = 0; i < width * height; i++) {
        std::cout << "Tile " << i << ": ";
        std::cout << "X: " << map[i]->getX() << ", ";
        std::cout << "Y: " << map[i]->getY() << std::endl;
    }
    
    std::cout << "Calculating distance between tile 0 and tile 15" << std::endl;
    std::pair<int, std::vector<int>> path = calculateDistance(map[5], map[42]);
    std::cout << "Distance: " << path.first << std::endl;
    std::cout << "Path: " << std::endl;
    int box_space = 0;
    for (auto tile : map) {
        switch (tile->getId()) {
            case 0:
                box_space = 4;
                break;
            case 10:
                box_space = 3;
                break;
            case 100:
                box_space = 2;
                break;
            default:
                break;
        }
        
        if (std::find(path.second.begin(), path.second.end(), tile->getId()) != path.second.end()) {
            std::cout << "[> " << tile->getId() << " <]";
        } else {
            std::cout << "[";
            for (int i = 0; i < box_space; i++) {
                std::cout << " ";
            }
            std::cout << tile->getId() << "]";
        }
        if (tile->getId() % width == width - 1) {
            std::cout << std::endl;
        }
    }
    return 0;
}