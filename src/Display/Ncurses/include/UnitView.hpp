/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** UnitView
*/

#ifndef MYFTP_UNITVIEW_HPP
#define MYFTP_UNITVIEW_HPP

#include "Units.hpp"

namespace arcade {
namespace display {
class CellUnitView {
public:
    CellUnitView() = delete;

    ~CellUnitView() = default;

    CellUnitView(const widget::CellUnit &unit);

    CellUnitView(widget::CellUnit &&unit);

    operator int() const noexcept;

private:
    int _value = 0;
};
}
}

#endif //MYFTP_UNITVIEW_HPP
