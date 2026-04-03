/*
** EPITECH PROJECT, 2026
** Arcade [WSL: Ubuntu-24.04]
** File description:
** Widget
*/

#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <forward_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Units.hpp"

namespace arcade {
namespace widget {
enum class Color: uint8_t {
    TRANSPARENT = 0,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

struct Vec2 {
    CellUnit x;
    CellUnit y;
};

enum class WidgetType : uint8_t {
    UNKNOWN = 0,
    TEXT,
    TILE,
    RECTANGLE,
    TILE_GRID,
};

struct AWidget {
    AWidget() = default;

    virtual ~AWidget() = 0;

    WidgetType type = WidgetType::UNKNOWN;
    Vec2 position   = {.x = CellUnit{0}, .y = CellUnit{0}};
};

struct Text: AWidget {
    std::string text;
    FontSizeUnit fontSize = FontSizeUnit{12};
    Color textColor       = Color::WHITE;
    Color backgroundColor = Color::BLACK;
};

struct Tile: AWidget {
    std::string symbol = " ";
    std::string textureName;
    Color color           = Color::WHITE;
    Color backgroundColor = Color::TRANSPARENT;
};

enum class BorderStyle : uint8_t {
    NONE = 0,
    SOLID,
};

struct BorderDecoration {
    WeightUnit weight = WeightUnit{0};
    Color borderColor = Color::WHITE;
    BorderStyle style = BorderStyle::NONE;
};

struct Rectangle: AWidget {
    explicit Rectangle(const Vec2 &size): _size{size}
    {}

    [[nodiscard]] Vec2 getSize() const noexcept;

    void setSize(const Vec2 &size) noexcept;

    BorderDecoration decoration;
    Color fillColor = Color::BLACK;
    std::string textureName;

protected:
    Vec2 _size = {.x = CellUnit{0}, .y = CellUnit{0}};
};

struct TileGrid: Rectangle {
    explicit TileGrid(const std::size_t &row, const std::size_t &column);

    std::vector<Tile> &operator[](const std::size_t &row);

    std::size_t getRow() const noexcept;

    std::size_t getColumn() const noexcept;

private:
    std::vector<std::vector<Tile>> _widgets;
    std::size_t _row    = 0;
    std::size_t _column = 0;
};

enum class KeyCode : int8_t {
    UNKNOWN = -1,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    ESC,
    ENTER,
    BACKSPACE,
    COUNT
};

enum class MouseButton : uint8_t {
    NONE = 0,
    LEFT,
    RIGHT,
};

class Event {
public:
    Event() = default;
    // {
    //
    // }
    struct KeyEvent {
        KeyCode code = KeyCode::UNKNOWN;
        bool alt     = false;
        bool ctrl    = false;
        bool shift   = false;
        bool system  = false;
    };

    struct MouseButtonEvent {
        MouseButton button = MouseButton::NONE;
        int x              = 0;
        int y              = 0;
    };

    enum class EventType : uint8_t {
        NONE = 0,
        CLOSED,
        KEY_PRESSED,
        KEY_RELEASED,
        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,

        COUNT,
    };

    EventType type = EventType::NONE;

    union {
        KeyEvent key{};
        MouseButtonEvent mouseButton;
    };
};

struct GameState {
    std::forward_list<std::unique_ptr<AWidget>> widgets;
    std::forward_list<std::string> sounds;
};

struct Resource {
    std::unordered_map<std::string, std::string> textures;
    std::unordered_map<std::string, std::string> sounds;
};

CellUnit operator+(const CellUnit &lhs, const int &rhs);
} // namespace widget
} // namespace arcade

#endif /* !WIDGET_HPP_ */
