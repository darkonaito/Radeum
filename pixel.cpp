#include "pixel.hpp"
#include "utils.hpp"
#include "random.hpp"

#include <limits>
#include <ctime>

rdm::types::Pixel::Pixel(Color t_fore, Color t_back, wchar_t t_txt):
    fore(t_fore), back(t_back), txt(t_txt)
{
}

rdm::types::Pixel& rdm::types::Pixel::operator=(const Pixel t_pxl)
{
    fore = t_pxl.fore;
    back = t_pxl.back;
    txt = t_pxl.txt;

    return *this;
}

bool rdm::types::Pixel::operator==(const Pixel t_pxl) const
{
    if(
        fore == t_pxl.fore &&
        back == t_pxl.back &&
        txt  == t_pxl.txt
    )
    {
        return true;
    } else return false;
}

bool rdm::types::Pixel::operator!=(const Pixel t_pxl) const
{
    if(
        fore != t_pxl.fore ||
        back != t_pxl.back ||
        txt  != t_pxl.txt
    )
    {
        return true;
    } else return false;
}

CHAR_INFO rdm::types::Pixel::to_charinfo() const
{
    static RandomGenerator rand_gen {std::time(nullptr)};

    static int     i_fore;
    static int     i_back;
    static wchar_t n_txt; 

    if(fore == Color::random)
    {
        i_fore = rand_gen.getRandomInt(static_cast<int>(Color::min_color), static_cast<int>(Color::max_color));
    } else 
    {
        i_fore = static_cast<WORD>(fore);
    }

    if(back == Color::random)
    {
        i_back = rand_gen.getRandomInt(static_cast<int>(Color::min_color), static_cast<int>(Color::max_color));
    } else 
    {
        i_back = static_cast<WORD>(back);
    }

    if(txt == random_char)
    {
        n_txt = static_cast<wchar_t>(
            rand_gen.getRandomInt(
                std::numeric_limits<wchar_t>::min(),
                std::numeric_limits<wchar_t>::max()
            )
        );
    } else 
    {
        n_txt = txt;
    }

    return {
        n_txt, static_cast<WORD>(i_fore | (i_back << 4))
    };
}