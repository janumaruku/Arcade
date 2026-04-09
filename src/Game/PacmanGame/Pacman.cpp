/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

arcade::game::Pacman::Pacaman()
{
    this->_pacman_position = {
    arcade::widget::Vec2.x = arcade::widget::CellUnit{27},
    arcade::widget::Vec2.y = arcade::widget::CellUnit{14}};
    this->_direction = arcade::game::Direction::RIGHT;
    this->_lives = 3;
    // set position (x, y)
    // set direction (RIGHT)
}

arcade::game::Pacman::~Pacaman()
{
}