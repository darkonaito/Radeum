#ifndef D_CAMERA_HPP
#define D_CAMERA_HPP

#include "types.hpp"
#include "coords.hpp"

class rdm::types::Camera
{
    public:
        /*** Constructors ***/

        // Starting buffer point, size of buffer region to draw, coords of the console to draw the region at
        Camera(const Size t_start, const Size t_size, const Size t_offset):
            starting_coords(t_start), draw_region_size(t_size), border_offset(t_offset)
        {
        }

        // *Setters*

        // Scroll by absolute and relative coords
        inline void scroll(const Size t_abs_coords) {starting_coords = t_abs_coords;}
        inline void scroll(const Coords t_rel_coords) {starting_coords += t_rel_coords;}

        // Set absolute and relative draw region size
        inline void setDrawRegionArea(const Size t_abs_coords) {draw_region_size = t_abs_coords;}
        inline void setDrawRegionArea(const Coords t_rel_coords) {draw_region_size += t_rel_coords;}

        // Set absolute and relative offset from top-left corner
        inline void setBorderOffset(const Size   t_abs_coords) {border_offset = t_abs_coords;}
        inline void setBorderOffset(const Coords t_rel_coords) {border_offset += t_rel_coords;}

        // Get starting area coords
        inline Size getStartingCoords() const {return starting_coords;}

        // Get draw region size 
        inline Size getDrawRegionArea() const {return draw_region_size;}

        // Get offset from top-left corner
        inline Size getBorderOffset()   const {return border_offset;}

    private:
        Size starting_coords;
        Size draw_region_size;
        Size border_offset;
};

#endif