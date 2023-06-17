#include "key.hpp"
#include "windows.h"

rdm::types::Key::Key(Counter t_code)
:   code(t_code)
{
}

bool rdm::types::Key::operator==(const Key t_key) const
{
    return code == t_key.code;
}

std::chrono::duration<double> rdm::types::Key::getPressedTime()
{
    return std::chrono::steady_clock::now() - last_pressed;
}

std::chrono::duration<double> rdm::types::Key::getReleasedTime()
{
    return std::chrono::steady_clock::now() - last_released;
}

rdm::types::KeyState rdm::types::Key::getState() const
{
    return state;
}

bool rdm::types::Key::isJustPressed() const
{
    return static_cast<bool>(state & KeyState::JUSTPRESSED);
}

bool rdm::types::Key::isBeingHeld() const
{
    return static_cast<bool>(state & KeyState::BEINGHELD);
}

bool rdm::types::Key::isJustReleased() const
{
    return static_cast<bool>(state & KeyState::JUSTRELEASED);
}

bool rdm::types::Key::isNoState() const
{
    return static_cast<bool>(state & KeyState::NOSTATE);
}

bool rdm::types::Key::isUp() const
{
    return isJustReleased() || isNoState();
}

bool rdm::types::Key::isDown() const
{
    return isJustPressed() || isBeingHeld();
}

void rdm::types::Key::update()
{
    const bool key_is_down {
        static_cast<bool>(GetAsyncKeyState(code))
    };

    if(static_cast<bool>(state & KeyState::UP))
    {
        if(key_is_down)
        {
            state = KeyState::JUSTPRESSED;

            last_pressed = std::chrono::steady_clock::now();
        } else 
        {
            state = KeyState::NOSTATE;
        }
    } else 
    {
        if(static_cast<bool>(state & KeyState::DOWN))
        {
            if(key_is_down)
            {
                state = KeyState::BEINGHELD;
            } else 
            {
                state = KeyState::JUSTRELEASED;

                last_released = std::chrono::steady_clock::now();
            }
        }
    }
}

rdm::types::Counter rdm::types::Key::getCode() const 
{
    return code;
}