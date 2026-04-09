/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include "Widget.hpp"

namespace arcade {
namespace game {

enum class TileType {
    WALL,
    DOT,
    EMPTY,
    POWER_PELLET
};

class Map {
public:
    Map(const std::string &path);
    ~Map() = default;
    // int getWidth(); // largeur
    // int getHeight(); // hauteur
    // bool isWall();
private:
    std::vector<std::vector<widget::Tile>> _map;
    void createTile(cosnt std::string &line);
    void loadGameMap(const std::string &path);
}
}
}

#endif /* !MAP_HPP_ */
