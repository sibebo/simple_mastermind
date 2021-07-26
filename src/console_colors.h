#pragma once

#include <iostream>

#include <windows.h>

namespace console_color {
class ConsoleColor
{
public:
    ConsoleColor(int color)
        : color(color)
    {
    }
    
    friend  std::ostream&    operator<<(std::ostream &stream, const ConsoleColor &c) 
    {
        const auto  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, c.color);
        return stream;
    }

private:
    int     color;
};

const ConsoleColor  reset(0
                | FOREGROUND_RED 
                | FOREGROUND_GREEN 
                | FOREGROUND_BLUE
                //| BACKGROUND_RED 
                //| BACKGROUND_GREEN 
                //| BACKGROUND_BLUE
                | FOREGROUND_INTENSITY
                //| BACKGROUND_INTENSITY
            );

const ConsoleColor  red(0
                | FOREGROUND_RED 
                | FOREGROUND_GREEN 
                | FOREGROUND_BLUE
                | BACKGROUND_RED 
                //| BACKGROUND_GREEN 
                //| BACKGROUND_BLUE
                | FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );

const ConsoleColor  green(0
                | FOREGROUND_RED 
                | FOREGROUND_GREEN 
                | FOREGROUND_BLUE
                //| BACKGROUND_RED 
                | BACKGROUND_GREEN 
                //| BACKGROUND_BLUE
                | FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );

const ConsoleColor  blue(0
                | FOREGROUND_RED 
                | FOREGROUND_GREEN 
                | FOREGROUND_BLUE
                //| BACKGROUND_RED 
                //| BACKGROUND_GREEN 
                | BACKGROUND_BLUE
                | FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );

const ConsoleColor  yellow(0
                //| FOREGROUND_RED 
                //| FOREGROUND_GREEN 
                //| FOREGROUND_BLUE
                | BACKGROUND_RED 
                | BACKGROUND_GREEN 
                //| BACKGROUND_BLUE
                //| FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );

const ConsoleColor  orange(0
                //| FOREGROUND_RED 
                //| FOREGROUND_GREEN 
                //| FOREGROUND_BLUE
                | BACKGROUND_RED 
                | BACKGROUND_GREEN 
                //| BACKGROUND_BLUE
                //| FOREGROUND_INTENSITY
                //| BACKGROUND_INTENSITY
            );

const ConsoleColor  magenta(0
                | FOREGROUND_RED 
                | FOREGROUND_GREEN 
                | FOREGROUND_BLUE
                | BACKGROUND_RED 
                //| BACKGROUND_GREEN 
                | BACKGROUND_BLUE
                | FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );

const ConsoleColor  cyan(0
                //| FOREGROUND_RED 
                //| FOREGROUND_GREEN 
                //| FOREGROUND_BLUE
                //| BACKGROUND_RED 
                | BACKGROUND_GREEN 
                | BACKGROUND_BLUE
                //| FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );

const ConsoleColor  black(0
                | FOREGROUND_RED 
                | FOREGROUND_GREEN 
                | FOREGROUND_BLUE
                //| BACKGROUND_RED 
                //| BACKGROUND_GREEN 
                //| BACKGROUND_BLUE
                | FOREGROUND_INTENSITY
                //| BACKGROUND_INTENSITY
            );

const ConsoleColor  white(0
                //| FOREGROUND_RED 
                //| FOREGROUND_GREEN 
                //| FOREGROUND_BLUE
                | BACKGROUND_RED 
                | BACKGROUND_GREEN 
                | BACKGROUND_BLUE
                //| FOREGROUND_INTENSITY
                | BACKGROUND_INTENSITY
            );



}   //namespace console_color {
