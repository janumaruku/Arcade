/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Pacman
*/

#include "PacmanGame.hpp"

arcade::game::PacmanGame::PacmanGame()
{
}

arcade::game::PacmanGame::~PacmanGame()
{
}

[[nodiscard]] std::string arcade::game::PacmanGame::getName() const noexcept
{
    return "Pacman";
}

void arcade::game::PacmanGame::start() noexcept
{
    // creer la map en appelant les fonction qu'on a créer dans map.hpp
}

[[nodiscard]] const arcade::widget::GameState &arcade::game::PacmanGame::getGameState() noexcept
{
    return this->_gameState;
}

void arcade::game::PacmanGame::userEvent(const widget::Event &)
{
}

[[nodiscard]] const arcade::widget::Resource &arcade::game::PacmanGame::getResource() const noexcept
{
    return this->_resources;
}