/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** UnitView
*/

#include "UnitView.hpp"

arcade::display::CellUnitView::CellUnitView(const widget::CellUnit &unit):
    _value{unit.getValue()}
{}

arcade::display::CellUnitView::CellUnitView(widget::CellUnit &&unit):
    _value{unit.getValue()}
{}

arcade::display::CellUnitView::operator int() const noexcept
{
    return _value;
}
