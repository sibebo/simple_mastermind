#pragma once

#include <string>
#include <iostream>
#include <algorithm>

#include <windows.h>

#include "console_colors.h"

class Buffer
{
public:
    Buffer(size_t buffer_size)
        : buffer(buffer_size, ' ')
    {}

    Buffer(const std::string &buffer)
        : buffer(buffer)
    {}

    void    Reset()
    {
        std::fill(buffer.begin(), buffer.end(), ' ');
        position = 0;
    }

    auto    Get() const
    {
        return buffer;
    }

    void    Set(const std::string &new_buffer)
    {
        buffer = new_buffer;
    }

    bool    Has(char c) const
    {
        return (buffer.find(c) != std::string::npos);
    }

    void    Insert(char c)
    {
        buffer[position] = c;
        MoveRight();
    }

    void    Set(char c)
    {
        buffer[position] = c;
    }

    void    MoveRight()
    {
        if (position <= buffer.size() - 2)
        {
            ++position;
        }
    }

    void    MoveLeft()
    {
        if (position > 0)
        {
            --position;
        }
    }

    void    Print()
    {
        std::cout << '\r' << '[';
        for (auto c : buffer)
        {
            std::cout << Color(c) << c << console_color::reset;
        }
        std::cout << ']';
    }

    void    PrintAndMoveCursorToPosition()
    {
        Print();
        MoveCursorToPosition();
    }

    auto    Position() const
    {
        return position;
    }


private:
    size_t     position{0};

    std::string buffer;

    void    MoveCursorToPosition() const
    {
        std::cout << std::string(buffer.size() + 1 - Position(), '\b');
    }

    console_color::ConsoleColor    Color(char value) const
    {
        switch (value)
        {
        default:
            return console_color::reset;
        case '1':
            return console_color::red;
        case '2':
            return console_color::green;
        case '3':
            return console_color::blue;
        case '4':
            return console_color::yellow;
        case '5':
            return console_color::cyan;
        case '6':
            return console_color::magenta;
        case '7':
            return console_color::white;
        case '8':
            return console_color::black;
        case '9':
            return console_color::reset;
        case '0':
            return console_color::reset;
        }
    }

};
