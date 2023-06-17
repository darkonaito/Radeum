#ifndef D_KEY_HPP
#define D_KEY_HPP

#include "types.hpp"
#include "keystate.hpp"

#include <chrono>

class rdm::types::Key
{
    public: 
        // Initialize with key code
        Key(Counter key);

        bool operator==(Key key) const;

        // Update key state
        void update();

        // Get pressed time
        std::chrono::duration<double> getPressedTime();

        // Get released time
        std::chrono::duration<double> getReleasedTime();

        // Get key state
        KeyState getState() const;

        // Direct states
        bool isJustPressed()  const;
        bool isBeingHeld()    const;
        bool isJustReleased() const;
        bool isNoState()      const;

        bool isUp()   const;
        bool isDown() const;

        Counter getCode() const;

    private:
        KeyState state {KeyState::UP};

        Counter code;

        std::chrono::steady_clock::time_point last_pressed;
        std::chrono::steady_clock::time_point last_released;
};

#endif