#include "utils.hpp"
#include "coords.hpp"
#include <windows.h>

rdm::types::Pixel rdm::utils::charInfoToPixel(CHAR_INFO t_ch_info)
{
    return types::Pixel {
        static_cast<types::Color>( t_ch_info.Attributes & 0b00001111),
        static_cast<types::Color>((t_ch_info.Attributes & 0b11110000) >> 4),
        static_cast<wchar_t>        ( t_ch_info.Char.UnicodeChar)
    };
}

rdm::types::Size rdm::utils::getScreenSize()
{
    return {
        static_cast<types::BigCounter>(GetSystemMetrics(SM_CXVIRTUALSCREEN)),
        static_cast<types::BigCounter>(GetSystemMetrics(SM_CYVIRTUALSCREEN))
    };
}

rdm::types::Size rdm::utils::getScreenSize2()
{
    const static types::Size screen_size
    {
        []()
        {
            const HWND desktop_handle{GetDesktopWindow()};

            RECT rect;

            GetWindowRect(desktop_handle, &rect);

            return types::Size
            {
                rect.right, rect.bottom
            };
        }()
    };

    return screen_size;
}

rdm::types::Size rdm::utils::getScreenCenter()
{
    return getScreenSize() / 2;
}