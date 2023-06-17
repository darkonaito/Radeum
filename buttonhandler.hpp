#ifndef D_BUTTONHANDLER_HPP
#define D_BUTTONHANDLER_HPP

#include "button.hpp"
#include "window.hpp"

class ButtonHandler
{
    public:
        ButtonHandler(const rdm::types::Window& window, const rdm::types::Size font_size);

        void addButton   (rdm::types::Button* const button);
        void removeButton(rdm::types::Button* const button);

        void update();

    private:
        std::vector<rdm::types::Button*> buttons;

        const rdm::types::Window& window;
        const rdm::types::Size font_size;
};

#endif
