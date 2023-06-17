#ifndef D_CURSOR_HPP
#define D_CURSOR_HPP

#include "types.hpp"

class rdm::types::Cursor
{
    public:
        Cursor();
        
        // Get coords
        Size getCoords() const;

        // Set absolute and relative coords
        void setCoords(Size   coords) const;
        void setCoords(Coords coords) const;
};

#endif