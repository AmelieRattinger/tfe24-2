#pragma once
#include <fmt/core.h>
#include "point.hpp"

template <typename T>
struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
    template <typename FormatContext>
    auto format(const Point<T>& p, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};
