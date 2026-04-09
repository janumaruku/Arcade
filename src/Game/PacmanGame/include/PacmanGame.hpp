/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <string>
#include "GameInterface.hpp"
#include "Widget.hpp"
#include "Map.hpp"


namespace arcade {
namespace game {
class PacmanGame : public arcade::game::IGameModule {
public:
    PacmanGame();
    ~PacmanGame();

    [[nodiscard]] std::string getName() const noexcept;

    void start() noexcept;

    [[nodiscard]] const widget::GameState &getGameState() noexcept;

    void userEvent(const widget::Event &input);

    [[nodiscard]] const widget::Resource &getResource() const noexcept;
private:
    widget::Resource _resources;
    widget::GameState _gameState;
    // Map _map; // champs qui stock la map
    int _score;
};
}
}

#endif /* !PACMAN_HPP_ */
