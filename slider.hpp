#ifndef D_SLIDER_HPP
#define D_SLIDER_HPP

#include "base_movement_controls.hpp"
#include "drawable.hpp"

class SliderButton : public rdm::abstr::BaseMovementControls, public rdm::abstr::Drawable
{
    public:
        SliderButton(
            const rdm::types::Texture&   slider_texture,
            const rdm::types::Texture&   slide_segment_texture,
            const rdm::types::BigCounter slider_size,
            const rdm::types::Size       coords = {}
        );

        double getValue() const;

        void setValue(double value);

        void setSliderIntensity(rdm::types::BigCounter intensity);

        rdm::types::Size getSliderCoords() const;

        rdm::types::Size getSliderSize() const;

    protected:
        const Element& getSlider() const;

        Element& getSlider();

        rdm::types::Texture slider_texture;
        rdm::types::Texture slide_segment_texture;

        rdm::types::BigCounter slider_size;
};

#endif