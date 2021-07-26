#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <windows.h>


#include "console_colors.h"

class Buffer
{
    HANDLE  hConsole;
public:
    Buffer(int buffer_size)
        : buffer_size(buffer_size),
          buffer(buffer_size, ' ')
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        PrintAndMoveCursorToPosition();
    }
    
    void    Reset()
    {
        transform(buffer.begin(), buffer.end(), buffer.begin(), [](auto c){return ' ';});
        position = 0;
    }

    void    Set(const std::vector<int> &new_buffer)
    {
        buffer_size = new_buffer.size();
        buffer.resize(buffer_size);
        std::transform(new_buffer.begin(), new_buffer.end(), buffer.begin(), [](auto v){return '0' + v;});
    }

    void    Set(const std::string &new_buffer)
    {
        buffer_size = new_buffer.size();
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
    
    void    MoveRight()
    {
        if (position <= buffer_size - 2)
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
        for (auto i=0; i<buffer_size; ++i)
        {
            std::cout << Color(buffer[i]) << buffer[i] << console_color::reset;
        }
        std::cout << ']';
        //std::cout << " p: " << Position();
        //std::cout << "    " << " ";
    }

    void    PrintAndMoveCursorToPosition()
    {
        Print();
        MoveCursorToPosition();
    }
    
    std::vector<int>    Get() const
    {
        std::vector<int>    guess;
        std::transform(buffer.begin(), buffer.end(), std::back_inserter(guess), [](auto c){return c - '0';});
        return guess;
    }
    
    int     Position() const
    {
        return position;
    }


private:
    int     buffer_size{0};
    int     position{0};
    
    std::string buffer;
    
    void    MoveCursorToPosition() const
    {
        std::cout << std::string(5 - Position(), '\b');
    }
    
    void    SetColor(char value) const
    {
        switch (value)
        {
        default:
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    //| BACKGROUND_RED
                                    //| BACKGROUND_GREEN
                                    //| BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    //| BACKGROUND_INTENSITY
                                    );
            break;
        case '1':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    | BACKGROUND_RED
                                    //| BACKGROUND_GREEN
                                    //| BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '2':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    //| BACKGROUND_RED
                                    | BACKGROUND_GREEN
                                    //| BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '3':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    //| BACKGROUND_RED
                                    //| BACKGROUND_GREEN
                                    | BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '4':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    //| FOREGROUND_RED
                                    //| FOREGROUND_GREEN
                                    //| FOREGROUND_BLUE
                                    | BACKGROUND_RED
                                    | BACKGROUND_GREEN
                                    //| BACKGROUND_BLUE
                                    //| FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '5':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    | BACKGROUND_RED
                                    //| BACKGROUND_GREEN
                                    | BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '6':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    //| FOREGROUND_RED
                                    //| FOREGROUND_GREEN
                                    //| FOREGROUND_BLUE
                                    //| BACKGROUND_RED
                                    | BACKGROUND_GREEN
                                    | BACKGROUND_BLUE
                                    //| FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '7':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    //| BACKGROUND_RED
                                    //| BACKGROUND_GREEN
                                    //| BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    //| BACKGROUND_INTENSITY
                                    );
            break;
        case '8':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    //| FOREGROUND_RED
                                    //| FOREGROUND_GREEN
                                    //| FOREGROUND_BLUE
                                    | BACKGROUND_RED
                                    | BACKGROUND_GREEN
                                    | BACKGROUND_BLUE
                                    //| FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '9':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    | BACKGROUND_RED
                                    | BACKGROUND_GREEN
                                    | BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        case '0':
            SetConsoleTextAttribute(hConsole,
                                    0
                                    | FOREGROUND_RED
                                    | FOREGROUND_GREEN
                                    | FOREGROUND_BLUE
                                    | BACKGROUND_RED
                                    | BACKGROUND_GREEN
                                    | BACKGROUND_BLUE
                                    | FOREGROUND_INTENSITY
                                    | BACKGROUND_INTENSITY
                                    );
            break;
        }
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
