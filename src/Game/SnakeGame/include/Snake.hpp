/*
** EPITECH PROJECT, 2026
** Mirror_Arcade
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_
#include <chrono>
#include <deque>
#include <iostream>
#include <vector>

#include "GameInterface.hpp"

namespace arcade {
namespace game {
class Food {
public:
    Food() = default;

    explicit Food(std::deque<widget::Vec2> snake);

    void generateFood(std::deque<widget::Vec2> snake);

    // void drawFood(IDisplayModule *display);

    int getX() const
    {
        return _x;
    }

    int getY() const
    {
        return _y;
    }

    // Params::Vect _pos;

private:
    int _x;
    int _y;
};

class Snake: public IGameModule {
public:
    Snake();
    // void drawSnake(IDisplayModule* display);
    void update();
    void reset();

    std::deque<widget::Vec2> _body;
    widget::Vec2 _direction;
    bool _add_segment;
    int _score;
};
} // namespace game
} // namespace arcade

#endif /* !SNAKE_HPP_ */
