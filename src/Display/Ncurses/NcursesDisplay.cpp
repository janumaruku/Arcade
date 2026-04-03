/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NcursesDisplay
*/

#include "NcursesDisplay.hpp"

#include <thread>

namespace arcade {
namespace display {
NcursesDisplay::~NcursesDisplay() = default;

void NcursesDisplay::closeWindow() noexcept
{
    if (!_isOpen)
        return;

    endwin();
    _isOpen = false;
}

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

void NcursesDisplay::draw(const widget::AWidget &widget)
{
    if (!_isOpen)
        return;

    drawText(widget);
}

void NcursesDisplay::clear(const widget::Color &/*color*/) noexcept
{
    if (!_isOpen)
        return;

    wclear(_window.get());
    dispWindowBox();
    refresh();
}

void NcursesDisplay::display() noexcept
{
    if (!_isOpen)
        return;

    wrefresh(_window.get());
    refresh();
    const std::chrono::steady_clock::time_point timeNow =
        std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsedTime = std::chrono::duration_cast
        <std::chrono::duration<double>>(timeNow - _startTime);

    if (elapsedTime.count() < _frameRate)
        std::this_thread::sleep_for(std::chrono::duration<double>
            (_frameRate - elapsedTime.count()));

    _startTime = std::chrono::steady_clock::now();
}

void NcursesDisplay::playSound(const std::string &/*soundName*/) noexcept
{
    if (!_isOpen)
        return;
}

void NcursesDisplay::loadResource(const widget::Resource &/*resources*/)
{
    if (!_isOpen)
        return;
}

widget::Vec2 NcursesDisplay::getWindowSize() const noexcept
{
    return {.x = _col, .y = _row};
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
    start_color();
    use_default_colors();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void NcursesDisplay::dispWindowBox() const
{
    box(_window.get(), 0, 0);
    mvwprintw(_window.get(), 0, 0, "╭");
    mvwprintw(_window.get(), 0, _col - 1, "╮");
    mvwprintw(_window.get(), _row - 1, 0, "╰");
    mvwprintw(_window.get(), _row - 1, _col - 1, "╯");
    mvwprintw(_window.get(), 0, 3, "%s - Ncurses", _windowTitle.c_str());
}

void NcursesDisplay::openWindowImpl(const CellUnitView &xAxis,
    const CellUnitView &yAxis)
{
    _row = yAxis;
    _col = xAxis;

    if (_row == 0 || _col == 0)
        getmaxyx(stdscr, _row, _col);
    _frameRate = 1.0 / 60.0;

    _window.reset(newwin(_row, _col, 0, 0));
    dispWindowBox();
    refresh();
    wrefresh(_window.get());
}

void NcursesDisplay::drawText(const widget::AWidget &widget) const
{
    if (widget.type == widget::WidgetType::TEXT) {
        const auto &text = dynamic_cast<const widget::Text &>(widget);

        const CellUnitView xAxis = text.position.x;
        const CellUnitView yAxis = text.position.y;

        init_pair(1, _colorMap.at(text.backgroundColor),
            _colorMap.at(text.textColor));

        wattron(_window.get(), COLOR_PAIR(1));
        mvwprintw(_window.get(), yAxis, xAxis, "%s", text.text.c_str());
        wattroff(_window.get(), COLOR_PAIR(1));
    }
}
} // namespace display
} // namespace arcade

extern "C" arcade::display::IDisplayModule *entryPointDisplay()
{
    return new arcade::display::NcursesDisplay();
}
