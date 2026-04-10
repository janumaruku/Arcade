/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Map
*/

#include <fstream>
#include <vector>
#include <string>

#include "Map.hpp"

namespace arcade {
namespace game {

void Map::createTile(const std::string &line, PacmanGame &game)
{
    std::vector<widget::Tile> tmp;

    for (const auto &character : line) {
        unique_ptr<widget::Tile> tile = std::make_unique<widget::Tile>();
        switch (character) {
            case '#':
                tile->symbol = "╔";
                break;
            case '-':
                tile->symbol = "═";
                break;
            case '@':
                tile->symbol = "╗";
                break;
            case '.':
                tile->symbol = "•";
                break;
            case 'o':
                tile->symbol = "●";
                break;
            case '$':
                tile->symbol = "╚";
                break;
            case '&':
                tile->symbol = "╝";
                break;
        }
        tmp.push_back(tile.get());
        game.getGameWidgetList().push_back(std::move(tile));
    }
    game.getGameWidgetList().emplace_back(tmp);
    _mapTile.push_back(tmp);
}

void Map::loadGameMap(const std::string &path, PacmanGame &game)
{
    std::fstream mapFile(path);
    std::string line;

    while (std::getline(mapFile, line)) {
        createTile(line, game);
    }
}

}
}