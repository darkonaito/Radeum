#include "drawable.hpp"
#include "base_movement_controls.hpp"
#include <functional>
#include "texture.hpp"

#ifndef D_BUTTON_HPP
#define D_BUTTON_HPP

class rdm::types::Button : public rdm::abstr::BaseMovementControls, public rdm::abstr::Drawable
{
    public:

        using Action   = std::function<void(void)>;
        using Effecter = std::function<void(rdm::types::Texture&)>; 

        enum class Event
        {
            RIGHT_CLICK,
            MIDDLE_CLICK,
            LEFT_CLICK,
            MOUSE_HOVER
        };

        // Button texture, button position
        Button(const rdm::types::Texture& texture, rdm::types::Size coords = {});

        // Copy constructor
        Button(const Button& button);

        // Move constructor
        Button(const Button&& button);

        // Copy assignment 
        Button& operator=(const Button& button);

        // Move assignment 
        Button& operator=(const Button&& button);
        
        // Set event related action
        void setAction(Event event, Action action);

        // Set effect to apply to the button texture on some event
        void setEffect(Event event, Effecter effecter);

        // Perform action related to event
        void performAction(Event event);

        // Enable event 
        void enableEvent(Event event, bool enable = true);

        // Enable button visibility
        void enableVisibility (bool enable = true);

        // Get function visibility
        bool isVisible();
    
        // Check if event is enabled
        bool isEnabled(Event event);

        // Get button texture
        const rdm::types::Texture& getTexture() const;

    private:
        std::array<std::tuple<Action, Effecter, bool>, 4> actions;
};

#endif