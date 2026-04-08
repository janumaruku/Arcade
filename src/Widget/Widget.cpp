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

// TileGrid::TileGrid(const std::size_t &row, const std::size_t &column):
//     Rectangle{Vec2{.x = static_cast<const int &>(column),
//                    .y = static_cast<const int &>(row)}},
//     _row{row},
//     _column{column}
// {
//     _widgets.resize(_row);
//
//     for (std::size_t i = 0; i < _row; ++i) {
//         _widgets[i].resize(_column);
//         for (std::size_t j = 0; j < _column; ++j) {
//             _widgets[i][j].position = {
//                 .x = _size.x + j,
//                 .y = _size.y + i
//             };
//         }
//     }
// }

// std::vector<Tile> &TileGrid::operator[](const std::size_t &row)
// {
//     return _widgets[row];
// }
//
// std::size_t TileGrid::getRow() const noexcept
// {
//     return _row;
// }
//
// std::size_t TileGrid::getColumn() const noexcept
// {
//     return _column;
// }

CellUnit operator+(const CellUnit &lhs, const int &rhs)
{
    return CellUnit{lhs.getValue() + rhs};
}

CellUnit operator+(const CellUnit &lhs, const CellUnit &rhs)
{
    return CellUnit{lhs.getValue() + rhs.getValue()};
}

CellUnit operator-(const CellUnit &lhs, const int &rhs)
{
    return CellUnit{lhs.getValue() - rhs};
}

CellUnit operator-(const CellUnit &lhs, const CellUnit &rhs)
{
    return CellUnit{lhs.getValue() - rhs.getValue()};
}

CellUnit operator/(const CellUnit &lhs, const int &rhs)
{
    return CellUnit{lhs.getValue() / rhs};
}
} // namespace widget
} // namespace arcade
