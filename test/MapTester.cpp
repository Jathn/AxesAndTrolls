#include "MapTester.hpp"
#include <iostream>

MapTester::MapTester() { }

int MapTester::runTest() {

    std::vector<Tile> map;
    int width = 5;
    int height = 3;
    
    std::cout << "## Map generation test ##" << std::endl;
    /* Important algorithm that will always be needed at map generation ( except of course if map is handmade ) */
    std::cout << "Enter width: " << std::endl;
    std::cin >> width;
    std::cout << "Enter height: " << std::endl;
    std::cin >> height;
    std::string mapString = "";
    for (int i = 0; i < width * height; i++) {
        std::vector<std::shared_ptr<Tile>> neighbors;
        if (i % width != 0) {
            neighbors.push_back(std::make_shared<Tile>(map[i - 1]));
        }
        if (i >= width) {
            neighbors.push_back(std::make_shared<Tile>(map[i - width]));
        }
        Tile tile = Tile(i, neighbors);

        map.push_back(tile);

        mapString += tile.getTypeChar();

        if ((i + 1) % width == 0) {
            mapString += '\n';
        }
    }

    std::cout << mapString << std::endl;

    if (mapString[2] == map[2 + width].getNeighbors().at(1)->getTypeChar()) {
        addCompleted("Map generation");
    } else {
        addUnsuccessful("Map generation");
    }

    /* Checking if the map is generated correctly */
    
    return 0;
}

void MapTester::addCompleted(const std::string& str) {
    tests_completed_++;
    tests_total_++;
    std::cout << "Test completed: " << str << std::endl;
}

void MapTester::addUnsuccessful(const std::string& str) {
    tests_total_++;
    std::cout << "Test unsuccessful: " << str << std::endl;
}
