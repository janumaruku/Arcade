/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** GameInterface
*/

#ifndef MYFTP_GAMEINTERFACE_HPP
#define MYFTP_GAMEINTERFACE_HPP

#include <string>

#include "Widget.hpp"

namespace arcade {
namespace game {
class IGameModule {
public:
    IGameModule() = default;

    virtual ~IGameModule() = default;

    [[nodiscard]] virtual std::string getName() const noexcept = 0;

    virtual void start() noexcept = 0;

    [[nodiscard]] virtual const widget::GameState &getGameState() noexcept = 0;

    virtual void userEvent(const widget::Event &input) = 0;

    [[nodiscard]] virtual const widget::Resource &getResource() const noexcept = 0;
};
}
}

#endif // MYFTP_GAMEINTERFACE_HPP
