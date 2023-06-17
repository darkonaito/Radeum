#include "button.hpp"

#include <iostream>

rdm::types::Button::Button(const rdm::types::Texture& t_txt, const rdm::types::Size t_coords)
:
    BaseMovementControls(t_coords, {}),
    Drawable{std::make_tuple(t_txt, t_coords, true)}
{
    // Already crashes here
}

rdm::types::Button::Button(const Button& t_butt)
:
    BaseMovementControls(t_butt.coords, t_butt.speed),
    Drawable(t_butt.elements)
{
    actions = t_butt.actions;
}

rdm::types::Button::Button(const Button&& t_butt)
:
    BaseMovementControls(t_butt.coords, t_butt.speed),
    Drawable(std::move(t_butt.elements)),
    actions(std::move(t_butt.actions))
{
}

rdm::types::Button& rdm::types::Button::operator=(const Button& t_butt)
{
    coords = t_butt.coords;
    speed  = t_butt.speed;

    actions  = t_butt.actions;
    elements = t_butt.elements;

    return *this;
}

rdm::types::Button& rdm::types::Button::operator=(const Button&& t_butt)
{
    coords = t_butt.coords;
    speed  = t_butt.speed;

    actions  = std::move(t_butt.actions);
    elements = std::move(t_butt.elements);

    return *this;
}

void rdm::types::Button::setAction(const Event t_event, Action t_action)
{
    std::get<Action>(actions[static_cast<size_t>(t_event)]) = t_action;
}

void rdm::types::Button::setEffect(const Event t_event, Effecter t_effecter)
{
    std::get<Effecter>(actions[static_cast<size_t>(t_event)]) = t_effecter;
}

void rdm::types::Button::performAction(const Event t_event)
{
    std::get<Action>(actions[static_cast<size_t>(t_event)])();

    if(std::get<Effecter>(actions[static_cast<size_t>(t_event)]))
    {
        std::get<Effecter>(actions[static_cast<size_t>(t_event)])(std::get<rdm::types::Texture>(elements.front()));
    }
}

void rdm::types::Button::enableEvent(const Event t_event, bool t_enable)
{
    std::get<bool>(actions[static_cast<size_t>(t_event)]) = t_enable;
}

void rdm::types::Button::enableVisibility(bool t_enable)
{
    std::get<bool>(elements.front()) = t_enable;
}

bool rdm::types::Button::isVisible()
{
    return std::get<bool>(elements.front());
}

bool rdm::types::Button::isEnabled(Event t_event)
{
    return std::get<bool>(actions[static_cast<size_t>(t_event)]);
}

const rdm::types::Texture& rdm::types::Button::getTexture() const
{
    return std::get<rdm::types::Texture>(elements.front());
}