/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** DisplayInterface
*/

#ifndef MYFTP_DISPLAYINTERFACE_HPP
#define MYFTP_DISPLAYINTERFACE_HPP

#include <string>

#include "Widget.hpp"

namespace arcade {
namespace display {
class IDisplayModule {
public:
    IDisplayModule() = default;

    virtual ~IDisplayModule() = default;

    virtual void closeWindow() noexcept = 0;

    virtual void openWindow() noexcept = 0;

    virtual void openWindow(const widget::Vec2 &size) noexcept = 0;

    [[nodiscard]] virtual bool isOpen() const noexcept = 0;

    virtual void draw(const widget::AWidget &widget) = 0;

    virtual void clear(const widget::Color &color) noexcept = 0;

    virtual void display() noexcept = 0;

    virtual void playSound(const std::string &soundName) noexcept = 0;

    virtual void loadResource(const widget::Resource &resources) = 0;

    [[nodiscard]] virtual widget::Vec2 getWindowSize() const noexcept = 0;

    virtual bool pollEvent(widget::Event &event) = 0;

    virtual const std::string &getName() const noexcept = 0;
};
} // namespace display
} // namespace arcade

#endif // MYFTP_DISPLAYINTERFACE_HPP
