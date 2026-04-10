/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Pacman
*/

#include "PacmanGame.hpp"
#include "Map.hpp"

namespace arcade {
namespace game {

PacmanGame::PacmanGame()
{

}

[[nodiscard]] std::string PacmanGame::getName() const noexcept
{
    return "Pacman";
}

void PacmanGame::start() noexcept
{

}

std::forward_list<std::unique_ptr<widget::AWidget>> &PacmanGame::getGameWidgetList() noexcept
{
    return this->_gameState.widgets;
}

[[nodiscard]] const arcade::widget::GameState &PacmanGame::getGameState() noexcept
{
    return this->_gameState;
}

void PacmanGame::userEvent(const widget::Event &)
{
}

[[nodiscard]] const arcade::widget::Resource &PacmanGame::getResource() const noexcept
{
    return this->_resources;
}

}
}