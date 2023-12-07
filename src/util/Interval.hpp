#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <fmt/format.h>

template <class T>
class Interval
{
public:
    T start;
    T end;

    Interval(){};
    Interval(T _start, T _end) : start(_start), end(_end){};

    bool contains(T value)
    {
        return value >= start && value <= end;
    }

    // returns true if this interval contains the other interval
    bool contains(Interval<T> other)
    {
        return other.start >= start && other.end <= end;
    }

    bool overlapped_at_start(Interval<T> other)
    {
        return other.start <= start && other.end >= start && other.end <= end;
    }

    bool overlapped_at_end(Interval<T> other)
    {
        return other.start >= start && other.start <= end && other.end >= end;
    }

    bool overlaps_completely(Interval<T> other)
    {
        return other.start <= start && other.end >= end;
    }

    bool operator==(const Interval<T> &other) const
    {
        return start == other.start && end == other.end;
    }

    // if the intervals overlap, return the part of the vector that overlaps.
    Interval<T> overlap(Interval<T> other)
    {
        if (!overlaps(other))
            return Interval<T>();

        T new_start = std::max(start, other.start);
        T new_end = std::min(end, other.end);

        return Interval<T>(new_start, new_end);
    }

    // Given a value and a map of intervals, return the interval that contains the value
    // If no interval contains the value, return an empty interval
    static Interval<T> find_interval(T value, std::map<T, Interval<T>> intervals)
    {
        for (auto [k, v] : intervals)
        {
            if (v.contains(value))
                return v;
        }

        return Interval<T>();
    }
};

template <class T>
struct fmt::formatter<Interval<T>>
{
    constexpr auto parse(format_parse_context &ctx) -> format_parse_context::iterator
    {
        // Parse the presentation format and store it in the formatter:
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    auto format(const Interval<T> &t, format_context &ctx) const -> format_context::iterator
    {
        // ctx.out() is an output iterator to write to.
        return fmt::format_to(ctx.out(), "[{}, {}]", t.start, t.end);
    }
};
