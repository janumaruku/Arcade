/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NcursesDisplay
*/

#include "NcursesDisplay.hpp"

namespace arcade {
namespace display {
NcursesDisplay::~NcursesDisplay() = default;

void NcursesDisplay::closeWindow() noexcept
{}

void NcursesDisplay::openWindow() noexcept
{
    if (_isOpen)
        return;

    setlocale(LC_ALL, "");
    initNcurses();
    _isOpen = true;
    openWindowImpl(0, 0);
}

void NcursesDisplay::openWindow(const widget::Vec2 &size) noexcept
{
    if (_isOpen)
        return;

    setlocale(LC_ALL, "");
    initNcurses();
    _isOpen = true;
    openWindowImpl(size.x, size.y);
}

bool NcursesDisplay::isOpen() const noexcept
{
    return _isOpen;
}

void NcursesDisplay::draw(const widget::AWidget &/*widget*/)
{}

void NcursesDisplay::clear(const widget::Color &/*color*/) noexcept
{}

void NcursesDisplay::display() noexcept
{}

void NcursesDisplay::playSound(const std::string &/*soundName*/) noexcept
{}

void NcursesDisplay::loadResource(const widget::Resource &/*resources*/)
{}

widget::Vec2 NcursesDisplay::getWindowSize() const noexcept
{
    return {.x = 0, .y = 0};
}

bool NcursesDisplay::pollEvent(widget::Event &/*event*/)
{
    return false;
}

const std::string &NcursesDisplay::getName() const noexcept
{
    return _libName;
}

void NcursesDisplay::initNcurses()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void NcursesDisplay::openWindowImpl(const CellUnitView &x,
    const CellUnitView &y)
{
    int row = y;
    int col = x;

    if (row == 0 || col == 0)
        getmaxyx(stdscr, row, col);
    _frameRate = 1.0 / 60.0;

    _window.reset(newwin(row, col, 0, 0));
    box(_window.get(), 0, 0);
    mvwprintw(_window.get(), 0, 0, "╭");
    mvwprintw(_window.get(), 0, col - 1, "╮");
    mvwprintw(_window.get(), row - 1, 0, "╰");
    mvwprintw(_window.get(), row - 1, col - 1, "╯");
    mvwprintw(_window.get(), 0, 3, "%s - Ncurses", _windowTitle.c_str());
    refresh();
    wrefresh(_window.get());
}
} // namespace display
} // namespace arcade

extern "C" arcade::display::IDisplayModule *entryPointDisplay()
{
    return new arcade::display::NcursesDisplay();
}
