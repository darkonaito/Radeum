#include "sliderhandler.hpp" 

#include "cursor.hpp"
#include "key.hpp"
#include "types.hpp"

#include <winuser.h>

SliderHandler::SliderHandler(const rdm::types::Window& t_window, const rdm::types::Size t_font_size)
:
    window(t_window), font_size(t_font_size)
{
}

void SliderHandler::addSlider(SliderButton* const slider)
{
    if(slider != nullptr) sliders.push_back(slider);
}

void SliderHandler::removeSlider(SliderButton* const slider)
{
    sliders.erase(std::find(sliders.begin(), sliders.end(), slider));
}

void SliderHandler::update()
{
    static const rdm::types::Cursor cursor;

    static rdm::types::Key right_button {VK_RBUTTON};

    right_button.update();

    if(right_button.isJustReleased())
    {
        last_hooked = nullptr;
    } else 
    {
        const rdm::types::Size cursor_pos {(cursor.getCoords() - window.getClientAreaCoords()) / font_size};

        if(right_button.isBeingHeld())
        {
            if(last_hooked) last_hooked->setSliderIntensity(cursor_pos.x - last_hooked->getCoords().x);
        } else 
        if(right_button.isJustPressed())
        {
            for(const auto& i : sliders)
            {
                if(cursor_pos.areWithin(i->getSliderCoords(), i->getSliderCoords() + i->getSliderSize()))
                {
                    last_hooked = i;

                    break;
                }
            }
        }
    }
}
