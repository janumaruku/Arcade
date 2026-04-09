/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "Widget.hpp"

namespace arcade {
namespace game {
enum class Direction {
    widget::KeyCode::UP,
    widget::KeyCode::DOWN,
    widget::KeyCode::RIGHT,
    widget::KeyCode::LEFT
};

class Pacman {
public:
    Pacman();
    ~Pacman();

    Direction getDirection();
    void setDirection(Direction direction);
private:
    widget::AWidget::position _pacman_position;
    Direction _direction;
    int _lives;
}
}
};

#endif /* !PACMAN_HPP_ */
