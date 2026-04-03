/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NcursesDisplay
*/

#ifndef MYFTP_NCURSESDISPLAY_HPP
#define MYFTP_NCURSESDISPLAY_HPP

#include <iostream>
#include <ncurses.h>

#include "DisplayInterface.hpp"
#include "UnitView.hpp"

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
    std::string _libName     = "Ncurses";
    std::string _windowTitle = "Arcade";
    bool _isOpen{false};
    double _frameRate = 0;
    int _row = 0;
    int _col = 0;
    std::unique_ptr<WINDOW, decltype(&delwin)> _window{nullptr, delwin};
    const std::unordered_map<widget::Color, int> _colorMap = {
        {widget::Color::TRANSPARENT, -1},
        {widget::Color::BLACK, COLOR_BLACK},
        {widget::Color::RED, COLOR_RED},
        {widget::Color::GREEN, COLOR_GREEN},
        {widget::Color::YELLOW, COLOR_YELLOW},
        {widget::Color::BLUE, COLOR_BLUE},
        {widget::Color::MAGENTA, COLOR_MAGENTA},
        {widget::Color::CYAN, COLOR_CYAN},
        {widget::Color::WHITE, COLOR_WHITE},
    };

    static void initNcurses();

    void dispWindowBox() const;

    void openWindowImpl(const CellUnitView &x, const CellUnitView &y);

    void draw(const widget::Text &text);
};

} // display
} // arcade

#endif //MYFTP_NCURSESDISPLAY_HPP
