#pragma once

#include <string>
#include <algorithm>

#include "console_colors.h"

namespace mastermind {

/**
 * @brief The Response class handles the response
 */
class   Response
{
public:
    Response(size_t code_size)
        : code_size(code_size)
    {}

    /**
     * @brief Set sets the number of exact matches and off matches.
     * @param match     number of exact matches.
     * @param off       number of off matches
     */
    void    Set(int match, int off)
    {
        if (match + off > code_size) throw std::runtime_error("Number of matches and offs are larger than code size");

        match_count = match;
        off_count = off;
    }

    /**
     * @brief IsDone returns true if number of exact matches = code size. I.e. game is done.
     * @return  true if game is done.
     */
    bool    IsDone() const
    {
        return (match_count == code_size);
    }

    /**
     * @brief AsString returns the response as a string where '#' represents exact match and '+' represents off match.
     * @return string representing the response.
     */
    std::string     AsString() const
    {
        std::string     hits(code_size, '.');
        std::fill_n(hits.begin(), match_count, '#');
        std::fill_n(hits.begin() + match_count, off_count, '+');

        return hits;
    }

    /**
     * @brief Print prints the response in color to console.
     */
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
    size_t      code_size{0};       ///< size of the code
    int         match_count{0};     ///< number of exact matches
    int         off_count{0};       ///< number of off matches

    /**
     * @brief Color converts a value, '#' or '+', to a color to be printed.
     * @param value     '#' or '+'
     * @return          color to be printed
     */
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

