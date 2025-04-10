#pragma once

#include <cmath>

struct Interval{
    const double min, max;

    inline Interval() noexcept : min(-INFINITY), max(INFINITY) {}
    inline Interval(const double minimum, const double maximum) noexcept : min(minimum), max(maximum) {}

    inline constexpr double size() const noexcept {
        return max - min;
    }

    inline constexpr double contains(const double value) const noexcept {
        return min <= value && value <= max;
    }

    inline constexpr bool surrounds(const double value) const noexcept {
        return min < value && value < max;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(INFINITY, -INFINITY);
const Interval Interval::universe = Interval(-INFINITY, INFINITY);
