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

    bool overlaps(Interval<T> other)
    {
        return contains(other.start) || contains(other.end) || other.contains(start) || other.contains(end);
    }

    bool operator==(const Interval<T> &other) const
    {
        return start == other.start && end == other.end;
    }

    // if the intervals overlap, return all parts of the intervals that overlap
    // if they don't overlap, return an empty vector
    std::vector<Interval<T>> overlap(Interval<T> other)
    {
        if (!overlaps(other))
            return {};

        std::vector<Interval<T>> result;

        if (contains(other.start))
            result.push_back(Interval<T>(other.start, std::min(end, other.end)));

        if (other.contains(start))
            result.push_back(Interval<T>(start, std::min(end, other.end)));

        return result;
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
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Interval<T> &interval, FormatContext &ctx)
    {
        return format_to(ctx.out(), "[{}, {}]", interval.start, interval.end);
    }
};
