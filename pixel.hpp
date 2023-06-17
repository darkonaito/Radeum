#ifndef D_PIXEL_HPP
#define D_PIXEL_HPP

#include "types.hpp"
#include "color.hpp"

struct rdm::types::Pixel
{
    Pixel(Color foreground_color = Color::random, Color background_color = Color::random, wchar_t character = random_char);

    Pixel& operator=(Pixel pixel);

    bool operator==(Pixel pixel) const;

    bool operator!=(Pixel pixel) const;

    CHAR_INFO to_charinfo() const;

    Color   fore;
    Color   back;
    wchar_t txt;

    static constexpr unsigned char transp_char {1};
    static constexpr unsigned char random_char {0};
};

#endif