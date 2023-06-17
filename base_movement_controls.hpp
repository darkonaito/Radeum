#ifndef D_BASE_MOVEMENT_CONTROLS_HPP
#define D_BASE_MOVEMENT_CONTROLS_HPP

#include "types.hpp"
#include "abstracts.hpp"
#include "coords.hpp"

class rdm::abstr::BaseMovementControls
{
    public:
        BaseMovementControls(types::Size coords, types::Size speed)
        :
            coords(coords),
            speed(speed)
        {
        }
        
        types::Size setSpeed(types::Size t_abs_speed)
        {
            return speed = t_abs_speed;
        }

        types::Size setSpeed(types::Coords t_rel_speed)
        {
            return speed += t_rel_speed;
        }

        types::Coords setCoords(types::Size t_abs_coords)
        {
            return coords = t_abs_coords;
        }

        types::Coords setCoords(types::Coords t_rel_coords)
        {
            return coords += t_rel_coords;
        }

        types::Size   getCoords() const {return coords;}
        types::Coords getSpeed () const {return speed; }  

        void incrsX() {++coords.x;}
        void incrsY() {++coords.y;}

        void decrsX() {--coords.x;}
        void decrsY() {--coords.y;}

    protected:
        types::Size   coords;
        types::Coords speed;
};

#endif