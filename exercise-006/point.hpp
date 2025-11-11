#pragma once

#include <type_traits>
#include <cmath>
#include <fmt/core.h>

template <typename T>
class Point {
    static_assert(std::is_arithmetic<T>::value, "Point<T>: T must be a numeric type");

public:
    T x;
    T y;

    Point() : x(T{}), y(T{}) {}

    Point(T x_val, T y_val) : x(x_val), y(y_val) {}

    void move(T dx, T dy) {
        x += dx;
        y += dy;
    }

    auto distance_to(const Point<T>& other) const -> std::common_type_t<T, double> {
        using dist_t = std::common_type_t<T, double>;
        auto dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
        auto dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
        return std::hypot(dx, dy);
    }
    
    bool operator==(const Point<T>& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Point<T>& rhs) const {
        return !(*this == rhs);
    }

};
