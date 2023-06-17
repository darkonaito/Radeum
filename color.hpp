#ifndef D_COLOR_HPP
#define D_COLOR_HPP

#include <windows.h>
#include "types.hpp"

enum class rdm::types::Color : rdm::types::Counter 
{
    black       = 0,
    dark_red    = FOREGROUND_RED,
    green       = FOREGROUND_GREEN,
    dark_blue   = FOREGROUND_BLUE,
    aqua        = FOREGROUND_GREEN | FOREGROUND_BLUE,
    olive       = FOREGROUND_RED | FOREGROUND_GREEN,
    purple      = FOREGROUND_RED | FOREGROUND_BLUE,
    light_gray  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    gray        = FOREGROUND_INTENSITY,
    red         = FOREGROUND_INTENSITY | FOREGROUND_RED,
    light_green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    blue        = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    light_aqua  = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    yellow      = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    magenta     = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    white       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    random      = 16,
    transp      = 17,

    min_value = 0,
    max_value = 17,

    min_color = 0,
    max_color = 15
};

#ifdef D_COLOR_MANIP

#include <iostream>

inline std::ostream& operator<<(std::ostream& t_stream, const rdm::types::Color t_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(t_color));

    return t_stream;
}


#endif

#endif