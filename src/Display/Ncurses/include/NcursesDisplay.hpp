/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NcursesDisplay
*/

#ifndef MYFTP_NCURSESDISPLAY_HPP
#define MYFTP_NCURSESDISPLAY_HPP

#include <iostream>

#include "DisplayInterface.hpp"

namespace arcade {
namespace display {

class NcursesDisplay: public IDisplayModule {
public:
    ~NcursesDisplay() override;

    void closeWindow() noexcept override;

    void openWindow() noexcept override;

    void openWindow(const widget::Vec2 &size) noexcept override;

    [[nodiscard]] bool isOpen() const noexcept override;

    void draw(const widget::AWidget &widget) override;

    void clear(const widget::Color &color) noexcept override;

    void display() noexcept override;

    void playSound(const std::string &soundName) noexcept override;

    void loadResource(const widget::Resource &resources) override;

    [[nodiscard]] widget::Vec2 getWindowSize() const noexcept override;

    bool pollEvent(widget::Event &event) override;

    [[nodiscard]] const std::string &getName() const noexcept override;

private:
    bool _isOpen{false};
};

} // display
} // arcade

#endif //MYFTP_NCURSESDISPLAY_HPP
