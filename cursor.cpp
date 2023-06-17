#include "cursor.hpp"
#include "coords.hpp"
#include <windows.h>

rdm::types::Cursor::Cursor()
{
}

rdm::types::Size rdm::types::Cursor::getCoords() const
{
    // Static const pointer to a POINT object 
    static POINT* const cursor_pos {new POINT};

    // Gets cursor position
    GetCursorPos(cursor_pos);

    return {
        static_cast<BigCounter>(cursor_pos->x),
        static_cast<BigCounter>(cursor_pos->y)
    };
}

void rdm::types::Cursor::setCoords(Size t_abs_coords) const
{
    SetCursorPos(t_abs_coords.x, t_abs_coords.y);
}

void rdm::types::Cursor::setCoords(Coords t_rel_coords) const
{
    static Size current_coords;
    
    current_coords = getCoords();

    SetCursorPos(current_coords.x + t_rel_coords.x, current_coords.y + t_rel_coords.y);
}