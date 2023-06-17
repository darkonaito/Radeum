#include "console.hpp"
#include "coords.hpp"
#include "camera.hpp"
#include "pixel.hpp"

#include <iostream>

rdm::types::Console::Console(const Size t_buff_size, const HANDLE& t_handle):
    handle(t_handle)
{
    resizeOutputBuffer(t_buff_size);
}

void rdm::types::Console::drawBuffer(const Buffer& t_buff, const Camera& t_cam)
{
    static SMALL_RECT write_region;

    write_region.Left   = static_cast<short>(t_cam.getBorderOffset().x);
    write_region.Top    = static_cast<short>(t_cam.getBorderOffset().y);
    write_region.Right  = static_cast<short>(t_cam.getBorderOffset().x + t_cam.getDrawRegionArea().x);
    write_region.Bottom = static_cast<short>(t_cam.getBorderOffset().y + t_cam.getDrawRegionArea().y);

    WriteConsoleOutput(
        // Handle to the current console
        handle,
        // Console buffer to read from
        t_buff.getBuffer(),
        // Size of the console buffer
        COORD{static_cast<short>(t_buff.getSize().x), static_cast<short>(t_buff.getSize().y)},
        // Top-left point of the buffer to start reading from
        COORD {
            static_cast<short>(t_cam.getStartingCoords().x),
            static_cast<short>(t_cam.getStartingCoords().y)
        },
        // Region of the console to write to
        &write_region
    );
}

rdm::types::Size rdm::types::Console::resizeOutputBuffer(Size t_abs_size)
{
    SetConsoleScreenBufferSize(
        handle,
        {
            static_cast<SHORT>(t_abs_size.x),
            static_cast<SHORT>(t_abs_size.y)
        }
    );

    return t_abs_size;
}

rdm::types::Size rdm::types::Console::resizeOutputBuffer(Coords t_rel_size)
{
    static Size output_buffer_size;

    return resizeOutputBuffer(getOutputBufferSize() + t_rel_size);
}

rdm::types::Size rdm::types::Console::getOutputBufferSize()
{
    static CONSOLE_SCREEN_BUFFER_INFO console_buffer_info;

    GetConsoleScreenBufferInfo(handle, &console_buffer_info);

    return Size {
        static_cast<BigCounter>(console_buffer_info.dwSize.X),
        static_cast<BigCounter>(console_buffer_info.dwSize.Y)
    };
}

int rdm::types::Console::setTextCursor(Counter t_n)
{
    static CONSOLE_CURSOR_INFO cursor_info;

    if(t_n == 0)
    {
        cursor_info.bVisible = false;
        cursor_info.dwSize = getTextCursorSize();
    } else 
    {
        cursor_info.bVisible = textCursorIsVisible();
        cursor_info.dwSize = t_n;
    }

    return SetConsoleCursorInfo(handle, &cursor_info);
}

bool rdm::types::Console::textCursorIsVisible()
{
    static CONSOLE_CURSOR_INFO cursor_info;

    GetConsoleCursorInfo(handle, &cursor_info);

    return cursor_info.bVisible;
}

rdm::types::Counter rdm::types::Console::getTextCursorSize()
{
    static CONSOLE_CURSOR_INFO cursor_info;

    GetConsoleCursorInfo(handle, &cursor_info);

    return cursor_info.dwSize;
}

void rdm::types::Console::setTextCursorCoords(const Size t_abs_coords)
{
    SetConsoleCursorPosition(
        handle,
        {
            static_cast<short>(t_abs_coords.x),
            static_cast<short>(t_abs_coords.y)
        }
    );
}

void rdm::types::Console::setTextCursorCoords(const Coords t_rel_coords)
{
    setTextCursorCoords(getTextCursorCoords() + t_rel_coords);
}


rdm::types::Size rdm::types::Console::getTextCursorCoords()
{
    static CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

    GetConsoleScreenBufferInfo(handle, &screen_buffer_info);

    return Size
    {
        static_cast<BigCounter>(screen_buffer_info.dwCursorPosition.X),
        static_cast<BigCounter>(screen_buffer_info.dwCursorPosition.Y)
    };
}

HANDLE rdm::types::Console::getHandle()
{
    return handle;
}