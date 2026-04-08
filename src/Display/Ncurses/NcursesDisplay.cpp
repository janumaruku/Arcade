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

    printf("\033[?1003l");
    printf("\033[?1006l");
    fflush(stdout);
    endwin();
    _isOpen = false;
}

void NcursesDisplay::openWindow() noexcept
{
    if (_isOpen)
        return;

    initNcurses();
    _isOpen = true;
    openWindowImpl(0, 0);
}

void NcursesDisplay::openWindow(const widget::Vec2 &size) noexcept
{
    if (_isOpen)
        return;

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
    drawTile(widget);
    drawRectangle(widget);
    // drawTileGrid(widget);
}

void NcursesDisplay::clear(const widget::Color &/*color*/) noexcept
{
    if (!_isOpen)
        return;

    wclear(_window.get());
}

void NcursesDisplay::display() noexcept
{
    if (!_isOpen)
        return;

    dispWindowBox();
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

bool NcursesDisplay::pollEvent(widget::Event &event)
{
    if (!_isOpen)
        return false;

    int character = wgetch(_window.get());

    if (character == ERR)
        return false;

    if (character == KEY_MOUSE)
        return handleKeyMouse(character, event);
    return handleKey(character, event);
}

const std::string &NcursesDisplay::getName() const noexcept
{
    return _libName;
}

short NcursesDisplay::getColorPair(const Foreground &foreground,
    const Background &background)
{
    const auto itt = std::ranges::find_if(_pairMap,
        [foreground, background](const auto &colorPair) {
            return colorPair.second.first == foreground &&
                colorPair.second.second == background;
        });

    if (itt != _pairMap.end())
        return itt->first;

    const short id = _pairId++;
    init_pair(id, _colorMap.at(foreground), _colorMap.at(background));
    _pairMap[id] = std::make_pair(foreground, background);

    return id;
}

void NcursesDisplay::initNcurses()
{
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    use_default_colors();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    timeout(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
    mouseinterval(0);
    printf("\033[?1003h");
    printf("\033[?1006h");
    fflush(stdout);
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
    keypad(_window.get(), TRUE);
    nodelay(_window.get(), TRUE);
    dispWindowBox();
}

void NcursesDisplay::drawText(const widget::AWidget &widget)
{
    if (widget.type == widget::WidgetType::TEXT) {
        const auto &text = dynamic_cast<const widget::Text &>(widget);

        const CellUnitView xAxis = text.position.x;
        const CellUnitView yAxis = text.position.y;

        const short colorId =
            getColorPair(text.textColor, text.backgroundColor);

        wattron(_window.get(), COLOR_PAIR(colorId));
        mvwprintw(_window.get(), yAxis + 1, xAxis + 1, "%s", text.text.c_str());
        wattroff(_window.get(), COLOR_PAIR(colorId));
    }
}

void NcursesDisplay::drawTile(const widget::AWidget &widget) const
{
    if (widget.type == widget::WidgetType::TILE) {
        const auto &tile = dynamic_cast<const widget::Tile &>(widget);

        const CellUnitView xAxis = tile.position.x;
        const CellUnitView yAxis = tile.position.y;

        init_pair(1, _colorMap.at(tile.color),
            _colorMap.at(tile.backgroundColor));

        wattron(_window.get(), COLOR_PAIR(1));
        mvwprintw(_window.get(), yAxis + 1, xAxis + 1, "%s",
            tile.symbol.c_str());
        wattroff(_window.get(), COLOR_PAIR(1));
    }
}

void NcursesDisplay::drawTile(const widget::Tile &tile) const
{
    const CellUnitView xAxis = tile.position.x;
    const CellUnitView yAxis = tile.position.y;

    init_pair(1, _colorMap.at(tile.color),
        _colorMap.at(tile.backgroundColor));

    wattron(_window.get(), COLOR_PAIR(1));
    mvwprintw(_window.get(), yAxis + 1, xAxis + 1, "%s", tile.symbol.c_str());
    wattroff(_window.get(), COLOR_PAIR(1));
}

void NcursesDisplay::drawRectangle(const widget::AWidget &widget) const
{
    if (widget.type == widget::WidgetType::RECTANGLE) {
        const auto &rectangle = dynamic_cast<const widget::Rectangle &>(widget);

        const CellUnitView xAxis = rectangle.position.x;
        const CellUnitView yAxis = rectangle.position.y;
        const CellUnitView xSize = rectangle.getSize().x;
        const CellUnitView ySize = rectangle.getSize().y;

        const std::unique_ptr<WINDOW, decltype(&delwin)> rect{
            subwin(_window.get(),
                ySize, xSize, yAxis + 1, xAxis + 1),
            delwin};
        box(rect.get(), 0, 0);
        mvwprintw(_window.get(), yAxis + 1, xAxis + 1, "%s", "╭");
        mvwprintw(_window.get(), yAxis + 1, xAxis + xSize, "%s", "╮");
        mvwprintw(_window.get(), yAxis + ySize, xAxis + 1, "%s", "╰");
        mvwprintw(_window.get(), yAxis + ySize, xAxis + xSize, "%s", "╯");
    }
}

// void NcursesDisplay::drawTileGrid(const widget::AWidget &widget) const
// {
//     if (widget.type == widget::WidgetType::TILE_GRID) {
//         widget::TileGrid tileGrid = dynamic_cast<const widget::TileGrid &>(
//             widget);
//
//         for (std::size_t i = 0; i < tileGrid.getRow(); ++i) {
//             for (std::size_t j = 0; j < tileGrid.getColumn(); ++j) {
//                 drawTile(tileGrid[i][j]);
//             }
//         }
//     }
// }

bool NcursesDisplay::handleKeyMouse(int /*character*/, widget::Event &event)
{
    MEVENT mouseEvent;

    if (getmouse(&mouseEvent) != OK)
        return false;

    if (mouseEvent.bstate & BUTTON1_PRESSED) {
        event.type = widget::Event::EventType::MOUSE_BUTTON_PRESSED;
        event.mouseButton.button = widget::MouseButton::LEFT;
    }
    if (mouseEvent.bstate & BUTTON1_RELEASED) {
        event.type = widget::Event::EventType::MOUSE_BUTTON_RELEASED;
        event.mouseButton.button = widget::MouseButton::LEFT;
    }
    if (mouseEvent.bstate & BUTTON3_PRESSED) {
        event.type = widget::Event::EventType::MOUSE_BUTTON_PRESSED;
        event.mouseButton.button = widget::MouseButton::RIGHT;
    }
    if (mouseEvent.bstate & BUTTON3_RELEASED) {
        event.type = widget::Event::EventType::MOUSE_BUTTON_RELEASED;
        event.mouseButton.button = widget::MouseButton::RIGHT;
    }
    event.mouseButton.x = mouseEvent.x - 1;
    event.mouseButton.y = mouseEvent.y - 1;
    return true;
}

bool NcursesDisplay::handleKey(const int character, widget::Event &event) const
{
    if (!_keys.contains(character))
        return false;

    event.type     = widget::Event::EventType::KEY_PRESSED;
    event.key.code = _keys.at(character);
    return true;
}
} // namespace display
} // namespace arcade

extern "C" arcade::display::IDisplayModule *entryPointDisplay()
{
    return new arcade::display::NcursesDisplay();
}
