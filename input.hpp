#ifndef D_INPUT_HPP
#define D_INPUT_HPP

#include "types.hpp"
#include "keystate.hpp"

class rdm::types::InputHandler
{
    public:
        InputHandler();

        // Update key states
        void update();

        // Get key state
        KeyState getKeyState(Counter);

    private:
        static constexpr Counter KEYS_NUMBER {254};

        KeyState keystates[KEYS_NUMBER];
};

#endif