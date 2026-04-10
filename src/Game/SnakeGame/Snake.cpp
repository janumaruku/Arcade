/*
** EPITECH PROJECT, 2026
** Mirror_Arcade
** File description:
** Snake
*/

#include "Snake.hpp"

namespace arcade {
namespace game {

std::string SnakeGame::getName() const noexcept
{
    return "Snake";
}

} // game
} // arcade

extern "C"
{
    arcade::game::SnakeGame *entryPointGame()
    {
        return new arcade::game::SnakeGame();
    }
}
