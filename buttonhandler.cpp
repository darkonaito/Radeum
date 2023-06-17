#include "buttonhandler.hpp" 

#include "cursor.hpp"
#include "key.hpp"
#include "types.hpp"

#include <winuser.h>

#include <iostream>

ButtonHandler::ButtonHandler(const rdm::types::Window& t_window, const rdm::types::Size t_font_size)
:
    window(t_window), font_size(t_font_size)
{
}

void ButtonHandler::addButton(rdm::types::Button* const button)
{
    if(button != nullptr) buttons.push_back(button);
}

void ButtonHandler::removeButton(rdm::types::Button* const button)
{
    buttons.erase(std::find(buttons.begin(), buttons.end(), button));
}

void ButtonHandler::update()
{
    static const rdm::types::Cursor cursor;

    static rdm::types::Key
        right_button  {VK_RBUTTON},
        left_button   {VK_LBUTTON},
        middle_button {VK_MBUTTON}
    ;

    right_button .update();
    left_button  .update();
    middle_button.update();

    const rdm::types::Size contexted_cursor_coords
    {
        (cursor.getCoords() - window.getClientAreaCoords()) / font_size
    };

    for(auto& i : buttons)
    {
        if(contexted_cursor_coords.areWithin(i->getCoords(), i->getCoords() + i->getTexture().getSize()))
        {
            if(i->isVisible())
            {
                if(i->isEnabled(rdm::types::Button::Event::MOUSE_HOVER)) i->performAction(rdm::types::Button::Event::MOUSE_HOVER);

                if(right_button .isDown() && i->isEnabled(rdm::types::Button::Event::RIGHT_CLICK )) i->performAction(rdm::types::Button::Event::RIGHT_CLICK );
                if(left_button  .isDown() && i->isEnabled(rdm::types::Button::Event::LEFT_CLICK  )) i->performAction(rdm::types::Button::Event::LEFT_CLICK  );
                if(middle_button.isDown() && i->isEnabled(rdm::types::Button::Event::MIDDLE_CLICK)) i->performAction(rdm::types::Button::Event::MIDDLE_CLICK);
            }

            break;
        }
    }
}
