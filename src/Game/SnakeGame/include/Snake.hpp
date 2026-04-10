/*
** EPITECH PROJECT, 2026
** Mirror_Arcade
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_
#include <iostream>
#include <chrono>
#include "GameInterface.hpp"
#include "Widget.hpp"

#define GRID_SIZE_X 45
#define GRID_SIZE_Y 30

namespace arcade {
namespace game {
namespace snake {
typedef enum {
    UP,
    LEFT,
    RIGHT,
    DOWN
} Direction;

typedef struct {
    widget::Vec2 head_pos;
    std::vector<widget::Vec2> pos;
    snake::Direction dir;
    long long score;
    bool addTail;
} Player;
} // snake

static const std::unordered_map<snake::Direction, std::string> SnakeUTF8 = {
    {snake::RIGHT, "▶"},
    {snake::LEFT,  "◀"},
    {snake::UP,    "▲"},
    {snake::DOWN,  "▼"},
};

class SnakeGame : public IGameModule {
public:
    SnakeGame();
    ~SnakeGame() override = default;

    [[nodiscard]] std::string getName() const noexcept override;
    void start() noexcept override;
    [[nodiscard]] const widget::GameState &getGameState() noexcept override;
    void userEvent(const widget::Event &input) override;
    [[nodiscard]] const widget::Resource &getResource() const noexcept override;

protected:
private:
    snake::Player _snakebody;
    snake::Direction _direction;
    std::vector<std::size_t> _map;
    void updateDirection();
    void updateGrid();
    void addFood();
    widget::GameState _gamest;
    bool _gameover;
};
} // game
} // arcade


#endif /* !SNAKE_HPP_ */
