/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Units
*/

#ifndef MYFTP_UNITS_HPP
#define MYFTP_UNITS_HPP
#include <cstddef>

namespace arcade {
namespace widget {
class AUnit {
public:
    AUnit() = default;

    explicit AUnit(const int &value);

    AUnit(const AUnit &) = default;

    AUnit(AUnit &&) noexcept = default;

    AUnit &operator=(const AUnit &) = default;

    AUnit &operator=(AUnit &&) noexcept = default;

    virtual ~AUnit() = 0;

    [[nodiscard]] int getValue() const noexcept;

protected:
    int _value{0};
};

class CellUnit: public AUnit {
public:
    CellUnit(const int &value);

    ~CellUnit() override = default;
};

class FontSizeUnit: public AUnit {
public:
    explicit FontSizeUnit(const int &value);

    ~FontSizeUnit() override = default;
};

class WeightUnit: public AUnit {
public:
    WeightUnit(const int &value);

    ~WeightUnit() override = default;
};
}
}

#endif //MYFTP_UNITS_HPP
