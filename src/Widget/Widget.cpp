/*
** EPITECH PROJECT, 2026
** Arcade [WSL: Ubuntu-24.04]
** File description:
** Widget
*/

#include "Widget.hpp"

namespace arcade {
namespace widget {
AWidget::~AWidget() = default;

Vec2 Rectangle::getSize() const noexcept
{
    return _size;
}

void Rectangle::setSize(const Vec2 &size) noexcept
{
    _size = size;
}

TileGrid::TileGrid(const std::size_t &row, const std::size_t &column):
    Rectangle{Vec2{.x = static_cast<const int &>(column),
                   .y = static_cast<const int &>(row)}},
    _row{row},
    _column{column}
{
    _widgets.resize(_row);

    for (auto &lst: _widgets)
        lst.resize(_column);
}

std::vector<Tile> &TileGrid::operator[](const std::size_t &row)
{
    return _widgets[row];
}
} // namespace widget
} // namespace arcade
