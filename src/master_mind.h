#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <stdexcept>

#include "response.h"



namespace mastermind {

class Mastermind
{
    std::string     base;       ///< holding the full base, i.e. all 'colors'.
    std::string     code;       ///< holding the code to guess.

public:
    Mastermind(size_t number_of_colors, size_t code_size)
        : base(number_of_colors, ' '),
          code(code_size, ' ')
    {
        std::iota(base.begin(), base.end(), '1');
        Shuffle();
    }

    const std::string&  GetCode() const
    {
        return code;
    }

    void    PrintCode() const
    {
        std::cout << code << std::endl;
    }

    void    Shuffle()
    {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(base.begin(), base.end(), std::default_random_engine(seed));
        std::copy_n(base.begin(), code.size(), code.begin());
    }

    Response    Check(const std::string &guess)
    {
        if (guess.size() != code.size()) throw std::runtime_error("Guess size does not match code size!!!");

        int     match{0};
        int     off{0};

        for (size_t i=0; i<code.size(); ++i)
        {
            if (code[i] == guess[i])
                ++match;
            else if (std::find(code.begin(), code.end(), guess[i]) != code.end())
                ++off;
        }

        Response    response(code.size());
        response.Set(match, off);

        return response;
    }

private:
};

} // namespace mastermind {
