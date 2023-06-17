#include "slider.hpp"

#include <cmath>

SliderButton::SliderButton(
    const rdm::types::Texture& slider_texture,
    const rdm::types::Texture& slide_segment_texture,
    const rdm::types::BigCounter slider_size,
    const rdm::types::Size coords
)
:
    BaseMovementControls(coords, {}), Drawable{},
    slider_texture(slider_texture),
    slide_segment_texture(slide_segment_texture),
    slider_size(slider_size) 
{
    using namespace rdm::types;

    const Coords segment_size {slide_segment_texture.getSize()};

    for(BigCounter i {}; i < slider_size; i += segment_size.x)
    {
        elements.push_back(std::make_tuple(slide_segment_texture, Size{coords.x + i, coords.y + slider_texture.getSize().y / 2 - segment_size.y / 2}, true));
    }

    elements.push_back(std::make_tuple(slider_texture, coords, true));
}

double SliderButton::getValue() const
{
    return static_cast<double>(std::get<1>(elements.back()).x - coords.x) / static_cast<double>(slider_size);
}

void SliderButton::setValue(const double value)
{
    if(value >= 0 && value <= 1)
    {
        std::get<1>(elements.back()).x = std::round(slider_size * value);
    }
}

void SliderButton::setSliderIntensity(const rdm::types::BigCounter intensity)
{
    if(intensity <= slider_size)
    {
        std::get<1>(getSlider()).x = coords.x + intensity;
    } 
}

rdm::types::Size SliderButton::getSliderCoords() const
{
    return std::get<1>(getSlider());
}

rdm::types::Size SliderButton::getSliderSize() const 
{
    return std::get<0>(getSlider()).getSize();
}

const SliderButton::Element& SliderButton::getSlider() const
{
    return elements.back();
}

SliderButton::Element& SliderButton::getSlider()
{
    return elements.back();
}