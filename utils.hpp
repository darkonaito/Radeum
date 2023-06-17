#ifndef D_UTILS_HPP
#define D_UTILS_HPP

#include "pixel.hpp"

namespace rdm::utils
{
    types::Pixel charInfoToPixel(CHAR_INFO);

    types::Size getScreenSize();

    types::Size getScreenSize2();

    types::Size getScreenCenter();
}

#endif