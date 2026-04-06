/*
** EPITECH PROJECT, 2026
** Mirror_Arcade
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include "GameInterface.hpp"

namespace arcade {
namespace game {
class Snake : public IGameModule{
public:
    Snake() noexcept;
    ~Snake();
    void gameLogic();
    void move(std::vector<std::pair<int, int>> body);
    void getApplePosition(int AppleX, int AppleY);
    std::vector<std::pair<int, int>> body;
    std::vector<std::pair<int, int>> applePos;
protected:
private:
    int _snakeX;
    int _snakeY;
    int _appleX;
    int _appleY;
    int _width;
    int _length;
};
} // game
} // arcade


#endif /* !SNAKE_HPP_ */
