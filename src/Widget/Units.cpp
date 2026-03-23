/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Units
*/

#include "include/Units.hpp"

namespace arcade {
namespace widget {
AUnit::AUnit(const int &value): _value(value)
{}

AUnit::~AUnit() = default;

unsigned int AUnit::getValue() const noexcept
{
    return _value;
}

CellUnit::CellUnit(const int &value): AUnit{value}
{}

FontSizeUnit::FontSizeUnit(const int &value): AUnit{value}
{}

WeightUnit::WeightUnit(const int &value): AUnit{value}
{}
}
}
