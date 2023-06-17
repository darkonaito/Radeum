#ifndef D_CONSOLE_HPP
#define D_CONSOLE_HPP

#include <windows.h>

#include "types.hpp"
#include "coords.hpp"
#include "buffer.hpp"

class rdm::types::Console
{
    public:
        /*** Constructors ***/

        Console(Size buffer_size, const HANDLE& handle = GetStdHandle(STD_OUTPUT_HANDLE));

        /*** Methods ***/

        // Draw buffer region
        void drawBuffer(const Buffer&, const Camera&);

        // Resize output buffer by absolute and relative coords
        Size resizeOutputBuffer(Size);
        Size resizeOutputBuffer(Coords);

        // Get output buffer size
        Size getOutputBufferSize();

        // Set text cursor visibility/size (0 to 100)
        int setTextCursor(Counter);
        
        // Text cursor size > 0?
        bool textCursorIsVisible();

        // Get text cursor size
        Counter getTextCursorSize();

        // Set text cursor coords
        void setTextCursorCoords(Size absolute_coords);
        void setTextCursorCoords(Coords relative_coords);

        // Get text cursor coords
        Size getTextCursorCoords();

        // Get current console handle
        HANDLE getHandle();

    private:
        HANDLE handle;
};

#endif