#ifndef D_KEYSTATE_HPP
#define D_KEYSTATE_HPP

#include "types.hpp"

enum class rdm::types::KeyState : rdm::types::Counter
{
    NOSTATE      = 0b0001,
    JUSTPRESSED  = 0b0010,
    BEINGHELD    = 0b0100,
    JUSTRELEASED = 0b1000,

    DOWN = JUSTPRESSED | BEINGHELD,
    UP   = NOSTATE     | JUSTRELEASED
};

rdm::types::KeyState operator&(rdm::types::KeyState, rdm::types::KeyState);

rdm::types::KeyState operator|(rdm::types::KeyState, rdm::types::KeyState);

#endif