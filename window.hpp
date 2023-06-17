#ifndef D_WINDOW_HPP
#define D_WINDOW_HPP

#include <string_view>
#include <Windows.h>

#include "types.hpp"

class rdm::types::Window
{
    public:
        /*** Constructor ***/

        // Coords, size, title
        Window(Size position, Size size, const std::string_view& title);

        /*** Methods ***/

        // Move by absolute and relative coords
        void move(Size);
        void move(Coords);

        // Resize by absolute and relative coords
        void resize(Size);
        void resize(Coords);

        // Resize client area by absolute and relative coords
        void resizeClientArea(Size);
        void resizeClientArea(Coords);

        // Show and hide 
        void setVisibility(bool);

        // Set title 
        void setTitle(const std::string_view& title);

        // Checks whether window is focused
        bool isFocused() const;

        // *Getters*

        // Get coords
        Size getCoords() const;

        // Get size
        Size getSize() const;

        // Get client area start coords
        Size getClientAreaCoords() const;    
        
        // Get client area size 
        Size getClientAreaSize() const;
        
    private:
        HWND handle;
};

#endif