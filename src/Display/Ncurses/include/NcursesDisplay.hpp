/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NcursesDisplay
*/

#ifndef MYFTP_NCURSESDISPLAY_HPP
#define MYFTP_NCURSESDISPLAY_HPP

#include <chrono>
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
    int _row          = 0;
    int _col          = 0;
    std::unique_ptr<SCREEN, decltype(&delscreen)> _screen{nullptr, delscreen};
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
    std::chrono::steady_clock::time_point _startTime;
    std::unique_ptr<SCREEN, decltype(&delscreen)> _screen2{nullptr, delscreen};
    const std::unordered_map<int, widget::KeyCode> _keys = {
        {'a', widget::KeyCode::KEY_A},
        {'b', widget::KeyCode::KEY_B},
        {'c', widget::KeyCode::KEY_C},
        {'d', widget::KeyCode::KEY_D},
        {'e', widget::KeyCode::KEY_E},
        {'f', widget::KeyCode::KEY_F},
        {'g', widget::KeyCode::KEY_G},
        {'h', widget::KeyCode::KEY_H},
        {'i', widget::KeyCode::KEY_I},
        {'j', widget::KeyCode::KEY_J},
        {'k', widget::KeyCode::KEY_K},
        {'l', widget::KeyCode::KEY_L},
        {'m', widget::KeyCode::KEY_M},
        {'n', widget::KeyCode::KEY_N},
        {'o', widget::KeyCode::KEY_O},
        {'p', widget::KeyCode::KEY_P},
        {'q', widget::KeyCode::KEY_Q},
        {'r', widget::KeyCode::KEY_R},
        {'s', widget::KeyCode::KEY_S},
        {'t', widget::KeyCode::KEY_T},
        {'u', widget::KeyCode::KEY_U},
        {'v', widget::KeyCode::KEY_V},
        {'w', widget::KeyCode::KEY_W},
        {'x', widget::KeyCode::KEY_X},
        {'y', widget::KeyCode::KEY_Y},
        {'z', widget::KeyCode::KEY_Z},
        {'A', widget::KeyCode::KEY_A},
        {'B', widget::KeyCode::KEY_B},
        {'C', widget::KeyCode::KEY_C},
        {'D', widget::KeyCode::KEY_D},
        {'E', widget::KeyCode::KEY_E},
        {'F', widget::KeyCode::KEY_F},
        {'G', widget::KeyCode::KEY_G},
        {'H', widget::KeyCode::KEY_H},
        {'I', widget::KeyCode::KEY_I},
        {'J', widget::KeyCode::KEY_J},
        {'K', widget::KeyCode::KEY_K},
        {'L', widget::KeyCode::KEY_L},
        {'M', widget::KeyCode::KEY_M},
        {'N', widget::KeyCode::KEY_N},
        {'O', widget::KeyCode::KEY_O},
        {'P', widget::KeyCode::KEY_P},
        {'Q', widget::KeyCode::KEY_Q},
        {'R', widget::KeyCode::KEY_R},
        {'S', widget::KeyCode::KEY_S},
        {'T', widget::KeyCode::KEY_T},
        {'U', widget::KeyCode::KEY_U},
        {'V', widget::KeyCode::KEY_V},
        {'W', widget::KeyCode::KEY_W},
        {'X', widget::KeyCode::KEY_X},
        {'Y', widget::KeyCode::KEY_Y},
        {'Z', widget::KeyCode::KEY_Z},
        {'0', widget::KeyCode::KEY_0},
        {'1', widget::KeyCode::KEY_1},
        {'2', widget::KeyCode::KEY_2},
        {'3', widget::KeyCode::KEY_3},
        {'4', widget::KeyCode::KEY_4},
        {'5', widget::KeyCode::KEY_5},
        {'6', widget::KeyCode::KEY_6},
        {'7', widget::KeyCode::KEY_7},
        {'8', widget::KeyCode::KEY_8},
        {'9', widget::KeyCode::KEY_9},
        {KEY_F(1), widget::KeyCode::KEY_F1},
        {KEY_F(2), widget::KeyCode::KEY_F2},
        {KEY_F(3), widget::KeyCode::KEY_F3},
        {KEY_F(4), widget::KeyCode::KEY_F4},
        {KEY_F(5), widget::KeyCode::KEY_F5},
        {KEY_F(6), widget::KeyCode::KEY_F6},
        {KEY_F(7), widget::KeyCode::KEY_F7},
        {KEY_F(8), widget::KeyCode::KEY_F8},
        {KEY_F(9), widget::KeyCode::KEY_F9},
        {KEY_F(10), widget::KeyCode::KEY_F10},
        {KEY_F(11), widget::KeyCode::KEY_F11},
        {KEY_F(12), widget::KeyCode::KEY_F12},
        {KEY_UP, widget::KeyCode::UP},
        {KEY_DOWN, widget::KeyCode::DOWN},
        {KEY_RIGHT, widget::KeyCode::RIGHT},
        {KEY_LEFT, widget::KeyCode::LEFT},
        {KEY_BACKSPACE, widget::KeyCode::BACKSPACE},
        {27, widget::KeyCode::ESC},
        {10, widget::KeyCode::ENTER}
    };

    static void initNcurses();

    void dispWindowBox() const;

    void openWindowImpl(const CellUnitView &xAxis, const CellUnitView &yAxis);

    void drawText(const widget::AWidget &widget) const;

    void drawTile(const widget::AWidget &widget) const;

    void drawTile(const widget::Tile &tile) const;

    void drawRectangle(const widget::AWidget &widget) const;

    void drawTileGrid(const widget::AWidget &widget) const;

    static bool handleKeyMouse(int character, widget::Event &event);

    bool handleKey(const int character, widget::Event &event) const;
};

} // display
} // arcade

#endif //MYFTP_NCURSESDISPLAY_HPP
