#include "input.hpp"
#include "keystate.hpp"
#include <windows.h>
#include <algorithm>

rdm::types::InputHandler::InputHandler()
{
    // Initialize key states array
    std::fill_n(keystates, KEYS_NUMBER, KeyState::UP);
}

void rdm::types::InputHandler::update()
{
    for(size_t i {}; i < KEYS_NUMBER; ++i)
    {
        bool key_is_down {
            static_cast<bool>(GetAsyncKeyState(i + 1))
        };

        if(static_cast<bool>(keystates[i] & KeyState::UP))
        {
            if(key_is_down)
            {
                keystates[i] = KeyState::JUSTPRESSED;
            } else 
            {
                keystates[i] = KeyState::NOSTATE;
            }
        } else 
        {
            if(static_cast<bool>(keystates[i] & KeyState::DOWN))
            {
                if(key_is_down)
                {
                    keystates[i] = KeyState::BEINGHELD;
                } else 
                {
                    keystates[i] = KeyState::JUSTRELEASED;
                }
            }
        }
    }
}

rdm::types::KeyState rdm::types::InputHandler::getKeyState(Counter t_key)
{
    // The array starts at [0], and the first key code is 1, so key_code - 1
    return keystates[t_key - 1];
}