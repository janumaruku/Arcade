/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Map
*/

#include <fstream>
#include <string>
#include "Map.hpp"

namespace arcade {
namespace game {
Map::Map(const std::string &path)
{
    this->loadGameMap(path);
}

void Map::createTile(const std::string &line)
{
    std::vector<widget::Tile> tmp;

    for (const auto &character : line) {
        widget::Tile tile;
        switch (character) {
            case '#':
                tile.symbol = "╔";
                break;
            case '-':
                tile.symbol = "═";
                break;
            case '@':
                tile.symbol = "╗";
                break;
            case '.':
                tile.symbol = "•";
                break;
            case 'o':
                tile.symbol = "●";
                break;
            case '$':
                tile.symbol = "╚";
                break;
            case '&':
                tile.symbol = "╝";
                break;
        }
        tmp.push_back(tile);
    }
    _map.push_back(tmp);
}

void Map::loadGameMap(const std::string &path)
{
    std::fstream mapFile(path);
    std::string line;

    while (std::getline(mapFile, line)) {
        createTile(line);
    }
}

}
}
