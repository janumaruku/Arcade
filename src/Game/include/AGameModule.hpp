/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

namespace arcade {
namespace game {
class IGameModule {
public:
    AGameModule() = default;
    ~AGameModule() = default;

    [[nodiscard]] std::string getName() const noexcept;

    void start() noexcept;

    [[nodiscard]] virtual const widget::GameState &getGameState() noexcept = 0;

    virtual void userEvent(const widget::Event &input) = 0;

    [[nodiscard]] virtual const widget::Resource &getResource() const noexcept = 0;
private:
    std::string _gameName;
};
}
}

#endif /* !AGAMEMODULE_HPP_ */
