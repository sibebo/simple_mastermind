#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <stdexcept>

#include "console_colors.h"

namespace mastermind {

class   Response
{
public:
    enum HIT {
        NONE, OFF, MATCH 
    };

    Response(int code_size)
        : code_size(code_size)
    {}

    void    Set(int match, int off)
    {
        match_count = match;
        off_count = off;
    }
    
    bool    Done() const
    {
        return (match_count == code_size);
    }
    
    std::vector<HIT>    Get() const
    {
        std::vector<HIT>    hits(code_size, HIT::NONE);
        std::fill_n(hits.begin(), match_count, HIT::MATCH);
        std::fill_n(hits.begin() + match_count, off_count, HIT::OFF);
        
        return hits;
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
            std::cout << Color(c) << c << Color(0);
        }

        std::cout << "]";
    }
    
private:
    int     code_size{0}; 
    int     match_count{0};
    int     off_count{0};

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

class Mastermind
{
    int     number_of_colors{6};
    int     code_size{4};

    std::vector<int> base;
    std::vector<int> code;

public:
    Mastermind(int number_of_colors, int code_size) 
        : number_of_colors(number_of_colors),
          code_size(code_size),
          base(number_of_colors, 0),
          code(code_size, 0)
    {
        std::iota(base.begin(), base.end(), 1);
        Shuffle();
    }

    const std::vector<int>&    GetCode() const
    {
        return code;
    }

    void    PrintCode() const
    {
        for (auto v : code)
        {
            std::cout << v;
        }
        std::cout << std::endl;
    }
    
    void    Shuffle()
    {    
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(base.begin(), base.end(), std::default_random_engine(seed));
        std::copy_n(base.begin(), code_size, code.begin());
    }
    
    Response    Check(std::vector<int> guess)
    {
        if (guess.size() != code.size()) throw std::runtime_error("Guess size does not match code size!!!");

        int     match{0};
        int     off{0};
        
        for (int i=0; i<code_size; ++i)
        {
            if (code[i] == guess[i])
                ++match;
            else if (std::find(code.begin(), code.end(), guess[i]) != code.end())
                ++off;
        }
        
        Response    response(code_size);
        response.Set(match, off);
        
        return response;
    }
    
private:
};

} // namespace mastermind {
