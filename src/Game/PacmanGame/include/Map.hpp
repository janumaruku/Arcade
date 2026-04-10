/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <string>

#include "Widget.hpp"

namespace arcade {
namespace game {
class PacmanGame;

enum class TileType {
    WALL,
    DOT,
    EMPTY,
    POWER_PELLET
};

class Map {
public:
    Map() = default;
    ~Map() = default;

    void loadGameMap(const std::string &path, PacmanGame &game);
    // int getWidth(); // largeur
    // int getHeight(); // hauteur
    // bool isWall();
private:
    std::vector<std::vector<widget::Tile *>> _mapTile;
    void createTile(const std::string &line, PacmanGame &game);
};
}
}

#endif /* !MAP_HPP_ */
