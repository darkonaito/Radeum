#ifndef D_SLIDERHANDLER_HPP
#define D_SLIDERHANDLER_HPP

#include <vector>
#include <algorithm>

#include "slider.hpp"
#include "window.hpp"

class SliderHandler
{
    public:
        SliderHandler(const rdm::types::Window& window, const rdm::types::Size font_size);

        void addSlider   (SliderButton* const slider);
        void removeSlider(SliderButton* const slider);

        void update();

    private:
        std::vector<SliderButton*> sliders;

        SliderButton* last_hooked {};

        const rdm::types::Window& window;
        const rdm::types::Size font_size;
};

#endif
