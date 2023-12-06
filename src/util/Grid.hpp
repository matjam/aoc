#pragma once
#include <vector>

template <class T>
class Grid
{
private:
    std::vector<T> _data;
    int _width;
    int _height;

public:
    Grid() {}
    Grid(int width, int height)
    {
        set_size(width, height);
    }

    void set_size(int width, int height)
    {
        _data.resize(height * width);
        _width = width;
        _height = height;
    }

    void set(int x, int y, T v)
    {
        if (x > -1 && x < _width && y > -1 && y < _height)
            _data[x + y * _width] = v;
    }

    T get(int x, int y)
    {
        if (x > -1 && x < _width && y > -1 && y < _height)
            return _data[x + y * _width];

        return T();
    }

    std::vector<T> neighbours(int x, int y)
    {
        std::vector<std::pair<int, int>> offsets = {
            {-1, -1},
            {0, -1},
            {1, -1},
            {-1, 0},
            {1, 0},
            {-1, 1},
            {0, 1},
            {1, 1},
        };

        std::vector<T> result;

        for (auto loc : offsets)
        {
            T v = get(x + loc.first, y + loc.second);
            result.push_back(v);
        }

        return result;
    }

    int width() { return _width; }

    int height() { return _height; }
};
