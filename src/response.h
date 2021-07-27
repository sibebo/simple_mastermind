#pragma once

#include <string>
#include <algorithm>

#include "console_colors.h"

namespace mastermind {

class   Response
{
public:
    Response(size_t code_size)
        : code_size(code_size)
    {}

    void    Set(int match, int off)
    {
        if (match + off > code_size) throw std::runtime_error("Number of matches and offs are larger than code size");

        match_count = match;
        off_count = off;
    }

    bool    IsDone() const
    {
        return (match_count == code_size);
    }

    std::string     AsString() const
    {
        std::string     hits(code_size, '.');
        std::fill_n(hits.begin(), match_count, '#');
        std::fill_n(hits.begin() + match_count, off_count, '+');

        return hits;
    }

    void    Print() const
    {
        std::cout << " [";

        for (auto c : AsString())
        {
            std::cout << Color(c) << c << console_color::reset;
        }

        std::cout << "]";
    }

private:
    size_t      code_size{0};
    int         match_count{0};
    int         off_count{0};

    console_color::ConsoleColor    Color(char value) const
    {
        switch (value)
        {
        default:
            return console_color::reset;
        case '#':
            return console_color::red;
        case '+':
            return console_color::white;
        }
    }
};

}   // namespace mastermind {

